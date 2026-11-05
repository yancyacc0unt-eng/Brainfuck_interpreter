#include "iostream"
#include "fstream"

enum class codeType {
    PLUS,
    MINUS,
    LEFT,
    RIGHT,
    INPUT,
    OUTPUT,
    LOOP_START,
    LOOP_END,
    HALT
};

struct Token {
    Token* prev;
    codeType type;
    Token* loopStart;
    Token* loopEnd;
    Token* next;
};

class Parser {
private:
    std::ifstream& input;
public:
    Parser(std::ifstream& file) : input(file) {}
    Token* tokenize() {
        Token* head = nullptr;
        Token* current = nullptr;
        Token* tail = nullptr;
        for(char c; input.get(c);) {
            Token* newToken = new Token{nullptr, codeType::HALT, nullptr, nullptr, nullptr};
            switch(c) {
                case '+':
                    newToken->type = codeType::PLUS;
                    break;
                case '-':
                    newToken->type = codeType::MINUS;
                    break;
                case '<':
                    newToken->type = codeType::LEFT;
                    break;
                case '>':
                    newToken->type = codeType::RIGHT;
                    break;
                case ',':
                    newToken->type = codeType::INPUT;
                    break;
                case '.':
                    newToken->type = codeType::OUTPUT;
                    break;
                case '[':
                    newToken->type = codeType::LOOP_START;
                    break;
                case ']':
                    newToken->type = codeType::LOOP_END;
                    while (current->type != codeType::LOOP_START) {
                        current = current->prev;
                    }
                    newToken->loopStart = current;
                    current->loopEnd = newToken;
                    break;
                default:
                    delete newToken; // Ignore unrecognized characters
                    continue;
            }
            if (head == nullptr) {
                head = tail = newToken;
            } else {
                tail->next = newToken;
                newToken->prev = tail;
                tail = newToken;
                current = newToken;
            }
        }
        Token* haltToken = new Token{tail, codeType::HALT, nullptr, nullptr, nullptr};
        tail->next = haltToken;
        return head;
    }
};

class Interpreter {
private:
    Token* tokens;
public:
    Interpreter(Token* tokenList) : tokens(tokenList) {}
    void run() {
        Token* current = tokens;
        char tape[32768] = {0};
        short position = 0;
        while (current->type != codeType::HALT) {
            switch (current->type) {
                case codeType::PLUS:
                    tape[position]++;
                    break;
                case codeType::MINUS:
                    tape[position]--;
                    break;
                case codeType::LEFT:
                    position--;
                    break;
                case codeType::RIGHT:
                    position++;
                    break;
                case codeType::INPUT:
                    tape[position] = std::cin.get();
                    break;
                case codeType::OUTPUT:
                    std::cout.put(tape[position]);
                    break;
                case codeType::LOOP_START:
                    if (tape[position] == 0) {
                        current = current->loopEnd; // Jump to the matching loop end
                    }
                    break;
                case codeType::LOOP_END:
                    if (tape[position] != 0) {
                        current = current->loopStart; // Jump back to the matching loop start
                    }
                    break;
                default:
                    break;
            }
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
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return -1;
    }
    std::ifstream input(argv[1]);
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
