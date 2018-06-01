#ifndef DURIAN_OPCODE_H
#define DURIAN_OPCODE_H

enum struct Opcode : unsigned char {
  NOP     = 0x00,  // pass
  ADD     = 0x60,  // add top two elements on stack, push result back onto stack.
  SUB     = 0x61,  // subtract top two elements on stack, push result back onto stack.
  MUL     = 0x62,  // multiply top two elements on stack, push result back onto stack.
  DIV     = 0x64,  // divide top two elements on stack, push result back onto stack as a double.
  NEG     = 0x67,  // negate top element on stack, push result back onto stack.
  CNCT    = 0x6B,  // concatenate top two elements on stack, push result back onto stack.
  HALT    = 0xF0   // halt
};

#endif
