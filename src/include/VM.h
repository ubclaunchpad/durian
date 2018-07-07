#pragma once

#include <DurianObject.h>

class VM {
    public:
        VM(unsigned char *);
        ~VM();
        int run();
    private:
        int m_pc;                  // Program Counter
        int m_sp;                  // Stack Pointer
        unsigned char *m_code;     // Pointer to bytecode
        static const int STACK_SIZE = 256;
        DurianObject stack[STACK_SIZE];      // Stack
        void push(DurianObject);
        DurianObject pop();
        unsigned char nextBytecode();
        void typeError(const char *operand, DurianObject a);
        void typeError(const char *operand, DurianObject a, DurianObject b);
};
