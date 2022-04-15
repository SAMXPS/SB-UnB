#include "jvm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "classfile_definitions.h"
#include "classfile_loader.h"
#include "linker.h"
#include "loader.h"
#include "initializer.h"

const component NULL_COMPONENT = {0};
frame_stack* fstack = 0;

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
    // TODO
    exit_jvm("i_local_variable nao implementada");
}

local_variable2 i_local_variable2(u2 position) {
    // TODO
    exit_jvm("i_local_variable2 nao implementada");
}

void i_local_variable_set(u2 position, local_variable value) {
    // TODO
    exit_jvm("i_local_variable_set nao implementada");
}

void i_local_variable_set2(u2 position, local_variable2 value) {
    // TODO
    exit_jvm("i_local_variable_set2 nao implementada");
}

int i_has_exception() {
    // TODO
    exit_jvm("i_has_exception nao implementada");
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
    // TODO
    // nao altera o pc diretamente, usa uma variavel next_pc...
    exit_jvm("i_read_code_u1 nao implementada");
}

u2 i_read_code_u2() {
    // TODO
    // nao altera o pc diretamente, usa uma variavel next_pc...
    exit_jvm("i_read_code_u2 nao implementada");
} 

component i_create_array(int type_index, int len) {
    // TODO
    exit_jvm("i_create_array nao implementada");
}

void i_return(component ret) {
    // TODO
    exit_jvm("i_return nao implementada");
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
        frame_stack* to_free = fstack;
        fstack = fstack->last;
        free(to_free);
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

void fstack_new(class_file* clazz) {
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