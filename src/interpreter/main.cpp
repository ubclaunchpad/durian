#include <iostream>
#include "../include/VM.h"
#include "../include/opcode.h"

using namespace Opcode;

int main() {
    // 1, 1, ADD, 1, ADD, RETURN, HALT
    unsigned char bytecodes[] = {ICONST_0, ICONST_1, ADD, PRINT, HALT};
    VM(bytecodes).run();
    return 0;
}