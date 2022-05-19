#pragma once

namespace silver::repl {
    void HideStdinKeystrokes() {
        termios tty{};
        tcgetattr(STDIN_FILENO, &tty);
        /* we want to disable echo */
        tty.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    }

    void ShowStdinKeystrokes() {
        termios tty{};
        tcgetattr(STDIN_FILENO, &tty);
        /* we want to reenable echo */
        tty.c_lflag |= ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    }
}
