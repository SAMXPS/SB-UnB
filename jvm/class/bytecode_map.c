#include "bytecode_map.h"

int   is_instruction_map_loaded = 0;

char* instruction_map[256] = {0};
int   instruction_arg_count[256] = {0};
void (*instruction_handler[256])();

void f_aaload() {
    // executar lógica da instrução
}

void load_instruction_map() {
    if (is_instruction_map_loaded) 
        return;

    instruction_map[0x32]="aaload";
    instruction_handler[0x32] = f_aaload;

    instruction_map[0x53]="aastore";
    instruction_map[0x01]="aconst_null";
    instruction_map[0x19]="aload"; instruction_arg_count[0x19] = 1;
    instruction_map[0x2a]="aload_0";
    instruction_map[0x2b]="aload_1";
    instruction_map[0x2c]="aload_2";
    instruction_map[0x2d]="aload_3";
    instruction_map[0xbd]="anewarray"; instruction_arg_count[0xbd] = 2;
    instruction_map[0xb0]="areturn";
    instruction_map[0xbe]="arraylength";
    instruction_map[0x3a]="astore"; instruction_arg_count[0x3a] = 1;
    instruction_map[0x4b]="astore_0";
    instruction_map[0x4c]="astore_1";
    instruction_map[0x4d]="astore_2";
    instruction_map[0x4e]="astore_3";
    instruction_map[0xbf]="athrow";
    instruction_map[0x33]="baload";
    instruction_map[0x54]="bastore";
    instruction_map[0x10]="bipush"; instruction_arg_count[0x10] = 1;
    instruction_map[0xca]="breakpoint";
    instruction_map[0x34]="caload";
    instruction_map[0x55]="castore";
    instruction_map[0xc0]="checkcast"; instruction_arg_count[0xc0] = 2;
    instruction_map[0x90]="d2f";
    instruction_map[0x8e]="d2i";
    instruction_map[0x8f]="d2l";
    instruction_map[0x63]="dadd";
    instruction_map[0x31]="daload";
    instruction_map[0x52]="dastore";
    instruction_map[0x98]="dcmpg";
    instruction_map[0x97]="dcmpl";
    instruction_map[0x0e]="dconst_0";
    instruction_map[0x0f]="dconst_1";
    instruction_map[0x6f]="ddiv";
    instruction_map[0x18]="dload"; instruction_arg_count[0x18] = 1;
    instruction_map[0x26]="dload_0";
    instruction_map[0x27]="dload_1";
    instruction_map[0x28]="dload_2";
    instruction_map[0x29]="dload_3";
    instruction_map[0x6b]="dmul";
    instruction_map[0x77]="dneg";
    instruction_map[0x73]="drem";
    instruction_map[0xaf]="dreturn";
    instruction_map[0x39]="dstore"; instruction_arg_count[0x39] = 1;
    instruction_map[0x47]="dstore_0";
    instruction_map[0x48]="dstore_1";
    instruction_map[0x49]="dstore_2";
    instruction_map[0x4a]="dstore_3";
    instruction_map[0x67]="dsub";
    instruction_map[0x59]="dup";
    instruction_map[0x5a]="dup_x1";
    instruction_map[0x5b]="dup_x2";
    instruction_map[0x5c]="dup2";
    instruction_map[0x5d]="dup2_x1";
    instruction_map[0x5e]="dup2_x2";
    instruction_map[0x8d]="f2d";
    instruction_map[0x8b]="f2i";
    instruction_map[0x8c]="f2l";
    instruction_map[0x62]="fadd";
    instruction_map[0x30]="faload";
    instruction_map[0x51]="fastore";
    instruction_map[0x96]="fcmpg";
    instruction_map[0x95]="fcmpl";
    instruction_map[0x0b]="fconst_0";
    instruction_map[0x0c]="fconst_1";
    instruction_map[0x0d]="fconst_2";
    instruction_map[0x6e]="fdiv";
    instruction_map[0x17]="fload"; instruction_arg_count[0x17] = 1;
    instruction_map[0x22]="fload_0";
    instruction_map[0x23]="fload_1";
    instruction_map[0x24]="fload_2";
    instruction_map[0x25]="fload_3";
    instruction_map[0x6a]="fmul";
    instruction_map[0x76]="fneg";
    instruction_map[0x72]="frem";
    instruction_map[0xae]="freturn";
    instruction_map[0x38]="fstore"; instruction_arg_count[0x38] = 1;
    instruction_map[0x43]="fstore_0";
    instruction_map[0x44]="fstore_1";
    instruction_map[0x45]="fstore_2";
    instruction_map[0x46]="fstore_3";
    instruction_map[0x66]="fsub";
    instruction_map[0xb4]="getfield"; instruction_arg_count[0xb4] = 2;
    instruction_map[0xb2]="getstatic"; instruction_arg_count[0xb2] = 2;
    instruction_map[0xa7]="goto"; instruction_arg_count[0xa7] = 2;
    instruction_map[0xc8]="goto_w"; instruction_arg_count[0xc8] = 4;
    instruction_map[0x91]="i2b";
    instruction_map[0x92]="i2c";
    instruction_map[0x87]="i2d";
    instruction_map[0x86]="i2f";
    instruction_map[0x85]="i2l";
    instruction_map[0x93]="i2s";
    instruction_map[0x60]="iadd";
    instruction_map[0x2e]="iaload";
    instruction_map[0x7e]="iand";
    instruction_map[0x4f]="iastore";
    instruction_map[0x02]="iconst_m1";
    instruction_map[0x03]="iconst_0";
    instruction_map[0x04]="iconst_1";
    instruction_map[0x05]="iconst_2";
    instruction_map[0x06]="iconst_3";
    instruction_map[0x07]="iconst_4";
    instruction_map[0x08]="iconst_5";
    instruction_map[0x6c]="idiv";
    instruction_map[0xa5]="if_acmpeq"; instruction_arg_count[0xa5] = 2;
    instruction_map[0xa6]="if_acmpne"; instruction_arg_count[0xa5] = 2;
    instruction_map[0x9f]="if_icmpeq"; instruction_arg_count[0xa5] = 2;
    instruction_map[0xa2]="if_icmpge"; instruction_arg_count[0xa5] = 2;
    instruction_map[0xa3]="if_icmpgt"; instruction_arg_count[0xa5] = 2;
    instruction_map[0xa4]="if_icmple"; instruction_arg_count[0xa5] = 2;
    instruction_map[0xa1]="if_icmplt"; instruction_arg_count[0xa5] = 2;
    instruction_map[0xa0]="if_icmpne"; instruction_arg_count[0xa5] = 2;
    instruction_map[0x99]="ifeq"; instruction_arg_count[0x99] = 2;
    instruction_map[0x9c]="ifge"; instruction_arg_count[0x9c] = 2;
    instruction_map[0x9d]="ifgt"; instruction_arg_count[0x9d] = 2;
    instruction_map[0x9e]="ifle"; instruction_arg_count[0x9e] = 2;
    instruction_map[0x9b]="iflt"; instruction_arg_count[0x9b] = 2;
    instruction_map[0x9a]="ifne"; instruction_arg_count[0x9a] = 2;
    instruction_map[0xc7]="ifnonnull"; instruction_arg_count[0xc7] = 2;
    instruction_map[0xc6]="ifnull"; instruction_arg_count[0xc6] = 2;
    instruction_map[0x84]="iinc"; instruction_arg_count[0x84] = 2;
    instruction_map[0x15]="iload"; instruction_arg_count[0x15] = 1;
    instruction_map[0x1a]="iload_0";
    instruction_map[0x1b]="iload_1";
    instruction_map[0x1c]="iload_2";
    instruction_map[0x1d]="iload_3";
    instruction_map[0xfe]="impdep1";
    instruction_map[0xff]="impdep2";
    instruction_map[0x68]="imul";
    instruction_map[0x74]="ineg";
    instruction_map[0xc1]="instanceof"; instruction_arg_count[0xc1] = 2;
    instruction_map[0xba]="invokedynamic"; instruction_arg_count[0xba] = 4;
    instruction_map[0xb9]="invokeinterface"; instruction_arg_count[0xb9] = 4;
    instruction_map[0xb7]="invokespecial"; instruction_arg_count[0xb7] = 2;
    instruction_map[0xb8]="invokestatic"; instruction_arg_count[0xb8] = 2;
    instruction_map[0xb6]="invokevirtual"; instruction_arg_count[0xb6] = 2;
    instruction_map[0x80]="ior";
    instruction_map[0x70]="irem";
    instruction_map[0xac]="ireturn";
    instruction_map[0x78]="ishl";
    instruction_map[0x7a]="ishr";
    instruction_map[0x36]="istore"; instruction_arg_count[0x36] = 1;
    instruction_map[0x3b]="istore_0";
    instruction_map[0x3c]="istore_1";
    instruction_map[0x3d]="istore_2";
    instruction_map[0x3e]="istore_3";
    instruction_map[0x64]="isub";
    instruction_map[0x7c]="iushr";
    instruction_map[0x82]="ixor";
    instruction_map[0xa8]="jsr"; instruction_arg_count[0xa8] = 2;
    instruction_map[0xc9]="jsr_w"; instruction_arg_count[0xc9] = 4;
    instruction_map[0x8a]="l2d";
    instruction_map[0x89]="l2f";
    instruction_map[0x88]="l2i";
    instruction_map[0x61]="ladd";
    instruction_map[0x2f]="laload";
    instruction_map[0x7f]="land";
    instruction_map[0x50]="lastore";
    instruction_map[0x94]="lcmp";
    instruction_map[0x09]="lconst_0";
    instruction_map[0x0a]="lconst_1";
    instruction_map[0x12]="ldc"; instruction_arg_count[0x12] = 1;
    instruction_map[0x13]="ldc_w"; instruction_arg_count[0x13] = 2;
    instruction_map[0x14]="ldc2_w"; instruction_arg_count[0x14] = 2;
    instruction_map[0x6d]="ldiv";
    instruction_map[0x16]="lload"; instruction_arg_count[0x16] = 1;
    instruction_map[0x1e]="lload_0";
    instruction_map[0x1f]="lload_1";
    instruction_map[0x20]="lload_2";
    instruction_map[0x21]="lload_3";
    instruction_map[0x69]="lmul";
    instruction_map[0x75]="lneg";
    instruction_map[0xab]="lookupswitch"; instruction_arg_count[0xab] = -1; // diferentao
    instruction_map[0x81]="lor";
    instruction_map[0x71]="lrem";
    instruction_map[0xad]="lreturn";
    instruction_map[0x79]="lshl";
    instruction_map[0x7b]="lshr";
    instruction_map[0x37]="lstore"; instruction_arg_count[0x37] = 1;
    instruction_map[0x3f]="lstore_0";
    instruction_map[0x40]="lstore_1";
    instruction_map[0x41]="lstore_2";
    instruction_map[0x42]="lstore_3";
    instruction_map[0x65]="lsub";
    instruction_map[0x7d]="lushr";
    instruction_map[0x83]="lxor";
    instruction_map[0xc2]="monitorenter";
    instruction_map[0xc3]="monitorexit";
    instruction_map[0xc5]="multianewarray"; instruction_arg_count[0xc5] = 3;
    instruction_map[0xbb]="new"; instruction_arg_count[0xbb] = 2;
    instruction_map[0xbc]="newarray"; instruction_arg_count[0xbc] = 1;
    instruction_map[0x00]="nop";
    instruction_map[0x57]="pop";
    instruction_map[0x58]="pop2";
    instruction_map[0xb5]="putfield"; instruction_arg_count[0xb5] = 2;
    instruction_map[0xb3]="putstatic"; instruction_arg_count[0xb3] = 2;
    instruction_map[0xa9]="ret"; instruction_arg_count[0xa9] = 1;
    instruction_map[0xb1]="return";
    instruction_map[0x35]="saload";
    instruction_map[0x56]="sastore";
    instruction_map[0x11]="sipush"; instruction_arg_count[0x11] = 2;
    instruction_map[0x5f]="swap";
    instruction_map[0xaa]="tableswitch";  instruction_arg_count[0xaa] = -1; // diferentao
    instruction_map[0xc4]="wide"; instruction_arg_count[0xc4] = -1; // diferentao
    is_instruction_map_loaded = 1;
}