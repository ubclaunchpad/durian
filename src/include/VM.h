#pragma once

#include <DurianObject.h>

#include <array>

class VM {
    unsigned char *m_code;     // Pointer to bytecode
    int64_t m_pc;                  // Program Counter
    int64_t m_sp;                  // Stack Pointer
    int64_t m_fp;                  // Frame Pointer
    static const int STACK_SIZE = 256;
    std::array<DurianObject, STACK_SIZE> m_stack; // Stack
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
