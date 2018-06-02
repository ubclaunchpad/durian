#include <VM.h>
#include <opcode.h>
#include <cstdlib>
#include <DurianObject.h>
#include <iostream>


// Public

VM::VM(unsigned char *bytecode) {
    pc = 0;
    sp = -1;
    code = bytecode;
}

VM::~VM() {
    free(code);
    free(stack);
}

int VM::run() {
    //DurianObject a, b, v;
    while(true) {
        unsigned char opcode = nextBytecode();
        DurianObject a, b;
        switch (opcode) {
            case Opcode::HALT: return 0;
            case Opcode::NOP: break;
            case Opcode::ICONST_0:
                push((int64_t)0);
                break;
            case Opcode::ICONST_1:
                push((int64_t)1);
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
                if (b.type == DurianType::Integer && b.value.ival == 0 ||
                    b.type == DurianType::Double && b.value.dval == 0.0) {
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
                }
                break;
            case Opcode::PRINT:
                a = pop();
                if (a.type == DurianType::Integer)
                    std::cout << a.value.ival << std::endl;
                else if (a.type == DurianType::Double)
                    std::cout << a.value.dval << std::endl;
                else
                    std::cout << "Unknown Type";
                break;
            // More cases here
            default:
                // TODO: Handle when opcode is invalid. Perhaps raise error
                return 1;
        }
    }
}

// Private

void VM::push(DurianObject v) {
    stack[++sp] = v;
}

DurianObject VM::pop() {
    return stack[sp--];
}

unsigned char VM::nextBytecode() {
    return code[pc++];
}
