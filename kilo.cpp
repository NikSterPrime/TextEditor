#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <cctype>
using namespace std;
struct termios orig_struct;

void die(const char *s){
	perror(s);
	exit(1);
}

void disableRawMode() {
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_struct) == -1){
		die("tcsetattr");
	}
}

void enableRawMode() {
    if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&orig_struct) == -1){
		die("tcsetattr");
	}
    atexit(disableRawMode);

    struct termios raw = orig_struct;
    raw.c_iflag &=~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &=~(OPOST);
    raw.c_cflag |=(CS8);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG);  // Disable echo + canonical mode
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw)==-1)die("tcsetattr");
}

int main() {
    enableRawMode();

    while (1) {
	char c = '\0';
	if(read(STDIN_FILENO,&c,1) == -1 && errno != EAGAIN) die("read");
        if (iscntrl(c)) {
            cout << (int)c << "\r\n";
        } else {
            cout << (int)c << " (" << c << ")\r\n";
        }
	if (c == 'q') break;
    }

    return 0;
}

