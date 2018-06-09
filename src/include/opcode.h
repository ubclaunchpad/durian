#pragma once

namespace Opcode {
    // Note: this is a raw enum, instead of an enum struct, because we need to be able to treat these as raw characters.
    enum : unsigned char {
      NOP       = 0x00,  // pass
      ICONST    = 0x02,  // push next 8 bytes onto stack as integer constant.
      ICONST_0  = 0x04,  // push literal int(0) onto stack.
      ICONST_1  = 0x05,  // push literal int(1) onto stack.
      DCONST    = 0x0A,  // push next 8 bytes onto st4ack as double constant.
      BCONST_F  = 0x0E,  // push literal bool(false) onto stack.
      BCONST_T  = 0x0F,  // push literal bool(true) onto stack.
      DUP       = 0x58,  // duplicate top of stack.
      POP       = 0x5F,  // pops top of stack.
      ADD       = 0x60,  // add top two elements on stack, push result back onto stack.
      SUB       = 0x61,  // subtract top two elements on stack, push result back onto stack.
      MUL       = 0x62,  // multiply top two elements on stack, push result back onto stack.
      FDIV      = 0x64,  // divide top two elements on stack, push result back onto stack as a double.
      NEG       = 0x67,  // negate top element on stack, push result back onto stack.
      NOT       = 0x69,  // negates a boolean on top of the stack.
      CNCT      = 0x6B,  // concatenate top two elements on stack, push result back onto stack.
      EQ        = 0x74,  // checks if the top two elements of the stack are equal.
      BR_F      = 0x93,  // pops the top of the stack, then branches if it is false. (takes next 4 bytes as jump length)
      HALT      = 0xF0,  // halt
      PRINT     = 0xFF   // print top of stack with newline, discarding top of stack.
    };
}

