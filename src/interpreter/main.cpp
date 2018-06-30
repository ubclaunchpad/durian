#include <opcode.h>
#include <VM.h>

#include <iostream>

using namespace Opcode;

int main() {
    // Temporary bytecodes primarily used for testing
    unsigned char bytecodes[] = {BCONST_F, ICONST_1, ADD, HALT};
    VM(bytecodes).run();
    return 0;
}
