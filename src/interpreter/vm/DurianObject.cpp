#include <DurianObject.h>

#include <ostream>

DurianObject::DurianObject() :
    type(DurianType::Integer) {
    value.ival = 0;
}

DurianObject::DurianObject(double dval) :
    type(DurianType::Double) {
    value.dval = dval;
}

DurianObject::DurianObject(int64_t ival) :
    type(DurianType::Integer) {
    value.ival = ival;
}

DurianObject::DurianObject(bool bval) :
    type(DurianType::Boolean) {
    value.bval = bval;
}

DurianObject::DurianObject(int32_t len, unsigned char *sval) :
    type(DurianType::String) {
    value.sval.val = sval;
    value.sval.len = len;
}

std::ostream &operator<<(std::ostream &os, DurianType &type) {
    // Make sure all cases are covered when adding new types.
    switch (type) {
        case DurianType::Integer:
            os << "int";
            break;
        case DurianType::Double:
            os << "double";
            break;
        case DurianType::Boolean:
            os << "bool";
            break;
        case DurianType::String:
            os << "str";
            break;
    }
    return os;
}
