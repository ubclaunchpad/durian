#pragma once

#include <DurianObject.h>

#include <array>

class VM {
    unsigned char *m_code;     // Pointer to bytecode
    int m_pc;                  // Program Counter
    int m_sp;                  // Stack Pointer
    static const int STACK_SIZE = 256;
    std::array<DurianObject, STACK_SIZE> m_stack; //stack
public:
    VM(unsigned char *);
    ~VM() = default;
    int run();
private:
    void push(DurianObject);
    DurianObject pop();
    unsigned char nextBytecode();
    void typeError(const char *operand, DurianObject a);
    void typeError(const char *operand, DurianObject a, DurianObject b);
};
