#pragma once

namespace Opcode {
    // Note: this is a raw enum, instead of an enum struct, because we need to be able to treat these as raw characters.
    enum : unsigned char {
        NOP      = 0x00, // pass.
        ICONST   = 0x02, // push next 8 bytes onto stack as integer constant.
        ICONST_0 = 0x04, // push literal int(0) onto stack.
        ICONST_1 = 0x05, // push literal int(1) onto stack.
        DCONST   = 0x0A, // push next 8 bytes onto stack as double constant.
        BCONST_F = 0x0E, // push literal bool(false) onto stack.
        BCONST_T = 0x0F, // push literal bool(true) onto stack.
        DUP      = 0x58, // duplicate top of stack.
        POP      = 0x5F, // pops top of stack.
        ADD      = 0x60, // pop top two elements, add, push result
        // reserved for modulo
        SUB      = 0x62, // pop top two elements, subtract, push result
        MUL      = 0x63, // pop top two elements, multiply, push result
        FDIV     = 0x64, // pop top two elements, divide, push result as a double
        // reserved for exponentiation
        // reserved for integer division
        CNCT     = 0x66, // pop top two elements, stringify both, concatenate, push result
        EQ       = 0x67, // pops two elements, checks if they are equal
        NEQ      = 0x68, // pops two elements, checks if they are not equal
        GT       = 0x69, // pops two elements, checks if bottom > top, push result
        GE       = 0x6A, // pops two elements, checks if bottom >= top, push result
        NEG      = 0x70, // pop top element, coerce to number, negate, push result
        POS      = 0x71, // pop top element, coerce to number, push result
        NOT      = 0x72, // pop top element, check truthiness, negate, push result
        STRFY    = 0x73, // pop top element, stringify, push result
        BR_F     = 0x93, // pops the top of the stack, then branches if it is false. (takes next 4 bytes as jump length)
        NEWSTR8  = 0xBB, // make new String (length: 8 bytes, value: length bytes) and push it onto stack
        PRINT    = 0xF0, // print top of stack to stdout with newline, discarding top of stack.
        ERR      = 0xF1, // print top of stack to stderr with newline, discarding top of stack.
        SCAN     = 0xF2, // read line from stdin and push
        HALT     = 0xFF, // halt.
    };
}

