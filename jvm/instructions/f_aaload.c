#include "base_instruction.h"
#include "arrays.h"

void f_aaload() {
	vlen_array* array = i_pop(vlen_array*);
	if (!array) {
		i_throw(NullPointerException);
		return;
	}

	int index = i_pop(int);

	if (index < 0 || index > array->len) {
		i_throw(ArrayIndexOutOfBoundsException);
		return;
	}

	i_push(array->data);
}
