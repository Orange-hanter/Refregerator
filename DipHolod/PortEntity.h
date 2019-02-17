/* 
* PortEntity.h
*
* Created: 12-Feb-19 23:57:57
* Author: Danil
*/


#ifndef __PORTENTITY_H__
#define __PORTENTITY_H__

typedef unsigned char uint8;
enum class MODE{
	INPUT = 0,
	OUTPUT = 1
};
enum class PORT{
	A = 0,
	B,
	C,
	D
};
enum class LEVEL {
	LOW = 0,
	HIGH = 1
};

class PortEntity
{
//variables
public:
protected:

	
private:
	PORT portNumber;
	uint8 DDRPort;
	

//functions
public:
	PortEntity();
	PortEntity( PORT );
	PortEntity( unsigned int );
	~PortEntity();
	void setPort( PORT );
	LEVEL getGPIOState( uint8 number );
	bool getBGPIOState( uint8 number );
	void setGPIOState( uint8 number, LEVEL level );
	void setPGIMode( uint8 number, MODE mode );
	void resetAllPINS();
	void setAllPINS();
	
protected:
private:
	// PortEntity( const PortEntity &c );
	// PortEntity& operator=( const PortEntity &c );
	
}; //PortEntity

#endif //__PORTENTITY_H__
