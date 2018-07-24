#pragma once

#include <cinttypes>
#include <string>
#include <DurianString.h>

enum struct DurianType {
    Double,
    Integer,
    Boolean,
    String,
    Function
};

struct DurianObject {
    DurianObject();
    DurianObject(double dval);
    DurianObject(int64_t ival, DurianType type);
    DurianObject(bool bval);
    DurianObject(int32_t len, unsigned char *sval);
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
