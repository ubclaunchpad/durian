#include <VM.h>
#include <opcode.h>


// Public

VM::VM(unsigned char *bytecode) {
    pc = 0;
    sp = -1;
    code = bytecode;
    stack = malloc(STACK_SIZE * sizeof(DurianObject));
}

VM::~VM() {
    free(code);
    free(stack);
}

int VM::run() {
    while(true) {
        unsigned char opcode = nextBytecode();
        DurianObject a, b, v;
        switch (opcode) {
            case Opcode::HALT: return 0;
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
                a = pop();
                push(-a);
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

double VM::pop() {
    return stack[sp--];
}

unsigned char VM::nextBytecode() {
    return code[pc++];
}
