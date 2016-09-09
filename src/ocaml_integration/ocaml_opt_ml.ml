(* External bigarray optimized array addition. *)

open Bigarray
open Unix

let size = 1000000;;
let iter = 100;;

external add_array : (float, float32_elt, c_layout) Array1.t -> 
                     (float, float32_elt, c_layout) Array1.t ->
                     (float, float32_elt, c_layout) Array1.t ->
                     unit = 
                     "bigarray_example";;

let get_time () = (times ()).tms_utime +. (times ()).tms_stime;;

let make_bigarray size = Array1.create float32 c_layout size;;

let x = make_bigarray size;;
let y = make_bigarray size;;
let z = make_bigarray size;;

let t = get_time ();;

for i = 1 to iter do
    let _ = add_array x y z in ();
done;

let ops = (float_of_int size) *. (float_of_int iter)
in
Printf.printf "%.1f\n" (1.e-6 *. ops /. (get_time () -. t));;

