#include <fcntl.h>
 
extern void exit(int code);
extern int main();
extern int _init_signal(void);

void _start() 
{
  _init_signal();
  int ex = main();
  exit(ex);
}

