#pragma once

#include <DurianObject.h>
#include <Types.h>

#include <array>

class VM {
    Bytecode* m_code;     // Pointer to bytecode
    BytecodeIndex m_pc;                  // Program Counter
    BytecodeIndex m_sp;                  // Stack Pointer
    BytecodeIndex m_fp;                  // Frame Pointer
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
