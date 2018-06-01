#pragma once

#include <DurianObject.h>

#ifndef DURIAN_VM_H
#define DURIAN_VM_H


class VM {
    public:
        VM(unsigned char *);
        ~VM();
        int run();
    private:
        int pc;                  // Program Counter
        int sp;                  // Stack Pointer
        unsigned char *code;     // Pointer to bytecode
        DurianObject stack;      // Stack
        const int STACK_SIZE = 256;
        void push(DurianObject);
        DurianObject pop();
        unsigned char nextBytecode();
};

#endif //DURIAN_VM_H
