#ifndef CLASS_DEFINITIONS_H
#define CLASS_DEFINITIONS_H
#include <stdint.h>

typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

enum CONSTANT_TAGS {
    CONSTANT_Class              = 7,
    CONSTANT_Fieldref           = 9,
    CONSTANT_Methodref          = 10,
    CONSTANT_InterfaceMethodref = 11,
    CONSTANT_String             = 8,
    CONSTANT_Integer            = 3,
    CONSTANT_Float              = 4,
    CONSTANT_Long               = 5,
    CONSTANT_Double             = 6,
    CONSTANT_NameAndType        = 12,
    CONSTANT_Utf8               = 1
};

typedef struct {
    u2 length;
    u1 bytes[];
} UTF8_String;

typedef struct {
    u1 tag;
    union {
        struct {
            u2 name_index;
        } Class;
        struct {
            u2 class_index;
            u2 name_and_type_index;
        } Fieldref;
        struct {
            u2 class_index;
            u2 name_and_type_index;
        } Methodref;
        struct {
            u2 class_index;
            u2 name_and_type_index;
        } InterfaceMethodref;
        struct {
            u2 string_index;
        } String;
        struct {
            u4 bytes;
        } Integer;
        struct {
            u4 bytes;
        } Float;
        struct {
            u4 high_bytes; // unsigned
            u4 low_bytes; // unsigned
        } Long; // Ocupa dois índices na tabela constant_pool. 
        struct { 
            u4 high_bytes; // unsigned
            u4 low_bytes; // unsigned
        } Double; // Ocupa dois índices na tabela constant_pool. 
        struct {
            u2 name_index;
            u2 descriptor_index;
        } NameAndType;
        UTF8_String Utf8;
    } data;
} cp_info;

typedef struct {
    u2              attribute_name_index;
    u4              attribute_length;
    u1*             info;
} attribute_info;

typedef struct {
    u2              access_flags;
    u2              name_index;
    u2              descriptor_index;
    u2              attributes_count;
    attribute_info* attributes;
} field_info;

typedef struct {
    u2              access_flags;
    u2              name_index;
    u2              descriptor_index;
    u2              attributes_count;
    attribute_info* attributes;
} method_info;

typedef struct {
    u4              magic;
    u2              minor_version;
    u2              major_version;
    u2              constant_pool_count;
    cp_info**       constant_pool;
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

#endif//CLASS_DEFINITIONS_H