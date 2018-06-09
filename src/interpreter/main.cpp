#include <opcode.h>
#include <VM.h>

#include <iostream>

using namespace Opcode;

int main() {
    unsigned char bytecodes[] = {DCONST, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x3F, PRINT, HALT};
    VM(bytecodes).run();
    return 0;
}