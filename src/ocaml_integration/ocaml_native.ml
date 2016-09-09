(* Native array add as imperative as possible. *)

open Unix

let size = 10000000;;
let iter = 100;;

let get_time () = (times ()).tms_utime +. (times ()).tms_stime;;

let x = Array.make size 1.;;
let y = Array.make size 1.;;

let t = get_time ();;

for i = 1 to iter do
    for j = 0 to (size - 1) do
        let _ = x.(j) +. y.(j) in ();
    done;
done;

let ops = (float_of_int size) *. (float_of_int iter)
in
Printf.printf "%.1f\n" (1.e-6 *. ops /. (get_time () -. t));;
