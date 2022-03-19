#include "class_loader.h"
#include "class_file.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void* copy_class_file_to_ram(const char *filename) {
    FILE* fp;
    fp = fopen(filename, "rb");
    if (!fp) return 0;
    fseek(fp, 0L, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    printf("File has %ld size\n", fsize);
    void* data = malloc(fsize);
    fread(data, fsize, 1, fp);
    return data;
}

u2 u2_read(const void* data) {
    u1* u1ptr = (u1*)data;
    return (u2)(u1ptr[0]) << 8 | (u2)u1ptr[1];
}

u2 u2_readp(void** data) {
    u2 ret = u2_read(*data);
    *data+=2;
    return ret;
}

u4 u4_read(const void* data) {
    u1* u1ptr = (u1*)data;
    return (u4)(u1ptr[0]) << 24 | (u4)(u1ptr[1]) << 16 | (u4)(u1ptr[2]) << 8 | (u4)u1ptr[3];
}

u4 u4_readp(void** data) {
    u4 ret = u4_read(*data);
    *data+=4;
    return ret;
}

u8 u8_read(const void* data) {
    return (u8)u4_read(data) << 32 | u4_read(data+4);
}

class_file* load_class_file(const char*filename) {
    void* data = copy_class_file_to_ram(filename);
    
    if (!data) {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }
    
    class_file class;

    class.freeme = data;
    class.magic = u4_readp(&data);

    if (class.magic != 0xCAFEBABE) {
        printf("Identificador CAFEBABE não encontrado no arquivo de classe.\n");
        return 0;
    }

    class.minor_version = u2_readp(&data);
    class.major_version = u2_readp(&data);
    class.constant_pool_count = u2_readp(&data);

    printf("minor_version=%u\n", class.minor_version);
    printf("major_version=%u\n", class.major_version);
    printf("cpoolcount=%d\n", class.constant_pool_count);

    //todo: finalizar leitura do classfile...

    class_file* ptr = malloc(sizeof(class));
    *ptr = class;

    return ptr;
}