#ifndef CLASSFILE_DEFINITIONS_H
#define CLASSFILE_DEFINITIONS_H
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
    CONSTANT_Utf8               = 1,
};

enum ACCESS_CLASS {
    ACC_PUBLIC	    = 0x0001,	// Declared public; may be accessed from outside its package.
    ACC_PRIVATE	    = 0x0002,	// Declared private; usable only within the defining class.
    ACC_PROTECTED	= 0x0004,	// Declared protected; may be accessed within subclasses.
    ACC_STATIC	    = 0x0008,	// Declared static.
    ACC_FINAL	    = 0x0010,	// Declared final; no subclasses allowed.
    ACC_SUPER	    = 0x0020,	// Treat superclass methods specially when invoked by the invokespecial instruction.
    ACC_VOLATILE	= 0x0040,	// Declared volatile; cannot be cached.
    ACC_TRANSIENT	= 0x0080,	// Declared transient; not written or read by a persistent object manager.
    ACC_INTERFACE	= 0x0200,	// Is an interface, not a class.
    ACC_ABSTRACT	= 0x0400,	// Declared abstract; must not be instantiated.
    ACC_SYNTHETIC	= 0x1000,	// Declared synthetic; not present in the source code.
    ACC_ANNOTATION	= 0x2000,	// Declared as an annotation type.
    ACC_ENUM	    = 0x4000,	// Declared as an enum type.
};

enum FIELD_DESCRIPTORS {
    FD_BYTE = 'B',	    //byte	signed byte
    FD_CHAR = 'C',	    //char	Unicode character code point in the Basic Multilingual Plane, encoded with UTF-16
    FD_DOUBLE = 'D',	//double	double-precision floating-point value
    FD_FLOAT = 'F',	    //float	single-precision floating-point value
    FD_INTEGER = 'I',	//int	integer
    FD_LONG = 'J',	    //long	long integer
    FD_CLASSNAME = 'L', //ClassName ;	reference	an instance of class ClassName
    FD_SHORT = 'S',	    //short	signed short
    FD_BOOLEAN = 'Z',	//boolean	true or false
    FD_REFERENCE = '['	//reference	one array dimension
};

#define ACC_IS_STATIC(x) (ACC_STATIC&(x))
#define ACC_IS_PUBLIC(x) (ACC_PUBLIC&(x))

typedef struct {
    u2 length;
    u1 bytes[];
} UTF8_String;

typedef struct {
    u1 tag;
    union {
        struct {
            u2 name_index;
        } Clazz;
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

#endif//CLASSFILE_DEFINITIONS_H