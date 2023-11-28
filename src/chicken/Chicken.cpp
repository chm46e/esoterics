#include "Chicken.h"
#include <sstream>
#include <string>
#include <iostream>

namespace chicken {
namespace compiler {

Chicken::Chicken(std::stringstream &&code)
        : code(std::move(code)) {}

Chicken::~Chicken() {
    code.clear();
}

int Chicken::compile() {
    std::istringstream ssline;
    int total_word_count = 0;
    int total_line_count = 0;
    int opcode;

    // Starting to build stack (look at tldraw)
    stack.push_back(0); // temporary, will be replaced with user_space pointer
    code_space_ptr++;

    // TODO: add user input to stack

    for (std::string line; std::getline(code, line); total_line_count++) {
        ssline = std::istringstream(line);
        opcode = 0;

        std::string word;
        while (ssline >> word) {
            if (word != "chicken") {
                std::cout << "Typo on line " << total_word_count + 1 << " word " << total_word_count + 1 << ": " << word
                          << "\n Aborting..." << std::endl;
                return -1;
            }
            opcode++;

            total_word_count++;
        }

        stack.push_back(opcode);
    }

    stack.push_back(0); // exit at the end of code space
    user_space_ptr = code_space_ptr + total_line_count + 1;
    stack[0] = user_space_ptr;

    run();

    return 0;
}

int Chicken::run() {
    for (instruction_ptr = code_space_ptr; instruction_ptr < user_space_ptr; instruction_ptr++) {
        //std::cout << "stack: ";
        for (int i = user_space_ptr; i < stack.size(); i++) {
            //std::cout << stack[i] << " ";
        }
        //std::cout << std::endl;
        //std::cout << "op: " << stack[instruction_ptr] << std::endl;
        auto &instruction = stack.at(instruction_ptr);
        switch (instruction) {
        case 0:
            return 0;
        case 1:
            CHICKEN();
            break;
        case 2:
            ADD();
            break;
        case 3:
            SUBTRACT();
            break;
        case 4:
            MULTIPLY();
            break;
        case 5:
            COMPARE();
            break;
        case 6:
            LOAD();
            break;
        case 7:
            STORE();
            break;
        case 8:
            JUMP();
            break;
        case 9:
            CHAR_OUT();
            break;
        default:
            PUSH();
            break;
        }
    }
        return 0;
}

void Chicken::CHICKEN() {
    stack.push_back(99);
    stack.push_back(104);
    stack.push_back(105);
    stack.push_back(99);
    stack.push_back(107);
    stack.push_back(101);
    stack.push_back(110);
}

void Chicken::ADD() {
    stack.push_back(peek() + stack[stack.size() - 2]);
}

void Chicken::SUBTRACT() {
    stack.push_back(peek() - stack[stack.size() - 2]);
}

void Chicken::MULTIPLY() {
    stack.push_back(peek() * stack[stack.size() - 2]);
}

void Chicken::COMPARE() {
    if (peek() == stack[stack.size() - 2]) {
        stack.push_back(1);
    } else {
        stack.push_back(0);
    }
}

// double wide, next instruction is where to load from (0 = stack, 1 = user input)
// top of stack points to index where to load from
// index 0 should be top of stack and index 1 the 2nd top, etc
void Chicken::LOAD() {
    if (stack[instruction_ptr+1] == 0) { // from stack
        stack.push_back(stack[peek() + user_space_ptr - 1]);
    } else if (stack[instruction_ptr+1] == 1) { // from user input
        stack.push_back(stack[peek() + 1 - 1]);
    }
    instruction_ptr++; // ignore next instruction in run loop
}


// top of stack points to index where to store to
// value below is popped and stored to index
// starts at index 1?
void Chicken::STORE() {
    stack.emplace(stack.begin() + user_space_ptr + peek() - 1, stack[stack.size() - 2]);
    stack.erase(stack.begin() + stack.size() - 2);
}

void Chicken::JUMP() {
    if (stack[instruction_ptr - 1] == 1) {
        instruction_ptr = instruction_ptr - peek();
    }
}

void Chicken::CHAR_OUT() {
    char c = (char)peek();
    std::cout << c;
}

void Chicken::PUSH() {
    stack.push_back(stack[instruction_ptr] - 10);
}

}
}