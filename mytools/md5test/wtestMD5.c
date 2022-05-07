#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define C_FILE_MAX  128
#define FILE_NAME 128  //文件名字长度
#define TEMP_FILE_DATE_NAME_LEN 32

static bool gQuit = false;
static int mode = 0;

static FILE *fp[C_FILE_MAX];
static int fp_index = 0;
char filename[FILE_NAME];


int getFileName(char *pDate, int len)
{
    int ret = -1;
    if(pDate != NULL && (len >= TEMP_FILE_DATE_NAME_LEN))
    {
        time_t temp;
        struct tm *p;
        time(&temp);
        p=localtime(&temp);
        sprintf(pDate, "%02d%02d%02d%02d%02d%02d.wet", (1900+p->tm_year)%100,1+p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
        ret = 1;
    }
    return ret;
}

//生成文件和MD5码
void generateFile()
{
        //创建新文件，如果存在，重新创建
    // memcpy(filename, "", );
    // fp[fp_index] = fopen(, "w");
    memset(filename, 0, FILE_NAME*sizeof(char));
    getFileName(filename, TEMP_FILE_DATE_NAME_LEN);
    if(filename != NULL && fp != NULL && fp_index < C_FILE_MAX)
    {
        fp[fp_index] = fopen(filename, "w");
        if(fp[fp_index] == NULL)
        {
            fprintf(stderr, "generate file fopen failed!!! index%d \n", fp_index);
            exit(0);
        }
        fprintf(stdout, "generate file :%s\n", filename);
        mode = 1; //生成文件

    }
    
}

static void handle_signal(int signo)
{
    fprintf(stdout, "signal:%d\n", signo);
    switch (signo) {
        case SIGINT:
            fprintf(stdout, "signal int \n");
            gQuit = true;
            break;
        case SIGQUIT:
            // suspend = true;
            // quit = true;

            gQuit = true;
            fprintf(stdout, "signQuit\n");
            break;
        case SIGSTOP:
            // suspend = true;
            gQuit = true;
            fprintf(stdout, "signStop\n");
            break;
        case SIGCONT:
            // suspend = false;
            fprintf(stdout, "signCon\n");
            break;
    }
}


/*
 * Set the signal handler:
 * SIGQUIT: Reset debugfs and tracing property and terminate the daemon.
 * SIGSTOP: Stop logging and suspend the daemon.
 * SIGCONT: Resume the daemon as normal.
 * SIGUSR1: Dump the logging to a compressed format for systrace to visualize.
 */
static void register_sighandler(void)
{
    struct sigaction sa;
    sigset_t block_mask;

    sigemptyset(&block_mask);
    sigaddset (&block_mask, SIGQUIT);
    sigaddset (&block_mask, SIGSTOP);
    sigaddset (&block_mask, SIGCONT);
    sigaddset (&block_mask, SIGKILL);
    sigaddset (&block_mask, SIGINT);

    sa.sa_flags = 0;
    sa.sa_mask = block_mask;
    sa.sa_handler = handle_signal;
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGSTOP, &sa, NULL);
    sigaction(SIGCONT, &sa, NULL);
    sigaction(SIGKILL, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
}

static void show_help(void) {

    fprintf(stderr, "usage: wtestMD5 [options] [categoris...]\n");
    fprintf(stdout, "Options includes:\n"
                    "   -a appname  enable app-level tracing for a comma "
                       "separated list of cmdlines\n"
                    "   -h          show helps\n");
    exit(0);
}


static int get_options(int argc, char *argv[]) {
    int opt = 0;

    while ((opt = getopt(argc, argv, "a:g:h")) >= 0) {
        switch(opt) {
            case 'a':
                
                break;
            case 'g':
                //生成文件和MD5
                generateFile();
                break;
            case 'h':
                show_help();
                break;
            default:
                fprintf(stderr, "Error in getting options.\n"
                        "run \"%s -h\" for usage.\n", argv[0]);
                return 1;
        }
    }

    return 0;
}



int main(int argc, char *argv[])
{
    fprintf(stdout, "test start\n");
    if(get_options(argc, argv) != 0)
        return 1;
    fprintf(stdout, "test get opt\n");

    // if (daemon(0, 0) != 0)
    //     return 1;
    fprintf(stdout, "test daemon ok\n");

    register_sighandler();

    while(!gQuit)
    {
        if()
    }

    return 0;
}


