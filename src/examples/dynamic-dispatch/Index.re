module type Database_intf = {
  type t;
  type data;

  let keys: t => list(string);
  let get: t => string => data;
  let set: t => string => data => t;
};

type genericDatabase('data) =
  GenericDatabase(
    (module Database_intf with type t = 'a and type data = 'data),
    'a
  ): genericDatabase('data);

module type Database_creatable_intf = {
  include Database_intf;
  type createArgs;
  let create: createArgs => t;
};

module type Database_generalized_intf = {
  include Database_intf;
  type createArgs;
  let create: createArgs => genericDatabase(data);
};

module Generalize(Db: Database_creatable_intf):
  Database_generalized_intf
    with type t = Db.t
     and type data = Db.data
     and type createArgs = Db.createArgs
= {
  include Db;

  let create = (args) => GenericDatabase((module Db), Db.create(args))
};

let keys =
  ( type data,
    GenericDatabase((module Db), db): genericDatabase(data)
  ): list(string) =>
    Db.keys(db);

let get =
  ( type data,
    GenericDatabase((module Db), db): genericDatabase(data),
    key: string
  ): data =>
    Db.get(db, key);

let set =
  ( type data,
    GenericDatabase((module Db), db): genericDatabase(data),
    key: string,
    value: data
  ): genericDatabase(data) =>
     GenericDatabase((module Db), Db.set(db, key, value));

let transfer =
  ( srcDb: genericDatabase('src),
    dstDb: genericDatabase('dst),
    func: 'src => 'dst
  ): genericDatabase('dst) =>
     List.fold_left(
       (db, key) => set(db, key, func(get(srcDb, key))),
       dstDb,
       keys(srcDb)
     );

module StringMap = Map.Make({
  type t = string;
  let compare = compare;
});

module type Type_intf = {
  type t
};

module Make_in_memory_db(Type: Type_intf):
  Database_creatable_intf
    with type data = Type.t
     and type createArgs = unit
= {
  type t = StringMap.t(Type.t);
  type data = Type.t;
  type createArgs = unit;

  let create = () => StringMap.empty;
  let keys = (map) => List.map(((k,_)) => k, StringMap.bindings(map));
  let get = (map, key) => StringMap.find(key, map);
  let set = (map, key, value) => StringMap.add(key, value, map);
};

module StringDbA =
  Generalize(Make_in_memory_db({ type t = string }));
module StringDbB =
  Generalize(Make_in_memory_db({ type t = string }));
module IntDb =
  Generalize(Make_in_memory_db({ type t = int }));

let test = () => {
  let db_a =
    StringDbA.create()
    |. set("x", "0")
    |. set("y", "42")
    |. set("z", "-143");
  let db_b = transfer(db_a, StringDbB.create(), (x) => x);
  let db_c = transfer(db_b, IntDb.create(), int_of_string);

  List.iter((k) => Printf.printf("%s: %d\n", k, get(db_c, k)), keys(db_c));
};

test();
// x: 0
// y: 42
// z: -143
