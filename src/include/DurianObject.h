#pragma once

#include <cinttypes>
#include <string>
#include <DurianString.h>

enum struct DurianType {
    Double,
    Integer,
    Boolean,
    String
};

struct DurianObject {
    DurianObject();
    DurianObject(double dval);
    DurianObject(int64_t ival);
    DurianObject(bool bval);
    DurianObject(unsigned char *sval, int64_t len);
    bool isFalsy() { return type == DurianType::Boolean && !value.bval; };
    DurianType type;
    union {
        double dval;
        int64_t ival;
        bool bval;
        DurianString sval;
    } value;
};

std::ostream &operator<<(std::ostream &os, DurianType &type);
