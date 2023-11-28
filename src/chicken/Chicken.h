#pragma once

#include <sstream>
#include <vector>

namespace chicken {
namespace compiler {

class Chicken {
public:
    explicit Chicken(std::stringstream &&code);
    ~Chicken();

    int compile();
    int run();

    // returns the value at the top of the stack
    inline int peek() {
        return stack.back();
    }

    // returns and removes the value at the top of the stack
    inline int pop() {
        int val = stack.back();
        stack.pop_back();
        return val;
    }

    inline void push(int value) {
        stack.push_back(value);
    }

private:
    void CHICKEN();
    void ADD();
    void SUBTRACT();
    void MULTIPLY();
    void COMPARE();
    void LOAD();
    void STORE();
    void JUMP();
    void CHAR_OUT();
    void PUSH();

    std::stringstream code;
    std::vector<int> stack;
    int code_space_ptr = 0;
    int user_space_ptr = 0;

    int instruction_ptr;
};

}

}

