#include <Compiler.h>
#include <Lexer.h>
#include <Parser.h>
#include <PrettyPrinter.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

// based on https://stackoverflow.com/a/868894
class ArgParser {
    std::vector<std::string> args;
public:
    bool verbose;
    enum struct Mode {
        PrettyPrint,
        CompileOnly,
        InterpretOnly,
        None
    } mode;
    std::pair<bool, std::string> optionalFilepath;

    ArgParser(int argc, char **argv)
            : verbose(false), mode(Mode::None), optionalFilepath() {
        for (int i = 0; i < argc; i++) {
            args.emplace_back(argv[i]);
        }

        this->verbose = optionExists("-v");
        if (optionExists("-h") || optionExists("--help")) {
            printHelpAndExit(0);
        }

        setModeIfExistsFlag("-p", Mode::PrettyPrint);
        setModeIfExistsFlag("-c", Mode::CompileOnly);
        setModeIfExistsFlag("-b", Mode::InterpretOnly);
        if (args.back() != "-p" &&
            args.back() != "-c" &&
            args.back() != "-b" &&
            args.back() != "-v" &&
            args.back() != args.front()) {
            optionalFilepath.first = true;
            optionalFilepath.second = args.back();
        } else {
            optionalFilepath.first = false;
            optionalFilepath.second = "";
        }
    }

private:
    bool optionExists(const std::string &option) {
        return std::find(args.begin(), args.end(), option) != args.end();
    }

    void setModeIfExistsFlag(const std::string &flag, Mode mode) {
        if (optionExists(flag)) {
            if (this->mode != Mode::None) {
                std::cout << "Cannot specify multiple modes!" << std::endl;
                printHelpAndExit(1);
            }
            this->mode = mode;
        }
    }

    [[noreturn]] void printHelpAndExit(int exitCode) {
        std::cout << "Optional command line arguments are: " << std::endl;
        std::cout << " -p [source]: Pretty print Durian source code." << std::endl;
        std::cout << " -c [source]: Produce bytecode but do not execute it." << std::endl;
        std::cout << " -b [source]: Execute the given bytecode." << std::endl;
        std::cout << "Each command optionally takes a path to source code or bytecode; if not provided, "
                     "a REPL will be launched." << std::endl;
        exit(exitCode);
    }
};

int prettyPrint(std::pair<bool, std::string> optionalFilepath) {
    std::cout << "Pretty printing..." << std::endl;
    if (optionalFilepath.first) {
        std::ifstream file(optionalFilepath.second);
        std::string input((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>());
        Parser parser{Lexer(input)};
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
    } else {
        // run pretty-printing REPL
        PrettyPrinter pp;
        std::cout << "Input some code! Type `fin` when you're done." << std::endl;
        while (true) {
            std::string input;
            std::getline(std::cin, input);
            if (input == "fin") {
                break;
            } else if (input.back() == '{') {
                // TODO make a less hacky way for this
                bool multilineDone = false;
                while (!multilineDone) {
                    std::string temp;
                    std::getline(std::cin, temp);
                    if (temp == "}") {
                        multilineDone = true;
                    }
                    input += temp;
                    input += '\n';
                }
            }
            Parser parser{Lexer(input)};
            while (true) {
                auto ast = parser.parse();
                if (ast == nullptr) {
                    break;
                } else {
                    ast->accept(&pp);
                }
            }
        }
        return 0;
    }
}

int compile(std::pair<bool, std::string> optionalFilepath, bool verbose) {
    std::cout << "Compiling only..." << std::endl;
    if (optionalFilepath.first) {
        std::cout << "Found filepath " << optionalFilepath.second << std::endl;
        std::ifstream file(optionalFilepath.second);
        std::string input((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>());
        Parser parser{Lexer(input)};
        std::vector<unsigned char> outBytecode;
        bool done = false;
        while (!done) {
            auto ast = parser.parse();
            if (ast == nullptr) {
                done = true;
            } else {
                Compiler compiler;
                ast->accept(&compiler);
                for (unsigned char bytecode : compiler.getBuffer()) {
                    outBytecode.push_back(bytecode);
                }
            }
        }
        std::ofstream outFile("tmp.durb", std::ios::binary);
        std::copy(outBytecode.cbegin(),
                  outBytecode.cend(),
                  std::ostreambuf_iterator<char>(outFile));
        
        if (verbose) {
            for (unsigned char bytecode : outBytecode) {
                printf("%.2X ", bytecode);
            }
            std::cout << std::endl;
        }
        return 0;
    } else {
        // TODO REPL
    }
    return 0;
}

int interpretBytecode(std::pair<bool, std::string> optionalFilepath, bool verbose) {
    std::cout << "Running bytecode..." << std::endl;
    // TODO
    return 0;
}

int execute(std::pair<bool, std::string> optionalFilepath, bool verbose) {
    std::cout << "Executing..." << std::endl;
    // TODO
    return 0;
}

int main(int argc, char *argv[]) {
    ArgParser argParser(argc, argv);
    switch (argParser.mode) {
        case ArgParser::Mode::PrettyPrint:
            return prettyPrint(argParser.optionalFilepath);
        case ArgParser::Mode::CompileOnly:
            return compile(argParser.optionalFilepath, argParser.verbose);
        case ArgParser::Mode::InterpretOnly:
            return interpretBytecode(argParser.optionalFilepath, argParser.verbose);
        default:
            return execute(argParser.optionalFilepath, argParser.verbose);
    }
}

