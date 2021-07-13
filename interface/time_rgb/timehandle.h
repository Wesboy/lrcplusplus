#ifndef __TIME__HANDLE__H___
#define __TIME__HANDLE__H___


#include "if_typeDef.h"


typedef struct WTIME
{
    /* data */
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
}wTime;

void timeInit(void);
void timeHandle(void);

#endif
