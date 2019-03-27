type 'a witness =
  | Int    : int witness
  | Float  : float witness
  | String : string witness

let print (type a) (witness: a witness) (value: a) : unit =
  let str =
    match witness with
    | Int    -> string_of_int value
    | Float  -> string_of_float value
    | String -> "\"" ^ value ^ "\""
  in
  print_endline str
