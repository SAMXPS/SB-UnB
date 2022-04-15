#include "initializer.h"
#include <stdio.h>

void initialize_class(c_class* clazz) {
    // TODO ... todar clinit etc etc
    clazz->initialized = 1;
}

void run_main(c_class* main) {
    // On instance method invocation, local variable 0 is always used to pass a reference to the object on which the instance method is being invoked (this in the Java programming language).
    // Any parameters are subsequently passed in consecutive local variables starting from local variable 1.
    printf("OPAAAAA\r\n");
}