#include <iostream>
#include <VM.h>

int main() {
    // 1, 1, ADD, 1, ADD, RETURN, HALT
    char bytecodes[] = {0x0C, 0x0C, 0x60, 0x0C, 0x60, 0x01, 0x00};
    std::cout << VM(bytecodes).run();
    return 0;
}