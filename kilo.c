#include <terminos.h>
#include <unistd.h>

void enableraw()
{
	struct terminos raw;

	tcgetattr(STDIN_FILENO,&raw);
	raw.c_lflag& = ~(ECHO);
	tcsetattr(STDIN_FILENO,&raw);
}
int main()
{
	enableraw();
	char c;
	while(read(STDIN_FILENO,&c,1)==1 && c!='q');
	return 0;
}
