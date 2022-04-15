#ifndef JVM_LINKER_H
#define JVM_LINKER_H
#include "jvm.h"
#include "loader.h"
#include "initializer.h"

/**
 * @brief Retorna a classe representada pelo nome class_name. Se a classe ainda não foi carregada,
 * tentamos carregá-la e linkala. Caso ela não seja encontrada, é retornado ponteiro pra nulo.
 * 
 * @param class_name Nome da classe.
 * @return c_class* ponteiro para classe procurada ou então nulo caso não tenha sido encontrada.
 */
c_class* get_class(char* class_name);

/**
 * @brief Atualiza o mapa de nome de classes e mapeia o nome da classe para a classe.
 * 
 * @param class_name Nome da classe.
 * @param clazz Classe.
 */
void     link_class(char* class_name, c_class* clazz);

component create_field(std::string descriptor);

#endif//JVM_LINKER_H