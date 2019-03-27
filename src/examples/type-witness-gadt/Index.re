type witness('a) =
  | Int: witness(int)
  | Float: witness(float)
  | String: witness(string);

let print = (type a, witness: witness(a), value: a) => {
  let str = switch(witness) {
    | Int    => string_of_int(value)
    | Float  => string_of_float(value)
    | String => "\"" ++ value ++ "\""
  };
  print_endline(str);
};

type item = Item(witness('a), 'a): item
type hlist = list(item)

let map_equal_witness = (type a, type b, target: witness(a), candidate: witness(b), value: b, func: a => a): b =>
  switch((target, candidate)) {
    | (Int, Int)       => func(value)
    | (Float, Float)   => func(value)
    | (String, String) => func(value)
    | _                => value
  };

let map_type = (type a, ls: hlist, witness: witness(a), func: a => a): hlist =>
  List.map(
    (Item(w, v)) =>
      Item(w, map_equal_witness(witness, w, v, func)),
    ls
  );

let test = () => {
  let ls = [
    Item(Int, 5),
    Item(String, "hello"),
    Item(Int, 2),
    Item(Float, 3.5),
    Item(Int, 16)
  ];
  let ls' = map_type(ls, Int, (n) => n * 2);
  List.iter((Item(w, v)) => print(w, v), ls');
};

test();
// 10
// hello
// 4
// 3.5
// 32
