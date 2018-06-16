#ifndef DEBUG_OUT_H
#define DEBUG_OUT_H

class DebugMsg
{
private:
	static char DebugBuff[256];

public:
	static void out( char* A, ...);
};



#endif