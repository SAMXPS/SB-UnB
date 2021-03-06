#include "jvm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "instruction_utils.h"
#include "classfile_definitions.h"
#include "classfile_loader.h"
#include "instruction_map.h"
#include "bytecode_map.h"
#include "linker.h"
#include "loader.h"
#include "initializer.h"
#include "utf8_utils.h"

int debug = 1;
int has_exception = 0;
const component NULL_COMPONENT = {0};
frame_stack* fstack = 0;
u1* next_pc;
void (*instruction)();

void i_push(component data) {
    if (fstack_empty())
        return;
    frame* f = fstack_top();
    f->operand_stack[++(f->operand_stack_pos)] = data;
}

component i_pop() {
    if (fstack_empty())
        return NULL_COMPONENT;

    frame* f = fstack_top();

    if (f->operand_stack_pos < 0)
        return NULL_COMPONENT;

    return f->operand_stack[f->operand_stack_pos--];   
}

local_variable i_local_variable(u2 position) {
    return fstack_top()->local_variables[position];
}

local_variable2 i_local_variable2(u2 position) {
    // TODO
    exit_jvm("i_local_variable2 nao implementada");
}

void i_local_variable_set(u2 position, local_variable value) {
    fstack_top()->local_variables[position] = value;
}

void i_local_variable_set2(u2 position, local_variable2 value) {
    // TODO
    exit_jvm("i_local_variable_set2 nao implementada");
}

int i_has_exception() {
    return has_exception;
}

int i_is_wide() {
    // TODO
    exit_jvm("i_is_wide nao implementada");
}

void i_set_wide() {
    // TODO
    exit_jvm("i_set_wide nao implementada");
}

void i_add_to_pc(int offset) {
    // TODO
    exit_jvm("i_add_to_pc nao implementada");
}

u1 i_read_code_u1() {
    return *(next_pc++);
}

u2 i_read_code_u2() {
    u1* u1ptr = next_pc;
    u2 uzhort = (u2)(u1ptr[0]) << 8 | (u2)u1ptr[1];
    next_pc+=2;
    return uzhort;
}

cp_info* i_read_cp(int index) {
    class_file* current_class = fstack_top()->clazz->class_file;
    return current_class->constant_pool[index-1];
}

component* i_find_static_field(cp_info* field_ref) {
    if (!field_ref || field_ref->tag != CONSTANT_Fieldref)
        return 0;
    
    std::string className = utf8_load_constant_pool_class_name_indirect(fstack_top()->clazz->class_file, field_ref->data.Fieldref.class_index);
    std::string name = utf8_load_constant_pool_name_and_type_name(fstack_top()->clazz->class_file, field_ref->data.Fieldref.name_and_type_index);
    std::string type =  utf8_load_constant_pool_name_and_type_type(fstack_top()->clazz->class_file, field_ref->data.Fieldref.name_and_type_index);

    printf("[WARNING] typecheck de fields desligado...\r\n");
    
    c_class* clazz = get_class(&(className[0]));
    
    if (clazz) {
        if (clazz->static_fields.find(name) != clazz->static_fields.end()) {
            if (debug) 
                printf("[DBG] Field encontrado!\r\n");
            return &(clazz->static_fields[name]);
        } else {
            i_throw(FieldNotFoundException);
        }
    } else {
        i_throw(ClassNotFoundException);
    }
}

c_method* i_find_method(cp_info* method_ref) {
    if (!method_ref || method_ref->tag != CONSTANT_Methodref)
        return 0;
    
    std::string className = utf8_load_constant_pool_class_name_indirect(fstack_top()->clazz->class_file, method_ref->data.Methodref.class_index);
    std::string name = utf8_load_constant_pool_name_and_type_name(fstack_top()->clazz->class_file, method_ref->data.Methodref.name_and_type_index);
    std::string type =  utf8_load_constant_pool_name_and_type_type(fstack_top()->clazz->class_file, method_ref->data.Methodref.name_and_type_index);
    std::string nameAndType = name + type;

    if (debug) 
        printf("[DBG] Procurando metodo %s da classe %s\r\n", nameAndType.c_str(), className.c_str());

    c_class* clazz = get_class(&(className[0]));

    if (clazz) {
        if (clazz->methods.find(nameAndType) != clazz->methods.end()) {
            if (debug) 
                printf("[DBG] Metodo encontrado!\r\n");
            return &(clazz->methods[nameAndType]);
        } else {
            i_throw(MethodNotFoundException);
        }
    } else {
        i_throw(ClassNotFoundException);
    }
}

void print_component(component c) {
    printf("component ");
    switch (c.type) {
        case NULL_REFERENCE:
            printf("referencia nula");
            break;
        case VOID_RETURN:
            printf("VOID RETURN");
            break;
        case NUMERIC:
            printf("NUMERICO %ld", c._long);
            break;
        default:
            break;
    }
    printf("\n");
}

void print_frame(frame* frame) {
    for(int i = 0; i <= frame->operand_stack_pos && frame->operand_stack_pos != 0xFF; i++) {
        printf("[%d] ");
        print_component(frame->operand_stack[i]);
    }
}

void i_load_method_parameters(c_method* method, frame* frame) {
    // TODO: ler method descriptor e carregar os parametros corretamente.
    std::string descriptor = method->descriptor;
    component c;
    int lpos = 0;
    local_variable l;
    int end = 0;
    for (int i = 1; i < descriptor.length() && !end; i++) {
        switch (descriptor[i]){
            case FD_BYTE:
            case FD_CHAR:
                c = i_pop();
                l._byte = c._byte;
                frame->local_variables[lpos++] = l;
                break;
            case FD_SHORT:
            case FD_BOOLEAN:
            case FD_FLOAT:
            case FD_INTEGER:
                c = i_pop();
                l._uint = c._uint;
                frame->local_variables[lpos++] = l;
                break;
            case FD_LONG:
            case FD_DOUBLE:
                break;
            case FD_CLASSNAME:
                break;
            case FD_REFERENCE:
                break;
            case ')':
                end = 1;
                break;
            default:
                break;
        }
    }

    printf("[WARNING] Eh preciso ler method descriptor e carregar os parametros corretamente.!\r\n");
}

void i_invoke_static(c_method* method) {
    if (!ACC_IS_STATIC(method->access_flags)) {
        i_throw(IncompatibleClassChangeError);
    }
    
    frame f = {0};
    f.clazz = method->clazz;
    f.operand_stack_pos = -1;

    i_load_method_parameters(method, &f);

    f.pc = method->code;

    if (fstack_top()) {
        fstack_top()->pc = next_pc;
    }

    fstack_push(f);

    next_pc = f.pc;
}

void i_invoke_virtual(c_method* method) {
    exit_jvm("i_invoke_virtual nao implementada");
}

void i_invoke_special(c_method* method) {
    exit_jvm("i_invoke_special nao implementada");
}

component i_create_array(int type_index, int len) {
    // TODO
    exit_jvm("i_create_array nao implementada");
}

void i_return(component ret) {
    if (debug) {
        printf("[DBG] Retornando ");
        print_component(ret);
    }
    fstack_pop();
    if (fstack_top() && ret.type != VOID_RETURN){
        i_push(ret);
    }
}

void i_throw_exception_by_name(char* name) {
    printf("Excessao lancada: %s\r\n", name);
    // TODO: handle exception
    exit_jvm("Excessao nao foi tratada");
}

int fstack_empty() {
    return fstack == 0;
}

frame* fstack_top() {
    if (fstack) {
        return &(fstack->data);
    }
    return 0;
}


frame fstack_pop() {
    if (fstack) {
        frame f = fstack->data;
        if (debug) {
            printf("[DBG] dando pop no frame atual da stack\r\n");
            print_frame(&f);
        }
        frame_stack* to_free = fstack;
        fstack = fstack->last;
        free(to_free);
        if (fstack) {
            next_pc = fstack->data.pc;
        }
        return f;
    }
    // Erro, pilha vazia??
}

void fstack_push(frame f) {
    frame_stack* new_frame = (frame_stack*) malloc(sizeof(frame_stack));
    new_frame->data = f;
    new_frame->last = fstack;
    fstack = new_frame;
}

void fstack_new(c_class* clazz) {
    frame f = {0};
    f.clazz = clazz;
    f.operand_stack_pos = -1;
    fstack_push(f);
}

void print_usage() {
    printf("Uso da JVM:\r\n jvm [opcoes] <MainClassName>\r\n");
    printf("Opcoces:\r\n");
    printf("\t--folder <folder>\tEspecificar uma pasta que contem uma serie de classes a serem carregadas.\r\n");
    printf("\t--exibir\tNao executar as classes, apenas rodar o leitor-exibidor.\r\n");
}


void decode(u1 opcode) {
    instruction = instruction_handler[opcode];
    if (!instruction) {
        printf("instrucao %d nao implementada\r\n", opcode);
        exit_jvm();
    }
    if (debug) {
        printf("[DBG] Rodando instrucao %s\r\n", instruction_map[opcode]);
    }
}

void run() {
    u1  opcode;
    while (fstack_top()) {
        next_pc = (fstack_top()->pc)+1;
        opcode = *(fstack_top()->pc);
        decode(opcode);
        instruction();
        if (fstack_top()) {
            fstack_top()->pc = next_pc;
        }
    }
}

void i_run_clinit(c_class* clazz) {
    if (debug) {
        printf("[DBG] Rodando clinit da classe %s\r\n", clazz->name.c_str());
    }

    fstack_new(clazz);
    fstack_top()->pc = clazz->methods["<clinit>()V"].code;
    run();
}

void run_main(c_class* main) {
    // On instance method invocation, local variable 0 is always used to pass a reference to the object on which the instance method is being invoked (this in the Java programming language).
    // Any parameters are subsequently passed in consecutive local variables starting from local variable 1.

    if (main->methods.find("main([Ljava/lang/String;)V") == main->methods.end()) {
        printf("Main nao encontrada!!\r\n");
        return;
    }

    c_method method = main->methods["main([Ljava/lang/String;)V"];

    if (!ACC_IS_STATIC(method.access_flags)) {
        printf("Main nao eh estatica!!\r\n");
        return;
    }

    if (!method.code) {
        printf("Main nao tem codigo implementado!!\r\n");
        return;
    }

    if (debug) {
        printf("[DBG] Iniciando aplicacao main da classe %s\r\n", main->name.c_str());
    }

    fstack_new(main);
    fstack_top()->pc = method.code;
    run();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 0;
    }

    u2 class_count = 0;
    u1 leitor_exibidor = 0;
    char* main_class_name = 0;

    for (int i = 1; i < argc; i++) {
        // Tentamos decodificar uma opcao
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-' && strcmp(argv[i]+2,"folder") == 0) {
                char* folder = argv[++i];
                add_class_folder(folder);
            }

            if (argv[i][1] == '-' && strcmp(argv[i]+2,"exibir") == 0) {
                leitor_exibidor = 1;
            }
            continue;
        }

        main_class_name = argv[i];
    }

    if (!main_class_name) {
        printf("[JVM] Classe Main nao informada... \r\n");
        print_usage();
        return 0;
    }

    if (leitor_exibidor) {
        // todo: ....
        for (int i = 0; i < class_count; i++) {

        }
    } else {
        load_instructions();
        load_instruction_map();

        c_class* main_class = get_class(main_class_name);

        if (!main_class) {
            printf("[JVM] Nao foi possivel carregar a JVM com classe main informada.\r\n");
            return 0;
        }

        run_main(main_class);
    }
    printf("[JVM] Fim da execucao normal da JVM.\r\n");
    return 0;
}