#include <opcode.h>
#include <VM.h>

#include <iostream>

using namespace Opcode;

int main() {
    unsigned char bytecodes[] = {BCONST_T, NOT, PRINT, HALT};
    VM(bytecodes).run();
    return 0;
}