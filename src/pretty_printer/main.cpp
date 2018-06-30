#include <Lexer.h>
#include <Parser.h>
#include <PrettyPrinter.h>

#include <iostream>

int main() {
    std::cout << "Input some code! Type `fin` when you're done." << std::endl;
    bool fin = false;
    std::string input = "";
    while (!fin) {
        std::string temp;
        std::getline(std::cin, temp);
        if (temp == "fin") {
            fin = true;
        } else {
            input += temp;
            input += "\n";
        }
    }
    Parser parser {Lexer(input)};
    PrettyPrinter pp;
    bool done = false;
    while (!done) {
        auto ast = parser.parse();
        if (ast == nullptr) {
            done = true;
        } else {
            ast->accept(&pp);
        }
    }
    return 0;
}
