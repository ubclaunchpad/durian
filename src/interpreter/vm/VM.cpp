#include <VM.h>

#include <debug.h>
#include <DurianObject.h>
#include <opcode.h>

#include <cstdlib>
#include <iostream>


// Public

VM::VM(unsigned char *bytecode) :
    m_pc(0),
    m_sp(-1),
    m_code(bytecode) {
    // Do nothing.
}

VM::~VM() {}


int VM::run() {
    while(true) {
        unsigned char opcode = nextBytecode();
        DURIAN_DEBUG_LOG("%x\n", opcode);
        DurianObject a, b;
        int32_t jump_len; // Jump length
        unsigned char *p_str; // String (length: 8 bytes, value: length bytes) pointer
        switch (opcode) {
            case Opcode::HALT: return 0;
            case Opcode::NOP: break;
            case Opcode::NEWSTR8:
                p_str = m_code + *reinterpret_cast<int32_t*>(m_code + m_pc); // m_code + headerOffset
                m_pc += sizeof(int32_t);
                push(DurianObject(*reinterpret_cast<int32_t*>(p_str), p_str + sizeof(int32_t)));
                break;
            case Opcode::ICONST:
                push(*reinterpret_cast<int64_t*>(m_code+m_pc));
                m_pc += sizeof(int64_t);
                break;
            case Opcode::ICONST_0:
                push((int64_t)0);
                break;
            case Opcode::ICONST_1:
                push((int64_t)1);
                break;
            case Opcode::DCONST:
                push(*reinterpret_cast<double*>(m_code+m_pc));
                m_pc += sizeof(double);
                break;
            case Opcode::BCONST_F:
                push(false);
                break;
            case Opcode::BCONST_T:
                push(true);
                break;
            case Opcode::DUP:
                a = pop();
                push(a);
                push(a);
                break;
            case Opcode::POP:
                pop();
                break;
            case Opcode::ADD:
                b = pop();
                a = pop();
                if (a.type == DurianType::Integer && b.type == DurianType::Integer) {
                    push(a.value.ival + b.value.ival);
                } else if (a.type == DurianType::Integer && b.type == DurianType::Double) {
                    push(a.value.ival + b.value.dval);
                } else if (a.type == DurianType::Double && b.type == DurianType::Integer) {
                    push(a.value.dval + b.value.ival);
                } else if (a.type == DurianType::Double && b.type == DurianType::Double) {
                    push(a.value.dval + b.value.dval);
                } else {
                    std::cout << "TypeError: Invalid operand types for +: "
                              << a.type
                              << " and "
                              << b.type
                              << "." << std::endl;
                    exit(EXIT_FAILURE);
                }
                break;
            case Opcode::SUB:
                b = pop();
                a = pop();
                if (a.type == DurianType::Integer && b.type == DurianType::Integer) {
                    push(a.value.ival - b.value.ival);
                } else if (a.type == DurianType::Integer && b.type == DurianType::Double) {
                    push(a.value.ival - b.value.dval);
                } else if (a.type == DurianType::Double && b.type == DurianType::Integer) {
                    push(a.value.dval - b.value.ival);
                } else if (a.type == DurianType::Double && b.type == DurianType::Double) {
                    push(a.value.dval - b.value.dval);
                } else {
                    std::cout << "TypeError: Invalid operand types for -: "
                            << a.type
                            << " and "
                            << b.type
                            << "." << std::endl;
                    exit(EXIT_FAILURE);
                }
            case Opcode::MUL:
                b = pop();
                a = pop();
                if (a.type == DurianType::Integer && b.type == DurianType::Integer) {
                    push(a.value.ival * b.value.ival);
                } else if (a.type == DurianType::Integer && b.type == DurianType::Double) {
                    push(a.value.ival * b.value.dval);
                } else if (a.type == DurianType::Double && b.type == DurianType::Integer) {
                    push(a.value.dval * b.value.ival);
                } else if (a.type == DurianType::Double && b.type == DurianType::Double) {
                    push(a.value.dval * b.value.dval);
                } else {
                    std::cout << "TypeError: Invalid operand types for *: "
                            << a.type
                            << " and "
                            << b.type
                            << "." << std::endl;
                    exit(EXIT_FAILURE);
                }
            case Opcode::FDIV:
                b = pop();
                a = pop();
                if ((b.type == DurianType::Integer && b.value.ival == 0) ||
                    (b.type == DurianType::Double && b.value.dval == 0.0)) {
                    std::cout << "DivisionByZeroError." << std::endl;
                }
                if (a.type == DurianType::Integer && b.type == DurianType::Integer) {
                    push((double)a.value.ival / (double)b.value.ival);
                } else if (a.type == DurianType::Integer && b.type == DurianType::Double) {
                    push(a.value.ival / b.value.dval);
                } else if (a.type == DurianType::Double && b.type == DurianType::Integer) {
                    push(a.value.dval / b.value.ival);
                } else if (a.type == DurianType::Double && b.type == DurianType::Double) {
                    push(a.value.dval / b.value.dval);
                } else {
                    std::cout << "TypeError: Invalid operand types for /: "
                            << a.type
                            << " and "
                            << b.type
                            << "." << std::endl;
                    exit(EXIT_FAILURE);
                }
            case Opcode::NEG:
                a = pop();
                if (a.type == DurianType::Integer) {
                    push(-a.value.ival);
                } else if (a.type == DurianType::Double) {
                    push(-a.value.dval);
                } else {
                    std::cout << "TypeError: Invalid operand type for -: "
                              << a.type
                              << "." << std::endl;
                    exit(EXIT_FAILURE);
                }
                break;
            case Opcode::NOT:
                a = pop();
                if (a.type == DurianType::Boolean) {
                    push(!a.value.bval);
                } else {
                    std::cout << "TypeError: Invalid operand type for !: "
                              << a.type
                              << "." << std::endl;
                    exit(EXIT_FAILURE);
                }
                break;
            case Opcode::CNCT:
                b = pop();
                a = pop();
                if (a.type == DurianType::String && b.type == DurianType::String) {
                    push(DurianObject(a.value.sval.len /* + b.value.sval.len */, a.value.sval.val /* TODO: Implement concat string */));
                } else {
                    std::cout << "TypeError: Invalid operand types for &: "
                              << a.type
                              << " and "
                              << b.type
                              << "." << std::endl;
                    exit(EXIT_FAILURE);
                }
            case Opcode::BR_F:
                a = pop();
                jump_len = *reinterpret_cast<int32_t*>(m_code+m_pc);
                m_pc += sizeof(int32_t);
                if (a.isFalsy()) {
                    m_pc += jump_len;
                }
                break;
            case Opcode::PRINT:
                a = pop();
                if (a.type == DurianType::Integer)
                    std::cout << a.value.ival << std::endl;
                else if (a.type == DurianType::Double)
                    printf("%f\n", a.value.dval);
                else if (a.type == DurianType::Boolean)
                    std::cout << (a.value.bval ? "True" : "False") << std::endl;
                else if (a.type == DurianType::String)
                    printf("%.*s\n", a.value.sval.len, a.value.sval.val);
                else {
                    std::cout << "TypeError: Invalid operand types for print: "
                              << a.type
                              << "." << std::endl;
                    exit(EXIT_FAILURE);
                }
                break;
            // More cases here
            default:
                // TODO: Handle when opcode is invalid. Perhaps raise error
                exit(EXIT_FAILURE);
        }
    }
}

// Private

void VM::push(DurianObject v) {
    stack[++m_sp] = v;
}

DurianObject VM::pop() {
    return stack[m_sp--];
}

unsigned char VM::nextBytecode() {
    return m_code[m_pc++];
}
