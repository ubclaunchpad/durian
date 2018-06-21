#include <opcode.h>
#include <VM.h>

#include <iostream>

using namespace Opcode;

int main() {
    unsigned char bytecodes[] = {HALT};
    VM(bytecodes).run();
    return 0;
}
