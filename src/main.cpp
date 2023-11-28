#include "Brainfuck.h"

int main(int argc, char **argv) {
    using esoterics::brainfuck::BrainfuckRuntime;

    BrainfuckRuntime runtime{argv[2]};
    if (!runtime.run())
        return 1;

    return 0;
}