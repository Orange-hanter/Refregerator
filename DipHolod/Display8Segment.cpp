/* 
* Display8Segment.cpp
*
* Created: 15-Feb-19 00:25:21
* Author: Danil
*/


#include "Display8Segment.h"

// default constructor
Display8Segment::Display8Segment(uint8 A, uint8 B, uint8 C, uint8 D, PORT PortName )
{
	PortEntity pPort(PortName);
	this->port = &pPort;
	port->setPort(PortName);
	this->a = A;
	this->b = B;
	this->c = C;
	this->d = D;
	port->setPGIMode(a, MODE::OUTPUT);
	port->setPGIMode(b, MODE::OUTPUT);
	port->setPGIMode(c, MODE::OUTPUT);
	port->setPGIMode(d, MODE::OUTPUT);
} //Display8Segment

// default destructor
Display8Segment::~Display8Segment()
{
} //~Display8Segment

void Display8Segment::setNumber(short num)
{
	if ( (num >= 0) && (num < 10) )
	{
		switch ( num )
		{
			case 0: port->setGPIOState(a, LEVEL::LOW);  port->setGPIOState(b, LEVEL::LOW);	port->setGPIOState(c, LEVEL::LOW);	port->setGPIOState(d, LEVEL::LOW); break;
			case 1: port->setGPIOState(a, LEVEL::HIGH); port->setGPIOState(b, LEVEL::LOW);	port->setGPIOState(c, LEVEL::LOW);	port->setGPIOState(d, LEVEL::LOW); break;
			case 2: port->setGPIOState(a, LEVEL::LOW);  port->setGPIOState(b, LEVEL::HIGH);	port->setGPIOState(c, LEVEL::LOW);	port->setGPIOState(d, LEVEL::LOW); break;
			case 3: port->setGPIOState(a, LEVEL::HIGH); port->setGPIOState(b, LEVEL::HIGH);	port->setGPIOState(c, LEVEL::LOW);	port->setGPIOState(d, LEVEL::LOW); break;
			case 4: port->setGPIOState(a, LEVEL::LOW);  port->setGPIOState(b, LEVEL::LOW);	port->setGPIOState(c, LEVEL::HIGH);	port->setGPIOState(d, LEVEL::LOW); break;
			case 5: port->setGPIOState(a, LEVEL::HIGH); port->setGPIOState(b, LEVEL::LOW);	port->setGPIOState(c, LEVEL::HIGH);	port->setGPIOState(d, LEVEL::LOW); break;
			case 6: port->setGPIOState(a, LEVEL::LOW);	port->setGPIOState(b, LEVEL::HIGH);	port->setGPIOState(c, LEVEL::HIGH);	port->setGPIOState(d, LEVEL::LOW); break;
			case 7: port->setGPIOState(a, LEVEL::HIGH);	port->setGPIOState(b, LEVEL::HIGH);	port->setGPIOState(c, LEVEL::HIGH);	port->setGPIOState(d, LEVEL::LOW); break;
			case 8: port->setGPIOState(a, LEVEL::LOW);	port->setGPIOState(b, LEVEL::LOW);	port->setGPIOState(c, LEVEL::LOW);	port->setGPIOState(d, LEVEL::HIGH); break;
			case 9: port->setGPIOState(a, LEVEL::HIGH);	port->setGPIOState(b, LEVEL::LOW);	port->setGPIOState(c, LEVEL::LOW);	port->setGPIOState(d, LEVEL::HIGH); break;
		};
	}
	
}
