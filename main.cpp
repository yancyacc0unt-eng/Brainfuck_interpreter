#include <iostream>
#include <fstream>
#include <array>
#include <stack>
#include <string>
#include <functional>

#define PLUS 0
#define MINUS 1
#define LEFT 2
#define RIGHT 3
#define INPUT 4
#define OUTPUT 5
#define LOOP_START 6
#define LOOP_END 7
#define HALT 8

struct Token {
    Token* prev;
    int type;
    Token* loopStart;
    Token* loopEnd;
    Token* next;
};

int getIndex(char c, const std::string& str) {
    std::string::size_type index = str.find(c);
    return index == std::string::npos ? HALT : static_cast<int>(index);
}

class Parser {
private:
    std::ifstream& input;
    const std::string validChars = "+-<>,.[]";
    std::stack<Token*> loopStack;
    std::array<std::function<void(Token*&)>, 3> operations;
public:
    Parser(std::ifstream& file) : input(file), loopStack{} {
        operations[0] = [&](Token*& t) { loopStack.push(t); };
        operations[1] = [&](Token*& t) {
            if (!loopStack.empty()) {
                        Token* loopStart = loopStack.top();
                        loopStack.pop();
                        t->loopStart = loopStart;
                        loopStart->loopEnd = t;
            } else {
                std::cerr << "Error: Unmatched ']' encountered." << std::endl;
                delete t;
                exit(-1);
            }
        };
        operations[2] = [&](Token*& t) { delete t; }; // Skip invalid characters
    }
    Token* tokenize() {
        Token* head = nullptr;
        Token* tail = nullptr;
        
        for(char c; input.get(c);) {
            Token* newToken = new Token{nullptr,
                getIndex(c, validChars),
                nullptr, nullptr, nullptr
            };
            operations[newToken->type - 6](newToken);
            if (head == nullptr) {
                head = tail = newToken;
            } else {
                tail->next = newToken;
                newToken->prev = tail;
                tail = newToken;
            }
        }
        if (!loopStack.empty()) {
            std::cerr << "Error: Unmatched '[' encountered." << std::endl;
            exit(-1);
        }

        Token* haltToken = new Token{tail, HALT, nullptr, nullptr, nullptr};
        tail->next = haltToken;

        return head;
    }
};

class Interpreter {
private:
    Token* tokens;
    std::array<unsigned char, 65536> tape;
    unsigned short position;
    std::array<std::function<void(Token*&)>, 8> operations;
public:
    Interpreter(Token* tokenList) : tokens(tokenList), position(0), tape{} {
        operations[0] = [&](Token*& t) { tape[position]++; };
        operations[1] = [&](Token*& t) { tape[position]--; };
        operations[2] = [&](Token*& t) { position--; };
        operations[3] = [&](Token*& t) { position++; };
        operations[4] = [&](Token*& t) { tape[position] = std::cin.get(); };
        operations[5] = [&](Token*& t) { std::cout.put(tape[position]); };
        operations[6] = [&](Token*& t) {
            if (tape[position] == 0) {
                t = t->loopEnd;
            }}; // Jump to the matching loop end
        operations[7] = [&](Token*& t) {
            if (tape[position] != 0) {
                t = t->loopStart;
            }}; // Jump back to the matching loop start
    }
    void run() {
        Token* current = tokens;
        while (current->type < HALT) {
            operations[current->type](current);
            current = current->next;
        }
    }
    ~Interpreter() {
        Token* current = tokens;
        while (current != nullptr) {
            Token* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 1) {
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return -1;
    }

    std::ifstream input(".\\test.bf");
    if (!input.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return -1;
    }

    Parser parser(input);
    Token* tokens = parser.tokenize();
    Interpreter interpreter(tokens);
    interpreter.run();

    return 0;
}
