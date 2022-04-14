#include "instruction_utils.h"

// Load reference from array
void f_aaload() {
	component comp_a = i_pop();
	component comp_b = i_pop();

	if (comp_a.type != ARRAY_REFERENCE) {
		i_throw(NullPointerException);
		return;
	}

	if (comp_b.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}

	c_array* array = comp_a.array;
	int index = comp_b._int;

	if (index < 0 || index > array->len) {
		i_throw(ArrayIndexOutOfBoundsException);
		return;
	}

	i_push(array->data[index]);
}

// Store into reference array
void f_aastore() {
	component comp_value = i_pop();
	component comp_index = i_pop();
	component comp_arrayref = i_pop();

	if (comp_arrayref.type != ARRAY_REFERENCE) {
		i_throw(NullPointerException);
		return;
	}

	if (comp_index.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}

	c_array* array = comp_arrayref.array;
	int index = comp_index._int;

	if (index < 0 || index > array->len) {
		i_throw(ArrayIndexOutOfBoundsException);
		return;
	}

	if (comp_value.type != array->type) {
		// TODO: Implementar a longa lista de checagens de tipo a serem feitas aqui....
		i_throw(ArrayStoreException);
		return;
	}

	array->data[index] = comp_value;
}

// Push the null object reference onto the operand stack.
void f_aconst_null() {
	i_push(NULL_COMPONENT);
}

void f_aload_n(u2 index) {
	local_variable l = i_local_variable(index);
	
	if (i_has_exception())
		return;
	
	if (l.reference.type == RETURN_ADDRESS) {
		i_throw(RuntimeException);
		return;
	}

	i_push(l.reference);
}

// Load reference from local variable
void f_aload() {
	f_aload_n(i_is_wide() ? i_read_code_u2() : i_read_code_u1());
}

void f_aload_0() {
	f_aload_n(0);
}

void f_aload_1() {
	f_aload_n(1);
}

void f_aload_2() {
	f_aload_n(2);
}

void f_aload_3() {
	f_aload_n(3);
}

void f_anewarray() {
	component comp_count = i_pop();
	u2 index = ((i_read_code_u1() << 8) | i_read_code_u1());

	if (comp_count.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}

	int count = comp_count._int;

	if (count < 0) {
		i_throw(NegativeArraySizeException);
		return;
	}

	component arrayref = i_create_array(index, count);

	if (arrayref.type != ARRAY_REFERENCE) {
		i_throw(RuntimeException);
		return;
	}

	i_push(arrayref);
}

void f_areturn() {
	i_return(i_pop());
}

void f_arraylength() {
	component arrayref = i_pop();

	if (arrayref.type != ARRAY_REFERENCE) {
		i_throw(NullPointerException);
		return;
	}

	component arraylen = {.type=NUMERIC,._int=(arrayref.array->len)};
	
	i_push(arraylen);
}

// Store reference into local variable
void f_astore_n(int n) {
	component objectref = i_pop();
	local_variable var = {.reference=objectref};
	i_local_variable_set(n, var);
}

void f_astore() {
	f_astore_n(i_is_wide() ? i_read_code_u2() : i_read_code_u1());
}

void f_astore_0() {
	f_astore_n(0);
}

void f_astore_1() {
	f_astore_n(1);
}

void f_astore_2() {
	f_astore_n(2);
}

void f_astore_3() {
	f_astore_n(3);
}

void f_athrow() {
	// TODO: implementar exception handler	
}

// Load byte or boolean from array
void f_baload(){
	component c_index = i_pop();
	component arrayref = i_pop();

	if (c_index.type != NUMERIC) {
		i_throw(NullPointerException);
		return;
	}

	if (arrayref.type != ARRAY_REFERENCE) {
		i_throw(NullPointerException);
		return;
	}

	int index = c_index._int;
	c_array* array = arrayref.array;

	if (index < 0 || index > array->len) {
		i_throw(ArrayIndexOutOfBoundsException);
		return;
	}

	if (array->type != NUMERIC && array->type != BOOLEAN) {
		i_throw(IllegalArgumentExcepetion);
		return;
	}

	component my_bool = array->data[index];
	component to_push = {.type=NUMERIC,._int=my_bool._byte};

	i_push(to_push);
}

void f_bastore() {
	// A implementação de array é a mesma para bytes e booleanos nessa jvm.
	f_astore();
}

void f_bipush() {
	u1 byte = i_read_code_u1();

	s4 extend = (s4)(*((s1*)&byte));
	component to_push = {.type=NUMERIC,._int=extend};

	i_push(to_push);
}

// ?
void f_breakpoint() {
	// TODO:
}

void f_caload() {
	// TODO: checar
	f_aaload();
}

void f_castore() {
	// TODO: checar
	f_aastore();
}

void f_checkcast() {
	
}

void f_d2f() {}
void f_d2i() {}
void f_d2l() {}
void f_dadd() {}
void f_daload() {}
void f_dastore() {}
void f_dcmpg() {}
void f_dcmpl() {}
void f_dconst_0() {}
void f_dconst_1() {}
void f_ddiv() {}
void f_dload() {}
void f_dload_0() {}
void f_dload_1() {}
void f_dload_2() {}
void f_dload_3() {}
void f_dmul() {}
void f_dneg() {}
void f_drem() {}
void f_dreturn() {}
void f_dstore() {}
void f_dstore_0() {}
void f_dstore_1() {}
void f_dstore_2() {}
void f_dstore_3() {}
void f_dsub() {}
void f_dup() {}
void f_dup_x1() {}
void f_dup_x2() {}
void f_dup2() {}
void f_dup2_x1() {}
void f_dup2_x2() {}
void f_f2d() {}
void f_f2i() {}
void f_f2l() {}
void f_fadd() {}
void f_faload() {}
void f_fastore() {}
void f_fcmpg() {}
void f_fcmpl() {}
void f_fconst_0() {}
void f_fconst_1() {}
void f_fconst_2() {}
void f_fdiv() {}
void f_fload() {}
void f_fload_0() {}
void f_fload_1() {}
void f_fload_2() {}
void f_fload_3() {}
void f_fmul() {}
void f_fneg() {}
void f_frem() {}
void f_freturn() {}
void f_fstore() {}
void f_fstore_0() {}
void f_fstore_1() {}
void f_fstore_2() {}
void f_fstore_3() {}
void f_fsub() {}
void f_getfield() {}
void f_getstatic() {}
void f_goto() {}
void f_goto_w() {}
void f_i2b() {}
void f_i2c() {}
void f_i2d() {}
void f_i2f() {}
void f_i2l() {}
void f_i2s() {}
void f_iadd() {}
void f_iaload() {}
void f_iand() {}
void f_iastore() {}
void f_iconst_m1() {}
void f_iconst_0() {}
void f_iconst_1() {}
void f_iconst_2() {}
void f_iconst_3() {}
void f_iconst_4() {}
void f_iconst_5() {}
void f_idiv() {}
void f_if_acmpeq() {}
void f_if_acmpne() {}
void f_if_icmpeq() {}
void f_if_icmpge() {}
void f_if_icmpgt() {}
void f_if_icmple() {}
void f_if_icmplt() {}
void f_if_icmpne() {}
void f_ifeq() {}
void f_ifge() {}
void f_ifgt() {}
void f_ifle() {}
void f_iflt() {}
void f_ifne() {}
void f_ifnonnull() {}
void f_ifnull() {}
void f_iinc() {}
void f_iload() {}
void f_iload_0() {}
void f_iload_1() {}
void f_iload_2() {}
void f_iload_3() {}
void f_impdep1() {}
void f_impdep2() {}
void f_imul() {}
void f_ineg() {}
void f_instanceof() {}
void f_invokedynamic() {}
void f_invokeinterface() {}
void f_invokespecial() {}
void f_invokestatic() {}
void f_invokevirtual() {}
void f_ior() {}
void f_irem() {}
void f_ireturn() {}
void f_ishl() {}
void f_ishr() {}
void f_istore() {}
void f_istore_0() {}
void f_istore_1() {}
void f_istore_2() {}
void f_istore_3() {}
void f_isub() {}
void f_iushr() {}
void f_ixor() {}
void f_jsr() {}
void f_jsr_w() {}
void f_l2d() {}
void f_l2f() {}
void f_l2i() {}
void f_ladd() {}
void f_laload() {}
void f_land() {}
void f_lastore() {}
void f_lcmp() {}
void f_lconst_0() {}
void f_lconst_1() {}
void f_ldc() {}
void f_ldc_w() {}
void f_ldc2_w() {}
void f_ldiv() {}
void f_lload() {}
void f_lload_0() {}
void f_lload_1() {}
void f_lload_2() {}
void f_lload_3() {}
void f_lmul() {}
void f_lneg() {}
void f_lookupswitch() {}
void f_lor() {}
void f_lrem() {}
void f_lreturn() {}
void f_lshl() {}
void f_lshr() {}
void f_lstore() {}
void f_lstore_0() {}
void f_lstore_1() {}
void f_lstore_2() {}
void f_lstore_3() {}
void f_lsub() {}
void f_lushr() {}
void f_lxor() {}
void f_monitorenter() {}
void f_monitorexit() {}
void f_multianewarray() {}
void f_new() {}
void f_newarray() {}
void f_nop() {}
void f_pop() {}
void f_pop2() {}
void f_putfield() {}
void f_putstatic() {}
void f_ret() {}
void f_return() {}
void f_saload() {}
void f_sastore() {}
void f_sipush() {}
void f_swap() {}
void f_tableswitch() {}
void f_wide() {}