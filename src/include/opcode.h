#pragma once

namespace Opcode {
    // Note: this is a raw enum, instead of an enum struct, because we need to be able to treat these as raw characters.
    enum : unsigned char {
      NOP       = 0x00,  // pass
      ICONST_0  = 0x04,  // push literal int(0) onto stack.
      ICONST_1  = 0x05,  // push literal int(1) onto stack.
      BCONST_F  = 0x0E,  // push literal bool(false) onto stack.
      BCONST_T  = 0x0F,  // push literal bool(true) onto stack.
      ADD       = 0x60,  // add top two elements on stack, push result back onto stack.
      SUB       = 0x61,  // subtract top two elements on stack, push result back onto stack.
      MUL       = 0x62,  // multiply top two elements on stack, push result back onto stack.
      FDIV      = 0x64,  // divide top two elements on stack, push result back onto stack as a double.
      NEG       = 0x67,  // negate top element on stack, push result back onto stack.
      NOT       = 0x69,  // negates a boolean on top of the stack.
      CNCT      = 0x6B,  // concatenate top two elements on stack, push result back onto stack.
      EQ        = 0x74,  // checks if the top two elements of the stack are equal.
      HALT      = 0xF0,  // halt
      PRINT     = 0xFF   // print top of stack with newline, discarding top of stack.
    };
}

