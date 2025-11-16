#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
struct termios orig_struct;

void disableRawMode(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_struct);
}

void enableRawMode(void) 
{
  tcgetattr(STDIN_FILENO,&orig_struct);
  atexit(disableRawMode);
  struct termios raw = orig_struct;
  raw.c_lflag &= ~(ECHO|ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
int main(void) {
  enableRawMode();
  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q'){
		if(iscntrl(c))
		{
			printf("%d\n",c);
		}
		else{
			printf("%d (%c)\n",c,c);
		}
	}
  return 0;
}
