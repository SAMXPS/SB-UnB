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

void f_d2f() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._float=value1._double};
	i_push(to_push);
}

void f_d2i() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._int=value1._double};
	i_push(to_push);
}

void f_d2l() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._long=value1._double};
	i_push(to_push);
}

void f_dadd() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}

	component ret = {.type=NUMERIC,._double = (value1._double + value2._double)};

	i_push(ret);
}

void f_daload() {
	// TODO: checar
	f_aaload();
}

void f_dastore() {

}

void f_dcmpg() {

}

void f_dcmpl() {

}

void f_dconst_0() {

}

void f_dconst_1() {

}

void f_ddiv() {
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	// result is value1 / value2
	component to_push = {.type=NUMERIC,._double=(value1._double/value2._double)};
	i_push(to_push);
}

void f_dload() {

}

void f_dload_0() {

}

void f_dload_1() {

}

void f_dload_2() {

}

void f_dload_3() {

}

void f_dmul() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._double=(value1._double*value2._double)};
	i_push(to_push);
}

void f_dneg() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}
	
	component to_push = {.type=NUMERIC,._double=(value1._double*(-1))};
	i_push(to_push);
}

void f_drem() {

}

void f_dreturn() {

}

void f_dstore_n(int index) {
	component objectref = i_pop();
	local_variable2 var = {._double=objectref._double};
	i_local_variable_set2(index, var);
}

void f_dstore() {
	f_dstore_n(i_is_wide() ? i_read_code_u2() : i_read_code_u1());
}

void f_dstore_0() {
	f_dstore_n(0);
}

void f_dstore_1() {
	f_dstore_n(1);
}

void f_dstore_2() {
	f_dstore_n(2);
}

void f_dstore_3() {
	f_dstore_n(3);
}

void f_dsub() {
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	// TODO type conversion??
	// result is value1 - value2
	component to_push = {.type=NUMERIC,._double=(value1._double-value2._double)};
	i_push(to_push);
}

void f_dup() {
	component to_dup = i_pop();
	i_push(to_dup);
	i_push(to_dup);
}

void f_dup_x1() {
	component value1 = i_pop();
	component value2 = i_pop();
	i_push(value1);
	i_push(value2);
	i_push(value1);
}

void f_dup_x2() {
	component value1 = i_pop();
	component value2 = i_pop();
	component value3 = i_pop();
	i_push(value1);
	i_push(value3);
	i_push(value2);
	i_push(value1);
}

void f_dup2() {
	// Cat 2???
}

void f_dup2_x1() {

}

void f_dup2_x2() {

}

void f_f2d() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._double=value1._float};
	i_push(to_push);
}

void f_f2i() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._int=value1._float};
	i_push(to_push);
}

void f_f2l() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._long=value1._float};
	i_push(to_push);
}

void f_fadd() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}

	component ret = {.type=NUMERIC,._float = (value1._float + value2._float)};

	i_push(ret);
}

void f_faload() {
	// TODO: checar
	f_aaload();
}

void f_fastore() {

}

void f_fcmpg() {

}

void f_fcmpl() {

}

void f_fconst_0() {

}

void f_fconst_1() {

}

void f_fconst_2() {

}

void f_fdiv() {
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	// result is value1 / value2
	component to_push = {.type=NUMERIC,._float=(value1._float/value2._float)};
	i_push(to_push);
}

void f_fload() {

}

void f_fload_0() {

}

void f_fload_1() {

}

void f_fload_2() {

}

void f_fload_3() {

}

void f_fmul() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._float=(value1._float*value2._float)};
	i_push(to_push);
}

void f_fneg() {

	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}
	
	component to_push = {.type=NUMERIC,._float=(value1._float*(-1))};
	i_push(to_push);
}

void f_frem() {

}

void f_freturn() {

}

void f_fstore() {

}

void f_fstore_0() {

}

void f_fstore_1() {

}

void f_fstore_2() {

}

void f_fstore_3() {

}

void f_fsub() {
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	// TODO type conversion??
	// result is value1 - value2
	component to_push = {.type=NUMERIC,._float=(value1._float-value2._float)};
	i_push(to_push);
}

void f_getfield() {

}

void f_getstatic() {

}

void f_goto() {

}

void f_goto_w() {

}

void f_i2b() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}
	// truncated to a byte, then sign-extended to an int result
	s1 my_byte = value1._int;
	component to_push = {.type=NUMERIC,._int=(s4)my_byte};
	i_push(to_push);
}

void f_i2c() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	// truncated to char, then zero-extended to an int result
	u1 my_char = value1._int;
	component to_push = {.type=NUMERIC,._int=(u4)my_char};
	i_push(to_push);
}

void f_i2d() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._double=(double) value1._int};
	i_push(to_push);
}

void f_i2f() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._float=(float) value1._int};
	i_push(to_push);
}

void f_i2l() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._long=(s4) value1._int};
	i_push(to_push);
}

void f_i2s() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._int=((s2) value1._int)};
	i_push(to_push);
}

void f_iadd() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}

	component ret = {.type=NUMERIC,._int = (value1._int + value2._int)};

	i_push(ret);
}

void f_iaload() {
	// TODO: checar
	f_aaload();
}

void f_iand() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._int=(value1._int&value2._int)};
	i_push(to_push);
}

void f_iastore() {

}

void f_iconst_m1() {

}

void f_iconst_0() {

}
void f_iconst_1() {

}

void f_iconst_2() {

}

void f_iconst_3() {

}

void f_iconst_4() {

}

void f_iconst_5() {

}

// Divide int
void f_idiv() {
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	// result is value1 / value2
	component to_push = {.type=NUMERIC,._int=(value1._int/value2._int)};
	i_push(to_push);
}

void f_if_acmpeq() {

}

void f_if_acmpne() {

}

void f_if_icmpeq() {

}

void f_if_icmpge() {

}

void f_if_icmpgt() {

}

void f_if_icmple() {

}

void f_if_icmplt() {

}

void f_if_icmpne() {

}

void f_ifeq() {

}

void f_ifge() {

}

void f_ifgt() {

}

void f_ifle() {

}

void f_iflt() {

}

void f_ifne() {

}

void f_ifnonnull() {

}

void f_ifnull() {

}

void f_iinc() {

}

void f_iload_n(int n) {
	local_variable var = i_local_variable(n);
	if (i_has_exception())
		return;
	component to_push = {.type=NUMERIC,._int=var._int};
	i_push(to_push);
}

// Load int from local variable
void f_iload() {
	u2 index = i_is_wide() ? i_read_code_u2() : i_read_code_u1();
	f_iload_n(index);
}

void f_iload_0() {
	f_iload_n(0);
}

void f_iload_1() {
	f_iload_n(1);
}

void f_iload_2() {
	f_iload_n(2);
}

void f_iload_3() {
	f_iload_n(3);
}

void f_impdep1() {

}

void f_impdep2() {

}

// Multiply int
void f_imul() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._int=(value1._int*value2._int)};
	i_push(to_push);
}

// Negate int
void f_ineg() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}
	
	component to_push = {.type=NUMERIC,._int=(value1._int*(-1))};
	i_push(to_push);
}

void f_instanceof() {

}

void f_invokedynamic() {

}

void f_invokeinterface() {

}

void f_invokespecial() {

}

void f_invokestatic() {

}

void f_invokevirtual() {

}

void f_ior() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._int=(value1._int|value2._int)};
	i_push(to_push);
}

void f_irem() {

}

void f_ireturn() {

}

void f_ishl() {
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	int s = (value2._int)&(0x1F);
	
	component to_push = {.type=NUMERIC,._int=(value1._int<<s)};
	i_push(to_push);
}

void f_ishr() {
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	int s = (value2._int)&(0x1F);
	
	component to_push = {.type=NUMERIC,._int=(value1._int>>s)};
	i_push(to_push);
}

// Store int into local variable
void f_istore_n(int index) {
	component value = i_pop();
	
	if (value.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}
	local_variable var = {._int=value._int};
	i_local_variable_set(index, var);
}

void f_istore() {
	f_istore_n(i_is_wide() ? i_read_code_u2() : i_read_code_u1());
}

void f_istore_0() {
	f_istore_n(0);
}

void f_istore_1() {
	f_istore_n(1);
}

void f_istore_2() {
	f_istore_n(2);
}

void f_istore_3() {
	f_istore_n(3);
}

// Subtract int
void f_isub() {
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	// result is value1 - value2
	component to_push = {.type=NUMERIC,._int=(value1._int-value2._int)};
	i_push(to_push);
}

// Logical shift right int
void f_iushr() {
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	int s = (value2._int)&(0x1F);

	// An int result is calculated by shifting value1 right by s bit positions, with zero extension, where s is the value of the low 5 bits of value2. 
	component to_push = {.type=NUMERIC,._uint=(value1._uint>>s)};
	i_push(to_push);
}

void f_ixor() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._int=(value1._int^value2._int)};
	i_push(to_push);
}

void f_jsr() {

}

void f_jsr_w() {

}

void f_l2d() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._double=value1._long};
	i_push(to_push);
}

void f_l2f() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._float=value1._long};
	i_push(to_push);
}

void f_l2i() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._int=value1._long};
	i_push(to_push);
}

void f_ladd() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}

	component ret = {.type=NUMERIC,._long = (value1._long + value2._long)};
	
	i_push(ret);
}

void f_laload() {
	// TODO: checar
	f_aaload();
}

void f_land() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._long=(value1._long&value2._long)};
	i_push(to_push);
}

void f_lastore() {

}

void f_lcmp() {

}

void f_lconst_0() {

}

void f_lconst_1() {

}

void f_ldc() {

}

void f_ldc_w() {

}

void f_ldc2_w() {

}

void f_ldiv() {
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	// result is value1 / value2
	component to_push = {.type=NUMERIC,._long=(value1._long/value2._long)};
	i_push(to_push);
}

void f_lload() {

}

void f_lload_0() {

}

void f_lload_1() {

}

void f_lload_2() {

}

void f_lload_3() {

}

void f_lmul() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._long=(value1._long*value2._long)};
	i_push(to_push);
}

void f_lneg() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}
	
	component to_push = {.type=NUMERIC,._long=(value1._long*(-1))};
	i_push(to_push);
}

void f_lookupswitch() {

}

void f_lor() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._long=(value1._long|value2._long)};
	i_push(to_push);
}

void f_lrem() {

}

void f_lreturn() {

}

void f_lshl() {
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	int s = (value2._int)&(0x3F);
	
	component to_push = {.type=NUMERIC,._long=(value1._long<<s)};
	i_push(to_push);
}

void f_lshr() {
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	int s = (value2._int)&(0x3F);
	
	component to_push = {.type=NUMERIC,._long=(value1._long>>s)};
	i_push(to_push);
}

void f_lstore_n(int index) {
	component objectref = i_pop();
	local_variable2 var = {._long=objectref._long};
	i_local_variable_set2(index, var);
}

void f_lstore() {
	f_lstore_n(i_is_wide() ? i_read_code_u2() : i_read_code_u1());
}

void f_lstore_0() {
	f_lstore_n(0);
}

void f_lstore_1() {
	f_lstore_n(1);
}

void f_lstore_2() {
	f_lstore_n(2);
}

void f_lstore_3() {
	f_lstore_n(3);
}

void f_lsub() {
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	// result is value1 - value2
	component to_push = {.type=NUMERIC,._long=(value1._long-value2._long)};
	i_push(to_push);
}

void f_lushr() {
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	int s = (value2._int)&(0x3F);
	
	component to_push = {.type=NUMERIC,._ulong=(value1._ulong>>s)};
	i_push(to_push);
}

void f_lxor() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC,._long=(value1._long^value2._long)};
	i_push(to_push);
}

void f_monitorenter() {
	// Não implementado
	i_throw(RuntimeException);
}

void f_monitorexit() {
	// Não implementado
	i_throw(RuntimeException);
}

void f_multianewarray() {

}

void f_new() {

}

void f_newarray() {

}

// Do nothing
void f_nop() {
	// Instrução mais legal de implementar :)
	// Deixa qualquer programador feliz ler: Do nothing
}

void f_pop() {
	i_pop();
}

void f_pop2() {
	// cat 2 deve ser assim? vamos assumir....
	i_pop();
	i_pop();
}

void f_putfield() {

}

void f_putstatic() {

}

void f_ret() {

}

void f_return() {
	component c = {.type=VOID_RETURN,.u8=0L};
	i_return(c);
}

void f_saload() {
	// TODO: checar
	f_aaload();
}

void f_sastore() {

}

void f_sipush() {
	u2 sshort = i_read_code_u2();

	s4 extend = (s4)(*((s2*)&sshort));
	component to_push = {.type=NUMERIC,._int=extend};

	i_push(to_push);
}

// Swap the top two operand stack values
void f_swap() {
	component value_1 = i_pop();
	component value_2 = i_pop();
	i_push(value_1);
	i_push(value_2);
}

void f_tableswitch() {
	// TODO
}

void f_wide() {
	i_set_wide();
}