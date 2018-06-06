#include <opcode.h>
#include <VM.h>

#include <iostream>

using namespace Opcode;

int main() {
    unsigned char bytecodes[] = {ICONST_0, ICONST_1, ADD, PRINT, HALT};
    VM(bytecodes).run();
    return 0;
}