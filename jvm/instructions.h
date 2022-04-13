#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

extern void (*instruction_handler[256])();
void load_instructions();

void f_aaload();
void f_aastore();
void f_aconst_null();
void f_aload();
void f_aload_0();
void f_aload_1();
void f_aload_2();
void f_aload_3();
void f_anewarray();
void f_areturn();
void f_arraylength();
void f_astore();
void f_astore_0();
void f_astore_1();
void f_astore_2();
void f_astore_3();
void f_athrow();
void f_baload();
void f_bastore();
void f_bipush();
void f_breakpoint();
void f_caload();
void f_castore();
void f_checkcast();
void f_d2f();
void f_d2i();
void f_d2l();
void f_dadd();
void f_daload();
void f_dastore();
void f_dcmpg();
void f_dcmpl();
void f_dconst_0();
void f_dconst_1();
void f_ddiv();
void f_dload();
void f_dload_0();
void f_dload_1();
void f_dload_2();
void f_dload_3();
void f_dmul();
void f_dneg();
void f_drem();
void f_dreturn();
void f_dstore();
void f_dstore_0();
void f_dstore_1();
void f_dstore_2();
void f_dstore_3();
void f_dsub();
void f_dup();
void f_dup_x1();
void f_dup_x2();
void f_dup2();
void f_dup2_x1();
void f_dup2_x2();
void f_f2d();
void f_f2i();
void f_f2l();
void f_fadd();
void f_faload();
void f_fastore();
void f_fcmpg();
void f_fcmpl();
void f_fconst_0();
void f_fconst_1();
void f_fconst_2();
void f_fdiv();
void f_fload();
void f_fload_0();
void f_fload_1();
void f_fload_2();
void f_fload_3();
void f_fmul();
void f_fneg();
void f_frem();
void f_freturn();
void f_fstore();
void f_fstore_0();
void f_fstore_1();
void f_fstore_2();
void f_fstore_3();
void f_fsub();
void f_getfield();
void f_getstatic();
void f_goto();
void f_goto_w();
void f_i2b();
void f_i2c();
void f_i2d();
void f_i2f();
void f_i2l();
void f_i2s();
void f_iadd();
void f_iaload();
void f_iand();
void f_iastore();
void f_iconst_m1();
void f_iconst_0();
void f_iconst_1();
void f_iconst_2();
void f_iconst_3();
void f_iconst_4();
void f_iconst_5();
void f_idiv();
void f_if_acmpeq();
void f_if_acmpne();
void f_if_icmpeq();
void f_if_icmpge();
void f_if_icmpgt();
void f_if_icmple();
void f_if_icmplt();
void f_if_icmpne();
void f_ifeq();
void f_ifge();
void f_ifgt();
void f_ifle();
void f_iflt();
void f_ifne();
void f_ifnonnull();
void f_ifnull();
void f_iinc();
void f_iload();
void f_iload_0();
void f_iload_1();
void f_iload_2();
void f_iload_3();
void f_impdep1();
void f_impdep2();
void f_imul();
void f_ineg();
void f_instanceof();
void f_invokedynamic();
void f_invokeinterface();
void f_invokespecial();
void f_invokestatic();
void f_invokevirtual();
void f_ior();
void f_irem();
void f_ireturn();
void f_ishl();
void f_ishr();
void f_istore();
void f_istore_0();
void f_istore_1();
void f_istore_2();
void f_istore_3();
void f_isub();
void f_iushr();
void f_ixor();
void f_jsr();
void f_jsr_w();
void f_l2d();
void f_l2f();
void f_l2i();
void f_ladd();
void f_laload();
void f_land();
void f_lastore();
void f_lcmp();
void f_lconst_0();
void f_lconst_1();
void f_ldc();
void f_ldc_w();
void f_ldc2_w();
void f_ldiv();
void f_lload();
void f_lload_0();
void f_lload_1();
void f_lload_2();
void f_lload_3();
void f_lmul();
void f_lneg();
void f_lookupswitch();
void f_lor();
void f_lrem();
void f_lreturn();
void f_lshl();
void f_lshr();
void f_lstore();
void f_lstore_0();
void f_lstore_1();
void f_lstore_2();
void f_lstore_3();
void f_lsub();
void f_lushr();
void f_lxor();
void f_monitorenter();
void f_monitorexit();
void f_multianewarray();
void f_new();
void f_newarray();
void f_nop();
void f_pop();
void f_pop2();
void f_putfield();
void f_putstatic();
void f_ret();
void f_return();
void f_saload();
void f_sastore();
void f_sipush();
void f_swap();
void f_tableswitch();
void f_wide();

#endif//INSTRUCTIONS_H