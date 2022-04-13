#include "class/class_attributes.h"
#include "class/class_attributes.h"

// Each frame has its own array of local variables (§2.6.1), 
// its own operand stack (§2.6.2), and a reference to the run-time constant pool (§2.5.5)
// of the class of the current method.
typedef struct {
    u1*         local_variables;
    u1*         operand_stack;
    // cp_info**   constant_pool; 
    // class_file* clazz;
    // qual seria mais simples de usar?
} frame;


typedef struct {
    linked_stack*   next;
    u1              data[];
} linked_stack;