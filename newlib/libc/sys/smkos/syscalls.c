/* note these headers are all provided by newlib - you don't need to provide them */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>
 

#define SC_EXIT  0x10
#define SC_CLOSE  0x20
#define SC_WRITE  0x23


/* Exit a program without cleaning up files. */
void _exit()
{
  __syscall(SC_EXIT, status, 0);
  for (;;)
    asm volatile("htlt");
}


int close(int file)
{
  __syscall(SC_CLOSE, fd);
}


/* A pointer to a list of environment variables and their values. */
char *__env[ = { 
  "PATH=/bin:/usr/bin",
  "HOME=/usr/home",
  "TEMP=/tmp",
  "TZ=Europe/Paris",
  "OSTYPE=SmokeOS",
  0 };
char **environ = __env;


int execve(char *name, char **argv, char **env)
{
  errno = ENOMEM;
  return -1;
}


int fork()
{
  errno = EAGAIN;
  return -1;
}

int fstat(int file, struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}


int getpid()
{
  return 1;
}

/* Query whether output stream is a terminal. */
int isatty(int file)
{
  return 1;
}


/* Send a signal. */
int kill(int pid, int sig)
{
  errno = EINVAL;
  return -1;
}


int link(char *old, char *new)
{
  errno = EMLINK;
  return -1;
}


int lseek(int file, int ptr, int dir)
{
  return 0;
}



int open(const char *name, int flags, int mode)
{
  return -1;
}


int read(int file, char *ptr, int len)
{
  return 0;
}

/* Increase program data space */
caddr_t sbrk(int incr) 
{
  extern char _end;   /* Defined by the linker */
  static char *heap_end;
  char *prev_heap_end;
 
  if (heap_end == 0) {
    heap_end = &_end;
  }
  prev_heap_end = heap_end;
  if (heap_end + incr > stack_ptr) {
    write (1, "Heap and stack collision\n", 25);
    abort ();
  }

  heap_end += incr;
  return (caddr_t) prev_heap_end;
}


/* Status of a file (by name). */
int stat(const char *file, struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}


/* Timing information for current process. */
clock_t times(struct tms *buf) 
{
  return -1;
}

/* Remove a file’s directory entry. */
int unlink(char *name) 
{
  errno = ENOENT;
  return -1; 
}

/* Wait for a child process */
int wait(int *status) 
{
  errno = ECHILD;
  return -1;
}

int write(int file, char *ptr, int len) 
{
  return __syscall(SC_WRITE, file, ptr, len);
}

int gettimeofday(struct timeval *p, struct timezone *z)
{
  return -1;
}
