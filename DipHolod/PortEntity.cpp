/* 
* PortEntity.cpp
*
* Created: 12-Feb-19 23:57:57
* Author: Danil
*/


#include "PortEntity.h"
#include <avr/io.h>

// default constructor
PortEntity::PortEntity( PORT port )
{
	this->portNumber = port;
} //PortEntity

PortEntity::PortEntity( unsigned int port )
{
	switch (port)
	{
	case 0:
		this->portNumber = PORT::A;
		break;
	case 1:
		this->portNumber = PORT::B;
		break;
	case 2:
		this->portNumber = PORT::C;
		break;
	case 3:
		this->portNumber = PORT::D;
		break;
	}
	
} //PortEntity

 PortEntity::PortEntity()
{

}

// default destructor
PortEntity::~PortEntity()
{
} //~PortEntity

void PortEntity::setPort(PORT port)
{
	this->portNumber = port;
}

LEVEL PortEntity::getGPIOState(uint8 number)
{
	if( number < 8 && 0 >= number )
	return LEVEL::LOW;
	
	unsigned int value = 0;
	switch (portNumber)
	{
		case PORT::A: value = PORTA; break;
		case PORT::B: value = PORTB; break;
		case PORT::C: value = PORTC; break;
		case PORT::D: value = PORTD; break;
	}
	return (bool) (( value >> number ) & 0x01) ? LEVEL::HIGH : LEVEL::LOW ;
}

bool PortEntity::getBGPIOState(uint8 number)
{
	if( number < 8 && 0 >= number )
	return false;
	
	unsigned int value = 0;
	switch (portNumber)
	{
		case PORT::A: value = PORTA; break;
		case PORT::B: value = PORTB; break;
		case PORT::C: value = PORTC; break;
		case PORT::D: value = PORTD; break;
	}
	return (bool) (( value >> number ) & 0x01) ;
}

void PortEntity::setGPIOState( uint8 number, LEVEL level )
{
	uint8 mask = ( 0x01 << number );

	if( level == LEVEL::LOW )
		mask = ~mask;

	switch (portNumber)
	{
		case PORT::A: ( LEVEL::HIGH == level ) ? PORTA |= mask : PORTA &= mask; break;
		case PORT::B: ( LEVEL::HIGH == level ) ? PORTB |= mask : PORTB &= mask; break;
		case PORT::C: ( LEVEL::HIGH == level ) ? PORTC |= mask : PORTC &= mask; break;
		case PORT::D: ( LEVEL::HIGH == level ) ? PORTD |= mask : PORTD &= mask; break;
	}
}

void PortEntity::setPGIMode(uint8 number, MODE mode)
{
	uint8 mask = ( 0x01 << number );
	
	if( mode == MODE::OUTPUT )
		mask = ~mask;
		
	switch (portNumber)
	{
		case PORT::A: DDRA = DDRA & mask; break;
		case PORT::B: DDRB = DDRB & mask; break;
		case PORT::C: DDRC = DDRC & mask; break;
		case PORT::D: DDRD = DDRD & mask; break;
	}
}

void PortEntity::resetAllPINS()
{
	switch (portNumber)
	{
		case PORT::A: PORTA = 0x00; break;
		case PORT::B: PORTB = 0x00; break;
		case PORT::C: PORTC = 0x00; break;
		case PORT::D: PORTD = 0x00; break;
	}
}

void PortEntity::setAllPINS()
{
	switch (portNumber)
	{
		case PORT::A: PORTA = 0xFF; break;
		case PORT::B: PORTB = 0xFF; break;
		case PORT::C: PORTC = 0xFF; break;
		case PORT::D: PORTD = 0xFF; break;
	}
}
