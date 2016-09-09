(* External function for adding arrays. *)

open Unix

let size = 10000000;;
let iter = 100;;

external add_array : float array -> 
                     float array -> 
                     float array = 
                     "array_example";;

let get_time () = (times ()).tms_utime +. (times ()).tms_stime;;

let make_array size = Array.make size 1.;;

let x = make_array size;;
let y = make_array size;;

let t = get_time ();;

for i = 1 to iter do
    let _ = add_array x y in ();
done;

let ops = (float_of_int size) *. (float_of_int iter)
in
Printf.printf "%.1f\n" (1.e-6 *. ops /. (get_time () -. t));;
