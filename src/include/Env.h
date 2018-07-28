#pragma once

#include <unordered_map>
#include <inttypes.h>
#include <string>

class Env {
public:
    Env *m_parent;    
    int64_t lookUpVar(std::string);
    void declVar(std::string);
private:    
    std::unordered_map<std::string, int64_t> m_values;
    int64_t getNumVars();
};
