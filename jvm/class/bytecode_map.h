#ifndef BYTECODE_MAP_H
#define BYTECODE_MAP_H

extern char* instruction_map[256];
extern int   instruction_arg_count[256];
void  load_instruction_map();

#endif//BYTECODE_MAP_H