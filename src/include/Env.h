#pragma once

#include <unordered_map>
#include <inttypes.h>


class Env {
public:
    Env *m_parent;    
private:    
    std::unordered_map<string, int64_t> m_values;
}
