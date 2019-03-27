type value =
  | Int(int)
  | Float(float)
  | String(string);

let print = (v: value) => {
  let str = switch(v) {
    | Int(n)    => string_of_int(n)
    | Float(f)  => string_of_float(f)
    | String(s) => "\"" ++ s ++ "\""
  };
  print_endline(str);
};

type hlist = list(value)

let partial_map = (values: hlist, func: value => option(value)): hlist =>
  List.map(
    (v) =>
      switch(func(v)) {
        | Some(v') => v'
        | None     => v
      },
    values
  );

let test = () => {
  let ls = [
    Int(5),
    String("hello"),
    Int(2),
    Float(3.5),
    Int(16)
  ];
  let ls' = partial_map(ls, (value) =>
    switch(value) {
      | Int(n) => Some (Int(n * 2))
      | _      => None
    }
  );
  List.iter(print, ls');
};

test();
// 10
// hello
// 4
// 3.5
// 32
