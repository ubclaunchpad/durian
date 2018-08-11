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
    value.sval.p_val = sval;
    value.sval.m_len = len;
}

DurianObject::DurianObject(int8_t len, int64_t fval) :
        type(DurianType::Function) {
    value.fval.m_len = len;
    value.fval.m_val = fval;
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
        case DurianType::Function:
            os << "fn";
            break;
    }
    return os;
}
