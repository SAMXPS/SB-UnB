#ifndef JVM_LOADER_H
#define JVM_LOADER_H
#include "jvm.h"

/**
 * @brief Adiciona uma pasta à lista de pastas de biblioteca de classes.
 * 
 * @param class_folder Nome da pasta.
 */
void     add_class_folder(char* class_folder);

/**
 * @brief Tenta carregar uma classe com base no seu nome.
 * 
 * @param class_name Nome da classe.
 * @return class_file* Arquivo da classe carregado.
 */
class_file* load_class(char* class_name);

#endif//JVM_LOADER_H