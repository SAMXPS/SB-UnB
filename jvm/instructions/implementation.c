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

	component arraylen = {.type=NUMERIC};
	arraylen._int = arrayref.array->len;
	
	i_push(arraylen);
}

// Store reference into local variable
void f_astore_n(int n) {
	component objectref = i_pop();
	local_variable var; 
	var.reference=objectref;
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
	component to_push = {.type=NUMERIC};
	to_push._int=my_bool._byte;

	i_push(to_push);
}

void f_bastore() {
	// A implementação de array é a mesma para bytes e booleanos nessa jvm.
	f_astore();
}

void f_bipush() {
	u1 byte = i_read_code_u1();

	s4 extend = (s4)(*((s1*)&byte));
	component to_push = {.type=NUMERIC};
	to_push._int=extend;

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
	// TODO: implementar tipos etc etc etc
}

void f_d2f() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._float=value1._double;
	i_push(to_push);
}

void f_d2i() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._int=value1._double;
	i_push(to_push);
}

void f_d2l() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._long=value1._double;
	i_push(to_push);
}

void f_dadd() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}

	component ret = {.type=NUMERIC};
	ret._double = (value1._double + value2._double);

	i_push(ret);
}

void f_daload() {
	// TODO: checar
	f_aaload();
}

void f_dastore() {
	// TODO: checar
	f_aastore();
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
	component to_push = {.type=NUMERIC};
	to_push._double=(value1._double/value2._double);
	i_push(to_push);
}

void f_dload_n(int index)  {
	local_variable2 var = i_local_variable2(index);
	if (i_has_exception())
		return;
	component to_push = {.type=NUMERIC};
	to_push._double=var._double;
	i_push(to_push);
}

void f_dload() {
	u2 index = i_is_wide() ? i_read_code_u2() : i_read_code_u1();
	f_dload_n(index);
}

void f_dload_0() {
	f_dload_n(0);
}

void f_dload_1() {
	f_dload_n(1);
}

void f_dload_2() {
	f_dload_n(2);
}

void f_dload_3() {
	f_dload_n(3);
}

void f_dmul() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._double=(value1._double*value2._double);
	i_push(to_push);
}

void f_dneg() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}
	
	component to_push = {.type=NUMERIC};
	to_push._double=(value1._double*(-1));
	i_push(to_push);
}

void f_drem() {

}

void f_dreturn() {

}

void f_dstore_n(int index) {
	component objectref = i_pop();
	local_variable2 var;
	var._double=objectref._double;
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
	component to_push = {.type=NUMERIC};
	to_push._double=(value1._double-value2._double);
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

	component to_push = {.type=NUMERIC};
	to_push._double=value1._float;
	i_push(to_push);
}

void f_f2i() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._int=value1._float;
	i_push(to_push);
}

void f_f2l() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._long=value1._float;
	i_push(to_push);
}

void f_fadd() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}

	component ret = {.type=NUMERIC};
	ret._float = (value1._float + value2._float);

	i_push(ret);
}

void f_faload() {
	// TODO: checar
	f_aaload();
}

void f_fastore() {
	// TODO: checar
	f_astore();
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
	component to_push = {.type=NUMERIC};
	to_push._float=(value1._float/value2._float);
	i_push(to_push);
}

void f_fload_n(int n) {
	local_variable var = i_local_variable(n);
	if (i_has_exception())
		return;
	component to_push = {.type=NUMERIC};
	to_push._float=var._float;
	i_push(to_push);
}

void f_fload() {
	u2 index = i_is_wide() ? i_read_code_u2() : i_read_code_u1();
	f_fload_n(index);
}

void f_fload_0() {
	f_fload_n(0);
}

void f_fload_1() {
	f_fload_n(1);
}

void f_fload_2() {
	f_fload_n(2);
}

void f_fload_3() {
	f_fload_n(3);
}

void f_fmul() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._float=(value1._float*value2._float);
	i_push(to_push);
}

void f_fneg() {

	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}
	
	component to_push = {.type=NUMERIC};
	to_push._float=(value1._float*(-1));
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
	component to_push = {.type=NUMERIC};
	to_push._float=(value1._float-value2._float);
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
	component to_push = {.type=NUMERIC};
	to_push._int=(s4)my_byte;
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
	component to_push = {.type=NUMERIC};
	to_push._int=(u4)my_char;
	i_push(to_push);
}

void f_i2d() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._double=(double) value1._int;
	i_push(to_push);
}

void f_i2f() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._float=(float) value1._int;
	i_push(to_push);
}

void f_i2l() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._long=(s4) value1._int;
	i_push(to_push);
}

void f_i2s() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._int=((s2) value1._int);
	i_push(to_push);
}

void f_iadd() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}

	component ret = {.type=NUMERIC};
	ret._int = (value1._int + value2._int);

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

	component to_push = {.type=NUMERIC};
	to_push._int=(value1._int&value2._int);
	i_push(to_push);
}

void f_iastore() {
	// TODO: checar
	f_aastore();
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
	component to_push = {.type=NUMERIC};
	to_push._int=(value1._int/value2._int);
	i_push(to_push);
}

void f_if_acmpeq() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type == value2.type && value1.u8 == value2.u8) {
		i_add_to_pc(branchbytes);
	}
}

void f_if_acmpne() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != value2.type || value1.u8 != value2.u8) {
		i_add_to_pc(branchbytes);
	}
}

void f_if_icmpeq() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}

	if (value1._int == value2._int) {
		i_add_to_pc(branchbytes);
	}
}

void f_if_icmpge() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}
	//value1 >= value2
	if (value1._int >= value2._int) {
		i_add_to_pc(branchbytes);
	}
}

void f_if_icmpgt() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}
	//value1 > value2
	if (value1._int > value2._int) {
		i_add_to_pc(branchbytes);
	}
}

void f_if_icmple() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}
	//value1 <= value2
	if (value1._int <= value2._int) {
		i_add_to_pc(branchbytes);
	}
}

void f_if_icmplt() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}
	//value1 < value2
	if (value1._int < value2._int) {
		i_add_to_pc(branchbytes);
	}
}

void f_if_icmpne() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value2 = i_pop();
	component value1 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}
	// value1 != value2
	if (value1._int != value2._int) {
		i_add_to_pc(branchbytes);
	}
}

void f_ifeq() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value1 = i_pop();

	if (value1.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}
	
	if (value1._int == 0) {
		i_add_to_pc(branchbytes);
	}
}

void f_ifge() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value1 = i_pop();

	if (value1.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}
	
	if (value1._int >= 0) {
		i_add_to_pc(branchbytes);
	}
}

void f_ifgt() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value1 = i_pop();

	if (value1.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}
	
	if (value1._int > 0) {
		i_add_to_pc(branchbytes);
	}
}

void f_ifle() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value1 = i_pop();

	if (value1.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}
	
	if (value1._int <= 0) {
		i_add_to_pc(branchbytes);
	}
}

void f_iflt() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value1 = i_pop();

	if (value1.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}
	
	if (value1._int < 0) {
		i_add_to_pc(branchbytes);
	}
}

void f_ifne() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value1 = i_pop();

	if (value1.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}
	
	if (value1._int != 0) {
		i_add_to_pc(branchbytes);
	}
}

void f_ifnonnull() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value1 = i_pop();
	
	if (value1.type != NULL_REFERENCE) {
		i_add_to_pc(branchbytes);
	}
}

void f_ifnull() {
	u2 unzigned =  i_read_code_u2();
	s2 branchbytes = *(s2*)(&unzigned);
	
	component value1 = i_pop();
	
	if (value1.type == NULL_REFERENCE) {
		i_add_to_pc(branchbytes);
	}
}

void f_iinc() {
	u1 index = i_read_code_u1();
	u1 unzigned = i_read_code_u1();
	s1 conzt = *((s1*)(&unzigned)); // extensão de sinal
	local_variable var = i_local_variable(index);

	if (i_has_exception())
		return;

	var._int += conzt;
	i_local_variable_set(index, var);
}

void f_iload_n(int n) {
	local_variable var = i_local_variable(n);
	if (i_has_exception())
		return;
	component to_push = {.type=NUMERIC};
	to_push._int=var._int;
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

	component to_push = {.type=NUMERIC};
	to_push._int=(value1._int*value2._int);
	i_push(to_push);
}

// Negate int
void f_ineg() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}
	
	component to_push = {.type=NUMERIC};
	to_push._int=(value1._int*(-1));
	i_push(to_push);
}

void f_instanceof() {

}

void f_invokedynamic() {
	exit_jvm("Instrucao f_invokedynamic NAO IMPLEMENTADA.");
}

void f_invokeinterface() {
	exit_jvm("Instrucao f_invokeinterface NAO IMPLEMENTADA.");
}

c_method* f_invoke() {
	u2 index = i_read_code_u2();
	cp_info* method_ref = i_read_cp(index);
	return i_find_method(method_ref);
}

void f_invokespecial() {
	i_invoke_special(f_invoke());
}

void f_invokestatic() {
	i_invoke_static(f_invoke());
}

void f_invokevirtual() {
	i_invoke_virtual(f_invoke());
}

void f_ior() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._int=(value1._int|value2._int);
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
	
	component to_push = {.type=NUMERIC};
	to_push._int=(value1._int<<s);
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
	
	component to_push = {.type=NUMERIC};
	to_push._int=(value1._int>>s);
	i_push(to_push);
}

// Store int into local variable
void f_istore_n(int index) {
	component value = i_pop();
	
	if (value.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}
	local_variable var;
	var._int=value._int;
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
	component to_push = {.type=NUMERIC};
	to_push._int=(value1._int-value2._int);
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
	component to_push = {.type=NUMERIC};
	to_push._uint=(value1._uint>>s);
	i_push(to_push);
}

void f_ixor() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._int=(value1._int^value2._int);
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

	component to_push = {.type=NUMERIC};
	to_push._double=value1._long;
	i_push(to_push);
}

void f_l2f() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._float=value1._long;
	i_push(to_push);
}

void f_l2i() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._int=value1._long;
	i_push(to_push);
}

void f_ladd() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC) {
		i_throw(RuntimeException);
		return;
	}

	component ret = {.type=NUMERIC};
	ret._long = (value1._long + value2._long);
	
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

	component to_push = {.type=NUMERIC};
	to_push._long=(value1._long&value2._long);
	i_push(to_push);
}

void f_lastore() {
	// TODO: checar
	f_aastore();
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
	component to_push = {.type=NUMERIC};
	to_push._long=(value1._long/value2._long);
	i_push(to_push);
}

void f_lload_n(int index) {
	local_variable2 var = i_local_variable2(index);
	if (i_has_exception())
		return;
	component to_push = {.type=NUMERIC};
	to_push._long=var._long;
	i_push(to_push);
}

void f_lload() {
	u2 index = i_is_wide() ? i_read_code_u2() : i_read_code_u1();
	f_lload_n(index);
}

void f_lload_0() {
	f_lload_n(0);
}

void f_lload_1() {
	f_lload_n(1);
}

void f_lload_2() {
	f_lload_n(2);
}

void f_lload_3() {
	f_lload_n(3);
}

void f_lmul() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._long=(value1._long*value2._long);
	i_push(to_push);
}

void f_lneg() {
	component value1 = i_pop();

	if (value1.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}
	
	component to_push = {.type=NUMERIC};
	to_push._long=(value1._long*(-1));
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

	component to_push = {.type=NUMERIC};
	to_push._long=(value1._long|value2._long);
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
	
	component to_push = {.type=NUMERIC};
	to_push._long=(value1._long<<s);
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
	
	component to_push = {.type=NUMERIC};
	to_push._long=(value1._long>>s);
	i_push(to_push);
}

void f_lstore_n(int index) {
	component objectref = i_pop();
	local_variable2 var;
	var._long=objectref._long;
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
	component to_push = {.type=NUMERIC};
	to_push._long=(value1._long-value2._long);
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
	
	component to_push = {.type=NUMERIC};
	to_push._ulong=(value1._ulong>>s);
	i_push(to_push);
}

void f_lxor() {
	component value1 = i_pop();
	component value2 = i_pop();

	if (value1.type != NUMERIC || value2.type != NUMERIC){
		i_throw(RuntimeException);
		return;
	}

	component to_push = {.type=NUMERIC};
	to_push._long=(value1._long^value2._long);
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
	component c = {.type=VOID_RETURN};
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
	component to_push = {.type=NUMERIC};
	to_push._int=extend;

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