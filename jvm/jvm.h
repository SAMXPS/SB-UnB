#ifndef JVM_H
#define JVM_H
#define OPERAND_STACK_SIZE      128
#define LOCAL_VARIABLES_SIZE    128
#include <stdint.h>
#include "classfile_definitions.h"
#include <unordered_map>
#include "classfile_attributes.h"

typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

typedef int8_t   s1;
typedef int16_t  s2;
typedef int32_t  s4;
typedef int64_t  s8;

enum {
    NULL_REFERENCE = 0,
    CLASS_REFERENCE,
    ARRAY_REFERENCE,
    INTERFACE_REFERENCE,
    NUMERIC,
    BOOLEAN,
    RETURN_ADDRESS,
    VOID_RETURN,
};

enum {
    T_BOOLEAN=4,
    T_CHAR=5,
    T_FLOAT=6,
    T_DOUBLE=7,
    T_BYTE=8,
    T_SHORT=9,
    T_INT=10,
    T_LONG=11,
};

typedef uint32_t component_type;

struct c_array;
struct c_class;
struct c_interface;

typedef struct component {
    component_type type;
    union {
 struct c_array*        array;
        class_file*     clazz;
 struct c_interface*    interface;
        s1              _byte;
        u1              _ubyte;
        s2              _short;
        u2              _ushort;
        s4              _int;
        u4              _uint;
        s8              _long;
        u8              _ulong;
        u1              u1;
        u2              u2;
        u4              u4;
        u8              u8;
        float           _float;
        double          _double;
    };
} component;

typedef struct c_array{
    u4              len;
    component_type  type;
    component       data[];
} c_array;

const extern component NULL_COMPONENT;

typedef struct  {
    union {
        s1              _byte;
        u1              _ubyte;
        s2              _short;
        u2              _ushort;
        s4              _int;
        u4              _uint;
        float           _float;
        component       reference;
        //s8              _long;
        //u8              _ulong;
        //double          _double;
    };
} local_variable;

typedef struct  {
    union {
        s8              _long;
        u8              _ulong;
        double          _double;
    };
} local_variable2;

typedef struct c_object{
    class_file*     clazz;
    void*           methods; 
    void*           object_data;
} c_object;

typedef struct c_interface{

} c_interface;

typedef struct c_method {
    std::string         name;
    std::string         descriptor;
    u1*                 code;
    attribute_Code*     atr_code;
    u2                  access_flags;
} c_method;

typedef struct c_class {
    class_file*                                 class_file;
    std::unordered_map<std::string,c_method>    methods;
    std::string                                 name;
    int                                         initialized;
} c_class;

typedef struct {
    local_variable  local_variables[LOCAL_VARIABLES_SIZE];
    component       operand_stack[OPERAND_STACK_SIZE];
    u1              operand_stack_pos;
    c_class*        clazz;
} frame;

typedef struct frame_stack {
    struct frame_stack* last;
    frame               data;
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
void fstack_new(c_class* clazz);

#define exit_jvm(MESSAGE)\
    printf(#MESSAGE"\r\n");\
    exit(0);

#endif//JVM_H