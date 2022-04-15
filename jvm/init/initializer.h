#ifndef JVM_INITIALIZER_H
#define JVM_INITIALIZER_H
#include "jvm.h"

/**
 * @brief Faz a inicialização da classe.
 * 
 * @param c_class* classe a ser iniciada. 
 */
void initialize_class(c_class* clazz);

/**
 * @brief Tenta executar o método main da classe...
 * 
 * @param main Classe main.
 */
void run_main(c_class* main);

#endif//JVM_INITIALIZER_H