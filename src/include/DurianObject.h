#pragma once

#include <cinttypes>
#include <string>
#ifndef DURIAN_DURIANOBJECT_H
#define DURIAN_DURIANOBJECT_H

enum struct DurianType {
    Double,
    Integer
};

struct DurianObject {
    DurianObject();
    DurianObject(double dval);
    DurianObject(int64_t ival);
    DurianType type;
    union {
        double dval;
        int64_t ival;
    } value;
};

std::ostream &operator<<(std::ostream &os, DurianType &type);


#endif //DURIAN_DURIANOBJECT_H
