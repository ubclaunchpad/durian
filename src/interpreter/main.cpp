#include <opcode.h>
#include <VM.h>

#include <iostream>

using namespace Opcode;

int main() {
    unsigned char bytecodes[] = {BCONST_F, DUP, BR_F, 0x02, 0x00, 0x00, 0x00, POP, BCONST_T, PRINT, HALT};
    VM(bytecodes).run();
    return 0;
}
