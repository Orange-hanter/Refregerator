#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include "utils.hpp"
#include "PortEntity.h"
#include "Display8Segment.h"

// дефайны именующие секции экрана
#define DISP_SECT_1 PA4
#define DISP_SECT_2 PA5
#define DISP_SECT_3 PA6
#define DISP_SECT_4 PA7

PortEntity myPortD( PORT::D );
Display8Segment my_display(PA0, PA1, PA2, PA3, PORT::A );
PortEntity PortACtr (PORT::A);

void setDisplayChannel(short chanell)
{
	PortACtr.setGPIOState(chanell, LEVEL::HIGH);
}



volatile unsigned char segcounter = 0, MC_p1 = 0, HC_p1 = 0, MC_p2 = 0, HC_p2 = 0;
volatile int mode = 1, 
			display1 = 1, 
			display2 = 2, 
			display3 = 3, 
			display4 = 4, 
			turn_on = 50000;
volatile int tune = 0, cnt_b = 100, MC = 1, HC = 1, MC_p = -4, HC_p = 4, hk = 0, mk = 0;
volatile int hour_1 = 0, hour_2 = 0, min_1 = 0, min_2 = 0, T1 = 2, T2 = -5, turn_onM = 0, turn_onH = 0;
volatile int second = 0, minute = 0, hour = 0, cnt = 0, cnt_m = 0;

ISR(TIMER0_OVF_vect){
	PortACtr.resetAllPINS();
	switch (segcounter)
	{
		case 0:
		setDisplayChannel( DISP_SECT_1 );
		my_display.setNumber( 1 );
		break;
		
		case 1:
		setDisplayChannel( DISP_SECT_2 );
		my_display.setNumber( 2 );
		break;
		
		case 2:
		setDisplayChannel( DISP_SECT_3 );
		my_display.setNumber( 3 );
		break;
		
		case 3:
		setDisplayChannel( DISP_SECT_4 );
		my_display.setNumber( 4 );
		break;
	}
	
	if ((segcounter++) > 2)
	segcounter = 0;
}


ISR(TIMER2_OVF_vect)
{
	cnt++;
	if ( cnt >= 1500 )
	{
		second++;
		if (second >= 59)
		{
			minute++;
			second = 0;
		}
		cnt = 0;
	}

	if (minute > 59)
	{
		hour++;
		minute = 0;
	}
	if (hour > 23)
		hour == 0;

}

unsigned char Temp_H0 = 0, Temp_L0 = 0, Temp_H1 = 0, Temp_L1 = 0, temp_flag;


void init_MC()
{
	DDRD = 0xFF;
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3);
	PORTD = 0x00;
	PORTB = 0x00;

	TIMSK |= (1 << TOIE2); // ?ac?aoaiea i?a?uaaiey ii oaeia?o2
	TCCR2 |= (1 << CS21);  // i?aaaaeeoaeu ia 8

	DDRC = 0x00;
	PORTC = 0xFF;
}

void turn_on_komp_hc()
{
	PORTD |= 0b01000000;
}

void turn_off_komp_hc()
{
	PORTD &= 0b10111111;
}

void turn_on_komp_mc()
{
	PORTD |= 0b10000000;
}

void turn_off_komp_mc()
{
	PORTD &= 0b01111111;
}

int main(void)
{
/*	myPortD.setPGIMode( PD3, MODE::OUTPUT );
	my_display.setNumber(2);
	PortACtr.setGPIOState(PA4, LEVEL::HIGH );
	while(1){};*/
	init_MC();

	unsigned int	tempint0 = 0, 
					tempint0_1, 
					tempint0_2, 
					tempint0_3, 
					tempint1 = 0, 
					tempint1_1, 
					tempint1_2, 
					tempint1_3;
	
	display1 = 1;
	display2 = 2;
	display3 = 3;
	display4 = 4;
	my_delay_ms(turn_on);

	sei();
	while (1)
	{
		
		if ((PORTC | 0b00000011) == 0b01000011) //button mode
		{
			cnt_m++;
			mode = 0;
			if (cnt_m > 1)
			{
				cnt_m = 0;
				mode = 1;
			}
			my_delay_ms(cnt_b);
		}
		else if ((PINC & 0b11111100) == 0b01111100) //button volume on/off
		{
			tune++;
			if (tune > 1)
			tune = 0;
			my_delay_ms(cnt_b);
		}
		else if ((PINC & 0b11111100) == 0b11111000) //button HC on/off
		{
			hk++;
			if (hk > 1)
			{
				HC = 0;
				hk = 0;
			}
			else
			{
				HC = 1;
			}
			my_delay_ms(cnt_b);
		}
		else if ((PINC & 0b11111100) == 0b11110100) //button MC on/off
		{
			mk++;
			if (mk > 1)
			{
				MC = 0;
				mk = 0;
			}
			else
			{
				MC = 1;
			}
			my_delay_ms(cnt_b);
		}
		else if ((PINC & 0b11111100) == 0b11101100) //button MC/hour +
		{
			if (mode == 0)
			{
				MC_p++;
				if (MC_p > (-1))
				MC_p = -12;
			}
			else if (mode == 1)
			{
				hour++;
				if (hour > 23)
				{
					hour = 0;
				}
			}
			my_delay_ms(cnt_b);
		}
		else if ((PINC & 0b11111100) == 0b11011100) //button HC/minute +
		{
			if (mode == 0)
			{
				HC_p++;
				if (HC_p > 12)
				HC_p = 4;
			}
			else if (mode == 1)
			{
				minute++;
				if (minute > 59)
				{
					minute = 0;
				}
			}
			my_delay_ms(cnt_b);
		}

		if (OK_Flag == 1)
		{
			display1 = 1;
			display2 = 2;
			display3 = 3;
			display4 = 4;
		}

		DS18B20_init();
		write_18b20_0(0xCC);
		write_18b20_0(0x44);
		write_18b20_1(0xCC);
		write_18b20_1(0x44);
		my_delay_ms(1000.0);

		DS18B20_init();
		write_18b20_0(0xCC);
		write_18b20_0(0xBE);
		write_18b20_1(0xCC);
		write_18b20_1(0xBE);
		Temp_L0 = read_18b20_0();
		Temp_H0 = read_18b20_0();
		Temp_L1 = read_18b20_1();
		Temp_H1 = read_18b20_1();
		temp_flag = 1;

		if (Temp_H0 & (1 << 3))
		{
			signed int tmp;
			temp_flag = 0;
			tmp = (Temp_H0 << 8) | Temp_L0;
			tmp = -tmp;
			Temp_L0 = tmp;
			Temp_H0 = tmp >> 8;
		}

		tempint0 = ((Temp_H0 << 4) & 0x70) | (Temp_L0 >> 4);
		tempint0_1 = tempint0 % 100 / 10;
		tempint0_2 = tempint0 % 10;
		tempint1 = ((Temp_H1 << 4) & 0x70) | (Temp_L1 >> 4);
		tempint1_1 = tempint1 % 100 / 10;
		tempint1_2 = tempint1 % 10;
		MC_p1 = module((int)MC_p) / 10;
		MC_p2 = module((int)MC_p) % 10;
		HC_p1 = HC_p / 10;
		HC_p2 = HC_p % 10;

		hour_1 = hour / 10;
		hour_2 = hour % 10;
		min_1 = minute / 10;
		min_2 = minute % 10;

		if (tempint0_1 < 1)
		tempint0_1 = 10;
		if (tempint1_1 < 1)
		tempint1_1 = 10;
		if (mode == 0)
		{
			if (MC_p1 < 1)
			MC_p1 = 10;
			if (HC_p1 < 1)
			HC_p1 = 10;
			display1 = MC_p1;
			display2 = MC_p2;
			display3 = HC_p1;
			display4 = HC_p2;
		}
		else if (mode == 1)
		{
			display1 = hour_1;
			display2 = hour_2;
			display3 = min_1;
			display4 = min_2;
		}
		if (HC == 1)
		{
			PORTD |= 0b00010000;
			if (tempint0 >= HC_p)
			turn_on_komp_hc();
			if (tempint0 <= (HC_p - 2))
			turn_off_komp_hc();
		}
		else
		{
			PORTD &= 0b11101111;
			turn_off_komp_hc();
		}
		
		if (MC == 1)
		{
			PORTD |= 0b00001000;
			if (MC_p < 0)
			PORTD |= 0b00000010;
			if (tempint1 >= MC_p)
			turn_on_komp_mc();
			if (tempint1 <= (MC_p - 2))
			turn_off_komp_mc();
		}
		else
		{
			PORTD &= 0b11110111;
			turn_off_komp_mc();
		}

		if (tune == 1)
		{
			if ((PINB | 0b11110111) == 0xFF)
			{
				if (second > 30)
				{
					if ((second - 30) % 2)
					{
						PORTD |= (1 << PD5);
					}
					else
					{
						PORTD &= (0 << PD5);
					}
				}
			}
		}
		else
		{
			if ((PINB | 0b11110111) == 0xFF)
			{
				if (second > 30)
				{
					PORTB |= (1 << PB1);
				}
			}
		}
		if ((PINB | 0b11101111) == 0xFF)
		{
			if (second > 30)
			{
				PORTB |= (1 << PB1);
			}
		}
	}
}
