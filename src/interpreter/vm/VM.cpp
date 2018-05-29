#include <VM.h>

// Duplicate of arithmetic-machine opcodes
enum opcodes {
    HALT      = 0x00, // halt
    RETURN    = 0x01, // return top value
    DCONST_1  = 0x0C, // push 1.0 onto stack

    /* arithmetic operations */
    ADD       = 0x60, // add two doubles
    SUB       = 0x61, // subtract two doubles
    MUL       = 0x62, // multiply two doubles
    DIV       = 0x64, // divide two doubles
    NEG       = 0x70, // negate an double (e.g. if -1.0 is on the stack, NEG will turn it to 1.0 on the stack)

    NOP       = 0xF0, // do nothing
};

VM::VM(char *bytecode) {
    pc = 0;
    sp = -1;
    code = bytecode;
    stack = new double[STACK_SIZE];
}

VM::~VM() {
    delete[] stack;
}

int VM::run() {
    while(1) {
        unsigned char opcode = nextBytecode();
        double a, b, v;
        switch (opcode) {
            case HALT: return 0;
            case RETURN: return (int)pop();
            case NOP: break;
            case DCONST_1:
                push(1.0);
                break;
            case ADD:
                b = pop();
                a = pop();
                push(a + b);
                break;
            case SUB:
                b = pop();
                a = pop();
                push(a - b);
                break;
            case MUL:
                b = pop();
                a = pop();
                push(a * b);
                break;
            case DIV:
                b = pop();
                a = pop();
                if (b == 0.0) return 1;
                push(a / b);
                break;
            case NEG:
                break;
            // More cases here
            default:
                // TODO: Handle when opcode is invalid. Perhaps raise error
                return 1;
        }
    }
}

// Privates

void VM::push(double v) { stack[++sp] = v; }
double VM::pop() { return stack[sp--]; }
unsigned char VM::nextBytecode() { return code[pc++]; }
