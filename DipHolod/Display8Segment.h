/* 
* Display8Segment.h
*
* Created: 15-Feb-19 00:25:21
* Author: Danil
*/
#ifndef __DISPLAY8SEGMENT_H__
#define __DISPLAY8SEGMENT_H__

#include "PortEntity.h"

typedef unsigned char uint8;

class Display8Segment
{
//variables
public:
protected:
private:	
	PortEntity* port;
	uint8 a,b,c,d;
	
//functions
public:
	Display8Segment(uint8 A, uint8 B, uint8 C, uint8 D, PORT PortName );
	~Display8Segment();
	void setNumber( short num );

}; //Display8Segment

#endif //__DISPLAY8SEGMENT_H__
