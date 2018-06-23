#pragma once

#include <Parser.h>
#include <ASTree.h>
#include <Visitor.h>

class Compiler : public Visitor {
    Parser m_parser;
    std::vector<unsigned char> m_buffer;
    std::vector<unsigned char> m_header;
public:
    explicit Compiler(Parser parser);
};