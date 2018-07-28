#pragma once

#include <cinttypes>
#include <string>
#include <DurianString.h>
#include <DurianFunction.h>

enum struct DurianType {
    Double,
    Integer,
    Boolean,
    String,
    Function
};

struct DurianObject {
    explicit DurianObject();
    explicit DurianObject(double dval);
    explicit DurianObject(int64_t ival);
    explicit DurianObject(bool bval);
    explicit DurianObject(int32_t len, unsigned char *sval);
    explicit DurianObject(int8_t len, int64_t fval);
    bool isFalsy() { return type == DurianType::Boolean && !value.bval; };
    DurianType type;
    union {
        double dval;
        int64_t ival;
        bool bval;
        DurianString sval;
        DurianFunction fval;
    } value;
};

std::ostream &operator<<(std::ostream &os, DurianType &type);
