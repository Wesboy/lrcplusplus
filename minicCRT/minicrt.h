#ifndef __MINI_CRT__H__
#define __MINI_CRT__H__


typedef int FILE;
#define EOF -1

#ifdef WIN32
#define stdin ((FILE *)(GetStdHandle(STD_INPUT_HANDLE)))
#define stdout ((FILE *)(GetStdHandle(STD_OUTPUT_HANDLE)))
#define stderr ((FILE *)(GetStdHandle(STD_ERROR_HANDLE)))
#else
#define stdin ((FILE *)0)
#define stdout ((FILE *)1)
#define stderr ((FILE *)2)
#endif


extern int mini_crt_heap_init(void);
extern void *malloc(unsigned size);
extern void free(void *ptr);

#endif