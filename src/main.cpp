#include <iostream>
#include <VM.h>

using namespace Opcode;

int main() {
    // 1, 1, ADD, 1, ADD, RETURN, HALT
    char bytecodes[] = {ICONST_0, ICONST_1, ADD, PRINT, HALT};
    VM(bytecodes).run();
    return 0;
}