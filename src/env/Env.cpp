#include <Env.h>


int64_t Env::getNumVars() {
    return m_values.size() + (m_parent ? m_parent->getNumVars() : 0);
}

void Env::declVar(std::string varName) {
    int64_t size = getNumVars();
    m_values.emplace(varName, size);
}

int64_t Env::lookUpVar(std::string varName) {
    auto v = m_values.find(varName);
    if (v != m_values.end()) return v->second;
    
    if (m_parent == nullptr) exit(1);
    
    return m_parent->lookUpVar(varName);
}
