#pragma once

#include <cinttypes>

#ifndef DURIAN_DURIANOBJECT_H
#define DURIAN_DURIANOBJECT_H

enum struct DurianType {
    Double,
    Integer
};

struct DurianObject {
    DurianType type;
    union {
        double dval;
        int64_t ival;
    } value;
};

#endif //DURIAN_DURIANOBJECT_H
