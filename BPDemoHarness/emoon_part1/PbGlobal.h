#ifndef _PBGLOBAL_H_
#define _PBGLOBAL_H_

/////////////////////////////////////////////////////////////////////
// misc stuff from harness
/////////////////////////////////////////////////////////////////////

#include <tamtypes.h> 	
#include "../harness.h" // dependent on tamtypes
extern const demo_init_t* gp_Info; // nice

/////////////////////////////////////////////////////////////////////
// output stuff, made with intention of being fast to type 
/////////////////////////////////////////////////////////////////////

void out( const char* pString, ... );
const char* PbGlobal_GetAsBits32( unsigned int value );

#define line out( "LINE: %d\n", __LINE__ );

#endif //_PBGLOBAL_H_
