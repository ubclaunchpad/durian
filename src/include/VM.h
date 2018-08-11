#pragma once

#include <DurianObject.h>
#include <Types.h>

#include <array>

class VM {
    Bytecode* m_code;     // Pointer to bytecode
    BytecodePointer m_pc;                  // Program Counter
    BytecodePointer m_sp;                  // Stack Pointer
    BytecodePointer m_fp;                  // Frame Pointer
    static const int STACK_SIZE = 256;
    std::array<DurianObject, STACK_SIZE> m_stack; // Stack
public:
    VM(Bytecode*);
    ~VM() = default;
    int run();
private:
    void push(DurianObject);
    DurianObject pop();
    Bytecode nextBytecode();
    void typeError(const char *operand, DurianObject a);
    void typeError(const char *operand, DurianObject a, DurianObject b);
};
