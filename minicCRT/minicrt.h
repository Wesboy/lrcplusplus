#ifndef __MINI_CRT__H__
#define __MINI_CRT__H__

#ifdef __cplusplus
extern "c"{
#endif


typedef int FILE;
#define EOF (-1)

#ifndef NULL
#define NULL (0)
#endif

#ifdef WIN32
#define stdin ((FILE *)(GetStdHandle(STD_INPUT_HANDLE)))
#define stdout ((FILE *)(GetStdHandle(STD_OUTPUT_HANDLE)))
#define stderr ((FILE *)(GetStdHandle(STD_ERROR_HANDLE)))
#else
#define stdin ((FILE *)0)
#define stdout ((FILE *)1)
#define stderr ((FILE *)2)
#endif

//string
extern char *itoa(int n, char *str, int radix);
extern int strcmp(const char *src, const char *dst);
extern char *strcpy(char *dst, const char *src);
extern unsigned strlen(const char *str);

//print
extern int fputc(int c, FILE *stream);
extern int fputs(const char *str, FILE *stream);
extern int printf(const char *format, ...);
extern int fprinf(FILE *stream, const char *format, ...);

//stdio
extern int mini_crt_io_init();
extern FILE *fopen(const char *filename, const char *mode);
extern int fread(void *buf, int size, int count, FILE *stream);
extern int fwrite(const void *buf, int size, int count, FILE *stream);
extern int fclose(FILE *fp);
extern int fseek(FILE *fp, int offset, int set);


//heap
extern int mini_crt_heap_init(void);
extern void *malloc(unsigned size);
extern void free(void *ptr);


void do_global_ctors();
void mini_crt_call_exit_routine();

//atexit
typedef void (*atexit_func_t)(void);
int atexit(atexit_func_t func);

#ifdef __cplusplus
}
#endif

#endif