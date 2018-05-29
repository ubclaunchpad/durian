#pragma once

#ifndef DURIAN_VM_H
#define DURIAN_VM_H


class VM {
    public:
        VM(char *);
        ~VM();
        int run();
    private:
        int pc;         // Program Counter
        int sp;         // Stack Pointer
        char* code;     // Pointer to bytecode
        double* stack;  // Stack
        const int STACK_SIZE = 256;

        void push(double);
        double pop();
        unsigned char nextBytecode();
};

#endif //DURIAN_VM_H
