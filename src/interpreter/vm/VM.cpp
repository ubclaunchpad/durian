#include <VM.h>

#include <debug.h>
#include <DurianObject.h>
#include <opcode.h>

#include <cstdlib>
#include <iostream>


// Public

VM::VM(unsigned char *bytecode) :
    m_code(bytecode),
    m_pc(0),
    m_sp(0),
    m_fp(0) {
    // Do nothing.
}

int VM::run() {
    while(true) {
        unsigned char opcode = nextBytecode();
        DURIAN_DEBUG_LOG("%x\n", opcode);
        DurianObject a, b;
        int32_t jumpLen; // Jump length
        unsigned char *p_headerStr; // String (length: 8 bytes, value: length bytes) pointer
        unsigned char *p_fnAddress; // Function Address
        switch (opcode) {
            case Opcode::HALT: return 0;
            case Opcode::NOP: break;
            case Opcode::NEWSTR8:
                p_headerStr = m_code + *reinterpret_cast<int32_t*>(m_code + m_pc); // m_code + headerOffset
                m_pc += sizeof(int32_t);
                push(DurianObject(*reinterpret_cast<int32_t*>(p_headerStr), p_headerStr + sizeof(int32_t)));
                break;
            case Opcode::ICONST:
                push(DurianObject(*reinterpret_cast<int64_t*>(m_code+m_pc)));
                m_pc += sizeof(int64_t);
                break;
            case Opcode::ICONST_0:
                push(DurianObject((int64_t)0));
                break;
            case Opcode::ICONST_1:
                push(DurianObject((int64_t)1));
                break;
            case Opcode::DCONST:
                push(DurianObject(*reinterpret_cast<double*>(m_code+m_pc)));
                m_pc += sizeof(double);
                break;
            case Opcode::BCONST_F:
                push(DurianObject(false));
                break;
            case Opcode::BCONST_T:
                push(DurianObject(true));
                break;
            case Opcode::FCONST:
                p_fnAddress = m_code + *reinterpret_cast<int64_t*>(m_code+m_pc);
                m_pc += sizeof(int64_t);
                push(DurianObject(*reinterpret_cast<int8_t*>(p_fnAddress), p_fnAddress + sizeof(int8_t)));
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
                    push(DurianObject(a.value.ival + b.value.ival));
                } else if (a.type == DurianType::Integer && b.type == DurianType::Double) {
                    push(DurianObject(a.value.ival + b.value.dval));
                } else if (a.type == DurianType::Double && b.type == DurianType::Integer) {
                    push(DurianObject(a.value.dval + b.value.ival));
                } else if (a.type == DurianType::Double && b.type == DurianType::Double) {
                    push(DurianObject(a.value.dval + b.value.dval));
                } else {
                    typeError("+", a, b);
                    exit(EXIT_FAILURE);
                }
                break;
            case Opcode::SUB:
                b = pop();
                a = pop();
                if (a.type == DurianType::Integer && b.type == DurianType::Integer) {
                    push(DurianObject(a.value.ival - b.value.ival));
                } else if (a.type == DurianType::Integer && b.type == DurianType::Double) {
                    push(DurianObject(a.value.ival - b.value.dval));
                } else if (a.type == DurianType::Double && b.type == DurianType::Integer) {
                    push(DurianObject(a.value.dval - b.value.ival));
                } else if (a.type == DurianType::Double && b.type == DurianType::Double) {
                    push(DurianObject(a.value.dval - b.value.dval));
                } else {
                    typeError("-", a, b);
                    exit(EXIT_FAILURE);
                }
            case Opcode::MUL:
                b = pop();
                a = pop();
                if (a.type == DurianType::Integer && b.type == DurianType::Integer) {
                    push(DurianObject(a.value.ival * b.value.ival));
                } else if (a.type == DurianType::Integer && b.type == DurianType::Double) {
                    push(DurianObject(a.value.ival * b.value.dval));
                } else if (a.type == DurianType::Double && b.type == DurianType::Integer) {
                    push(DurianObject(a.value.dval * b.value.ival));
                } else if (a.type == DurianType::Double && b.type == DurianType::Double) {
                    push(DurianObject(a.value.dval * b.value.dval));
                } else {
                    typeError("*", a, b);
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
                    push(DurianObject((double)a.value.ival / (double)b.value.ival));
                } else if (a.type == DurianType::Integer && b.type == DurianType::Double) {
                    push(DurianObject(a.value.ival / b.value.dval));
                } else if (a.type == DurianType::Double && b.type == DurianType::Integer) {
                    push(DurianObject(a.value.dval / b.value.ival));
                } else if (a.type == DurianType::Double && b.type == DurianType::Double) {
                    push(DurianObject(a.value.dval / b.value.dval));
                } else {
                    typeError("/", a, b);
                    exit(EXIT_FAILURE);
                }
            case Opcode::NEG:
                a = pop();
                if (a.type == DurianType::Integer) {
                    push(DurianObject(-a.value.ival));
                } else if (a.type == DurianType::Double) {
                    push(DurianObject(-a.value.dval));
                } else {
                    typeError("-", a);
                    exit(EXIT_FAILURE);
                }
                break;
            case Opcode::NOT:
                a = pop();
                if (a.type == DurianType::Boolean) {
                    push(DurianObject(!a.value.bval));
                } else {
                    typeError("!", a);
                    exit(EXIT_FAILURE);
                }
                break;
            case Opcode::CNCT:
                b = pop();
                a = pop();
                if (a.type == DurianType::String && b.type == DurianType::String) {
                    push(DurianObject(a.value.sval.m_len /* + b.value.sval.m_len */, a.value.sval.p_val /* TODO: Implement concat string */));
                } else {
                    typeError("&", a, b);
                    exit(EXIT_FAILURE);
                }
            case Opcode::BR_F:
                a = pop();
                jumpLen = *reinterpret_cast<int32_t*>(m_code+m_pc);
                m_pc += sizeof(int32_t);
                if (a.isFalsy()) {
                    m_pc += jumpLen;
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
                    printf("%.*s\n", a.value.sval.m_len, a.value.sval.p_val);
                else if (a.type == DurianType::Function)
                    printf("TODO: Implement print for function type");
                else {
                    typeError("print", a);
                    exit(EXIT_FAILURE);
                }
                break;
            case Opcode::CALL:
                push(DurianObject(m_fp));
                push(DurianObject(m_pc));
                m_fp = m_sp;
                break;
            case Opcode::RET:
                a = pop(); // return value
                m_sp = m_fp;
                m_pc = pop().value.ival;
                m_fp = pop().value.ival;
                b = pop(); // Function DurianObject
                for (int i = 0; i < b.value.fval.m_len; i++) {
                    pop();
                }
                push(a);
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
    m_stack[++m_sp] = v;
}

DurianObject VM::pop() {
    return m_stack[m_sp--];
}

unsigned char VM::nextBytecode() {
    return m_code[m_pc++];
}

void VM::typeError(const char *operand, DurianObject a) {
    std::cout << "TypeError: Invalid operand type for " << operand << ": "
              << a.type
              << "." << std::endl;
}

void VM::typeError(const char *operand, DurianObject a, DurianObject b) {
    std::cout << "TypeError: Invalid operand type for " << operand << ": "
              << a.type
              << " and "
              << b.type
              << "." << std::endl;
}
