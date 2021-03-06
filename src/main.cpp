#include <Compiler.h>
#include <Lexer.h>
#include <Parser.h>
#include <PrettyPrinter.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

typedef std::pair<bool, std::string> OptionalFilepath;

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
    OptionalFilepath input;

    ArgParser(int argc, char **argv)
            : verbose(false), mode(Mode::None), input() {
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
            input.first = true;
            input.second = args.back();
        } else {
            input.first = false;
            input.second = "";
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

int prettyPrint(OptionalFilepath input) {
    std::cout << "Pretty printing..." << std::endl;
    if (input.first) {
        std::ifstream file(input.second);
        std::string source((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        Parser parser{Lexer(source)};
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
            std::string source;
            std::getline(std::cin, source);
            if (source == "fin") {
                break;
            } else if (source.back() == '{') {
                // TODO make a less hacky way for this
                bool multilineDone = false;
                while (!multilineDone) {
                    std::string temp;
                    std::getline(std::cin, temp);
                    if (temp == "}") {
                        multilineDone = true;
                    }
                    source += temp;
                    source += '\n';
                }
            }
            Parser parser{Lexer(source)};
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

int compile(OptionalFilepath input, bool verbose) {
    std::cout << "Compiling only..." << std::endl;
    if (input.first) {
        std::cout << "Found filepath " << input.second << std::endl;
        std::ifstream file(input.second);
        std::string source((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        Parser parser{Lexer(source)};
        Compiler compiler;
        std::vector<unsigned char> outBytecode;
        bool done = false;
        while (!done) {
            auto ast = parser.parse();
            if (ast == nullptr) {
                done = true;
            } else {
                ast->accept(&compiler);
                for (unsigned char bytecode : compiler.getBuffer()) {
                    outBytecode.push_back(bytecode);
                }
            }
        }
        outBytecode.push_back(Opcode::HALT);
        std::vector<uint8_t> strings = compiler.getStaticStrings();
        std::string outFileName = std::string(input.second);
        outFileName += 'b';
        std::ofstream outFile(outFileName, std::ios::binary);
        std::copy(strings.cbegin(),
                  strings.cend(),
                  std::ostreambuf_iterator<char>(outFile));
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

int interpretBytecode(OptionalFilepath input, bool verbose) {
    std::cout << "Running bytecode..." << std::endl;
    if (input.first) {
        std::cout << "Found filepath " << input.second << std::endl;
        std::ifstream file(input.second);
    } else {
        // TODO REPL
    }
    // TODO
    return 0;
}

int execute(OptionalFilepath input, bool verbose) {
    std::cout << "Executing..." << std::endl;
    int compileResult = compile(input, verbose);
    if (compileResult != 0) {
        std::cout << "Compilation failed" << std::endl;
        return compileResult;
    }
    OptionalFilepath bytecodeFile;
    bytecodeFile.first = true;
    if (!input.first) {
        bytecodeFile.second = "temp.durb";
    } else {
        bytecodeFile.second += input.second;
        bytecodeFile.second += 'b';
    }
    return interpretBytecode(bytecodeFile, verbose);
}

int main(int argc, char *argv[]) {
    ArgParser argParser(argc, argv);
    switch (argParser.mode) {
        case ArgParser::Mode::PrettyPrint:
            return prettyPrint(argParser.input);
        case ArgParser::Mode::CompileOnly:
            return compile(argParser.input, argParser.verbose);
        case ArgParser::Mode::InterpretOnly:
            return interpretBytecode(argParser.input, argParser.verbose);
        default:
            return execute(argParser.input, argParser.verbose);

    }
}

