/* Explicit decoding/encoding of array to compute result. */

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>

CAMLprim value array_example(value x, value y) {

    CAMLparam2(x, y);
    CAMLlocal1(result);

    int i;
    int l = Wosize_val(x);;
    double temp;

    result = caml_alloc(l * Double_wosize, Double_array_tag);

    for (i = 0; i < l; i++) {
        temp = Double_field(x, i) + Double_field(y, i);
        Store_double_field(result, i, temp);
    }

    CAMLreturn(result);
}
