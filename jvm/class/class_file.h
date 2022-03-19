#ifndef CLASS_FILE_H
#define CLASS_FILE_H
#include <stdint.h>

typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

typedef struct {
    //todo
} cp_info;

typedef struct {
    //todo
} field_info;


typedef struct {
    //todo
} method_info;

typedef struct {

    //todo
} attribute_info;

typedef struct {
    u4              magic;
    u2              minor_version;
    u2              major_version;
    u2              constant_pool_count;
    cp_info*        constant_pool;
    u2              access_flags;
    u2              this_class;
    u2              super_class;
    u2              interfaces_count;
    u2*             interfaces;
    u2              fields_count;
    field_info*     fields;
    u2              methods_count;
    method_info*    methods;
    u2              attributes_count;
    attribute_info* attributes;
    void*           freeme;
} class_file;

#endif//CLASS_FILE_H