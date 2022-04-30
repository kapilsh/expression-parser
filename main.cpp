#include <iostream>
#include <unistd.h>
#include <termios.h>

void HideStdinKeystrokes()
{
    termios tty{};
    tcgetattr(STDIN_FILENO, &tty);
    /* we want to disable echo */
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void ShowStdinKeystrokes()
{
    termios tty{};
    tcgetattr(STDIN_FILENO, &tty);
    /* we want to reenable echo */
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

int main() {
    HideStdinKeystrokes();
    std::cout << "==========================" << '\n';
    std::cout << "Welcome to SilverLang REPL" << '\n';
    std::cout << "==========================" << '\n';
    while (true) {
        std::string command;
        std::cout << "[silver]>> ";
        std::getline(std::cin, command);
        if (command == "exit()") {
            break;
        }
        else if (command.empty() or command == " "){
            continue;
        }
        else {
            std::cout << "INVALID COMMAND " << command << '\n';
        }
    }
    ShowStdinKeystrokes();
    return 0;
}
