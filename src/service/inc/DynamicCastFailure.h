#ifndef _CDynamicCastFailure_h_included_
#define _CDynamicCastFailure_h_included_

#include "ExceptionSource.h"
	  
class CDynamicCastFailure: public CExceptionSource
{
public: 
	CDynamicCastFailure(unsigned short errorcode, const CSource& src,unsigned char package_id);	
};

#endif