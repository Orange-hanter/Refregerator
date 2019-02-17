
int module( int arg )
{
	if ( arg < 0 )
	return -arg;
	return arg;
}

void my_delay_ms(int ms)
{
	while (0 < ms)
	{
		_delay_ms(1);
		--ms;
	}
}
unsigned char  OK_Flag = 0;

unsigned char DS18B20_init(void)
{
	
	PORTC &= ~(1 << PC0);
	DDRC |= (1 << PC0);
	_delay_us(490);
	DDRC &= ~(1 << PC0);
	_delay_us(68);
	OK_Flag = (PINC & (1 << PC0));
	_delay_us(422);
	
	PORTC &= ~(1 << PC1);
	DDRC |= (1 << PC1);
	_delay_us(490);
	DDRC &= ~(1 << PC1);
	_delay_us(68);
	OK_Flag = (PINC & (1 << PC1));
	_delay_us(422);
	
	return OK_Flag;
}

unsigned char read_18b20_0(void)
{
	unsigned char i;
	unsigned char dat = 0;
	for (i = 0; i < 8; i++)
	{
		DDRC |= (1 << PC0);
		_delay_us(2);
		DDRC &= ~(1 << PC0);
		_delay_us(4);
		dat = dat >> 1;
		if (PINC & (1 << PC0))
		{
			dat |= 0x80;
		}
		_delay_us(62);
	}
	_delay_us(422);
	return dat;
	
}

unsigned char read_18b20_1(void)
{

	unsigned char i;
	unsigned char dat = 0;
	for (i = 0; i < 8; i++)
	{
		DDRC |= (1 << PC1);
		_delay_us(2.0);
		DDRC &= ~(1 << PC1);
		_delay_us(4.0);
		dat = dat >> 1;
		if (PINC & (1 << PC1))
		{
			dat |= 0x80;
		}
		_delay_us(62.0);
	}
	return dat;
}

void write_18b20_0(unsigned char dat)
{
	
	unsigned char i;
	for (i = 0; i < 8; i++)
	{
		DDRC |= (1 << PC0);
		_delay_us(2.0);
		if (dat & 0x01)
		{
			DDRC &= ~(1 << PC0);
		}
		else
		{
			DDRC |= (1 << PC0);
		}
		dat = dat >> 1;
		_delay_us(62.0);
		DDRC &= ~(1 << PC0);
		_delay_us(2.0);
	}
}

void write_18b20_1(unsigned char dat)
{
	unsigned char i;
	for (i = 0; i < 8; i++)
	{
		DDRC |= (1 << PC1);
		_delay_us(2);
		if (dat & 0x01)
		{
			DDRC &= ~(1 << PC1);
		}
		else
		{
			DDRC |= (1 << PC1);
		}
		dat = dat >> 1;
		_delay_us(62);
		DDRC &= ~(1 << PC1);
		_delay_us(2);
	}
}

