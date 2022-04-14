#ifndef FRAMES_H
#define FRAMES_H
#include "class/class_attributes.h"

#define OPERAND_STACK_SIZE      128
#define LOCAL_VARIABLES_SIZE    128
#define OPERAND_STACK_TYPE      u8

// Each frame has its own array of local variables (§2.6.1), 
// its own operand stack (§2.6.2), and a reference to the run-time constant pool (§2.5.5)
// of the class of the current method.
typedef struct {
    OPERAND_STACK_TYPE  local_variables[LOCAL_VARIABLES_SIZE];
    OPERAND_STACK_TYPE  operand_stack[OPERAND_STACK_SIZE];
    u1              operand_stack_pos;
    class_file*     clazz;
} frame;

typedef struct {
    frame_stack*   last;
    frame          data;
} frame_stack;

/**
 * @brief Retorna se a pilha de frames está vazia.
 * 
 * @return int empty.
 */
int fstack_empty();

/**
 * @brief Acessa o frame no topo da pilha de frames, sem retirar.
 * 
 * @return frame* Frame no topo da pilha.
 */
frame* fstack_top();

/**
 * @brief Retira o frame no topo da pilha de frames.
 * 
 * @return frame* Frame retirado do topo da pilha.
 */
frame fstack_pop();

/**
 * @brief Adiciona um frame no topo da pilha de frames.
 * @param f Frame a ser adicionado ao topo da fila.
 */
void fstack_push(frame f);

/**
 * @brief Adiciona um novo frame no topo da pilha de frames, especificando a classe mãe do frame.
 * @param clazz Classe do frame que será adicionado.
 */
void fstack_new(class_file* clazz);

#endif//FRAMES_H