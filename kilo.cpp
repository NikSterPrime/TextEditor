#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cctype>
using namespace std;
struct termios orig_struct;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_struct);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_struct);
    atexit(disableRawMode);

    struct termios raw = orig_struct;
    raw.c_lflag &= ~(ECHO | ICANON);  // Disable echo + canonical mode

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enableRawMode();

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        if (iscntrl(static_cast<unsigned char>(c))) {
            cout << (int)c << "\n";
        } else {
            cout << (int)c << " (" << c << ")\n";
        }
    }

    return 0;
}

