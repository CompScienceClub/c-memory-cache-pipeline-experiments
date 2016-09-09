/* In-place computation based on passed bigarray pointers. */

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/bigarray.h>

CAMLprim value bigarray_example (value x, value y, value z) {
    
    CAMLparam3(x, y, z);
    
    int i;
    int l = Caml_ba_array_val(x)->dim[0];
    float *a = Data_bigarray_val(x);
    float *b = Data_bigarray_val(y);
    float *c = Data_bigarray_val(z);

    for (i = 0; i < l; i++) {
        c[i] = a[i] + b[i];
    }

    CAMLreturn(Val_unit);
}
