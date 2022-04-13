#include "class/class_definitions.h"
#include "class/bytecode_map.h"

u1      read_opcode();
u1      has_operands(u1 opcode);
void    get_operands();

void run() {
    do {
        u1 opcode = read_opcode();
        if (has_operands(opcode)) 
            get_operands();
        (*instruction_handler[opcode])();
    } while (1); 
}