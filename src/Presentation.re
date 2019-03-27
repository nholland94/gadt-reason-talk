open BsSpectacle;
let s = ReasonReact.string;

[@bs.module("spectacle-theme-nova")] external createTheme: unit => Theme.theme = "default";

[@bs.module]
external typeWitnessADTCode: string = "!!raw-loader!./examples/type-witness-adt/Index.re";
[@bs.module]
external typeWitnessGADTCode: string = "!!raw-loader!./examples/type-witness-gadt/Index.re";
[@bs.module]
external dynamicDispatchCode: string = "!!raw-loader!./examples/dynamic-dispatch/Index.re";

// let theme = {
//   open Theme;
//   createTheme(
//     {primary: "#26A0D1", secondary: "white", tertiary: "#505050", quarternary: "white"},
//     {
//       primary: {name: "Merriweather", googleFont: true, styles: [|"300"|]},
//       secondary: {name: "Roboto", googleFont: true, styles: [|"100"|]},
//       tertiary: simpleFont("monospace")
//     }
//   )
// }

/*
<Slide>
  <Heading>
    (s("Heterogeneous lists"))
  </Heading>
  <PrismCode
    lang="reason"
    code={{|
      // homogeneous list
      let things: list(string) = [
        "Apple",
        "4",
        "3.5"
      ];

      // heterogeneous list
      // NOTE: does not compile
      let things: hlist = [
        "Apple",
        4,
        3.5
      ];
    |}} />
</Slide>
*/

let theme = createTheme();
let component = ReasonReact.statelessComponent("Presentation");

let make = (_children) => {
  ...component,
  render: (_self) => {
    <Deck transition=[|Slide|] progress=`pacman controls=false theme>

      <Slide>
        <Heading textColor="secondary" textFont="secondary">
          (s("Better Libraries Using GADTs"))
        </Heading>
        <Text>
          <S type_=`italic>(s("Nathan Holland"))</S>
        </Text>
        <Notes>
          <ul>
            <li>(s("we will be using reason syntax"))</li>
          </ul>
        </Notes>
      </Slide>

      <Slide>
        <Heading>(s("Goal: a basic introduction"))</Heading>
        <Notes>
          <ul>
            <li>(s("goal of this talk is not to give a complete understanding, but to motivate"))</li>
            <li>(s("we will look at a lot of code, don't make your goal to understand all of it, just the gist"))</li>
          </ul>
        </Notes>
      </Slide>

      <Slide>
        <Heading size=2>(s("Why GADTs?"))</Heading>
        <Notes>
          <ul>
            <li>(s("strongly statically typed languages are great, but often type level abstraction leaks"))</li>
            <li>(s("GADTs can help us abstract more from the user of a library"))</li>
            <li>(s("they can also enable developers to write safer and more performant code"))</li>
            <li>(s("we will focus on library abstractions in this talk"))</li>
          </ul>
        </Notes>
      </Slide>

      <Slide><Heading size=2>(s("An Example in the Wild: ocaml-graphql-server"))</Heading></Slide>

      <Slide>
        <BlockQuote>
          <Quote textSize="24">
            (s("Initially, I thought the lack of generics in Go was the root of the issue. Out of curiosity, I looked into graphql-java, and noticed that it offered equally bad type safety guarantees. [...] This was the starting point of a journey to try to implement a GraphQL library with better type safety guarantees than were offered at the time."))
          </Quote>
          <Cite>(s({js|Andreas Garnæs - Creator of ocaml-graphql-server|js}))</Cite>
        </BlockQuote>
        <Notes>
          (s("creator of ocaml-graphql-server originally tried writing a library in Go and other statically typed languages"))
        </Notes>
      </Slide>

      <Slide>
        <Heading size=2>(s("What the heck is a GADT anyway?"))</Heading>
        <Heading size=3>(s("GADT = Generalized ADT"))</Heading>
        <Heading size=3>(s("ADT = Algebraic Data Type"))</Heading>
        <Notes>
          <ul>
            <li>(s("you may or may not have heard of them"))</li>
            <li>(s("you probably know what an ADT is, even if you don't recognize the name"))</li>
          </ul>
        </Notes>
      </Slide>

      <CodeSlide
        lang="reason"
        className="big-code"
        showLineNumbers=false
        code={"\
type example =
  | A
  | B(int)
  | C(string, float);"}
        ranges=[|
          CodeSlide.range(
            ~loc=[|0, 4|],
            ~title="ADT",
            ())
        |] />

      <CodeSlide
        lang="reason"
        className="big-code"
        showLineNumbers=false
        code={"\
type example('a) =
  | A('a)
  | B('a, int)
  | C(list('a));"}
        ranges=[|
          CodeSlide.range(~loc=[|0, 4|], ~title="ADT with Type Parameter", ())
        |] />

      <CodeSlide
        lang="reason"
        className="big-code"
        showLineNumbers=false
        code={"\
type example('a) =
  | A: example(int)
  | B(string): example(float)
  | C(list('a)): example('a)"}
        ranges=[|
          CodeSlide.range(
            ~loc=[|0, 4|],
            ~title="GADT",
            ())
        |] />

      <Slide>
        <Heading>(s("Prompt"))</Heading>
        <Text>
          (s("\
Sometimes we want to represent lists containing values of multiple types (for instance, a list of strings and ints). \
Let's create a library in ReasonML for lists of mixed types and expose an interface which allows users of the \
library to map over specific types in the list."))
        </Text>
        <Notes>
          (s("in a dynamic programming language like Javascript, this is arbitrary, but not in strongly statically typed languages like OCaml/ReasonML"))
        </Notes>
      </Slide>

      <Slide><Heading size=2>(s("Example application: URL encoding string parameters"))</Heading></Slide>

      <CodeSlide
        lang="reason"
        code={"\
let path = \"/api/v1/model\"
let parameters = [
  (\"name\", \"Steve\")
  (\"description\", \"The one and only\"),
  (\"id\", 15)
];

// how can this be implemented?
let encodedParameters = urlEncode(parameters);
let url = sprintf(\"%s?%s\", path, joinParameters(encodedParameters);"}
        ranges=[|CodeSlide.range(~loc=[|0, 13|], ~title="URL Encoding Pseudo-Code", ())|] />

      <CodeSlide
        lang="reason"
        code={"\
let escapeString = (string) => ...;
map_type(parameters, String, escapeString);
"}
        ranges=[|CodeSlide.range(~loc=[|0, 2|], ~title="Tentative urlEncode Implementation", ())|] />

      <Slide>
        <Heading>(s("Lists and Hlists"))</Heading>
        <Notes>(s("problem: we can't just mix types in lists be default"))</Notes>
      </Slide>

      <CodeSlide
        lang="reason"
        code={"\
let things: list(string) = [
  \"Apple\",
  \"4\",
  \"3.5\"
];

// invalid!
let things: hlist = [
  \"Apple\",
  4,
  3.5
];"}
        ranges=[|
          CodeSlide.range(~loc=[|0, 5|], ~title="Homogeneous List", ()),
          CodeSlide.range(~loc=[|6, 12|], ~title="Heterogeneous List", ())
        |] />

/*
      <Slide><Heading>(s("ADT vs. GADT Hlist Interface"))</Heading></Slide>

      <CodeSlide
        lang="reason"
        code={"\
let ls = [
  Int(5),
  String(\"hello\"),
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



let ls = [
  Item(Int, 5),
  Item(String, \"hello\"),
  Item(Int, 2),
  Item(Float, 3.5),
  Item(Int, 16)
];
let ls' = map_type(ls, Int, (n) => n * 2);"}
        ranges=[|
          CodeSlide.range(~loc=[|0, 13|], ~title="ADT Interface", ()),
          CodeSlide.range(~loc=[|16, 24|], ~title="GADT Interface", ())
        |] />

*/

      <Slide>
        <Heading>
          (s("ADT Implementation of Hlists"))
        </Heading>
        <Notes>
          <ul>
            <li>(s("refamiliarize ourselves with ADTs"))</li>
            <li>(s("provide a case to contrast against GADTs"))</li>
            <li>(s("prompt: heterogeneous lists"))</li>
          </ul>
        </Notes>
      </Slide>

      <CodeSlide
        lang="reason"
        code=typeWitnessADTCode
        ranges=[|
          CodeSlide.range(~loc=[|0, 4|], ~title="Defining Values", ()),
          CodeSlide.range(~loc=[|5, 13|], ~title="Printing Values", ()),
          CodeSlide.range(~loc=[|14, 15|], ~title="Defining an Hlist", ()),
          CodeSlide.range(~loc=[|16, 25|], ~title="An Operation on Value Lists", ()),
          CodeSlide.range(~loc=[|18, 23|], ()),
          CodeSlide.range(~loc=[|26, 42|], ~title="Using the Interface", ()),
          CodeSlide.range(~loc=[|27, 34|], ~title="Creating a List", ()),
          CodeSlide.range(~loc=[|34, 40|], ~title="Mapping Over Specific Types", ()),
          CodeSlide.range(~loc=[|40, 41|], ~title="Printing the List", ()),
          CodeSlide.range(~loc=[|43, 49|], ~title="Output", ()),
          CodeSlide.range(~loc=[|26, 42|], ~title="Analysis of the ADT Interface", ())
        |] />

      <Slide><Heading>(s("We can do better than this!"))</Heading></Slide>

      <CodeSlide
        lang="reason"
        code=typeWitnessGADTCode
        ranges=[|
          CodeSlide.range(~loc=[|0, 4|], ~title="Defining a Witness", ()),
          CodeSlide.range(~loc=[|5, 13|], ~title="Printing with a Witness", ()),
          CodeSlide.range(~loc=[|14, 16|], ~title="Defining an Hlist", ()),
          CodeSlide.range(~loc=[|14, 15|], ~title="Hiding a Type Parameter", ()),
          CodeSlide.range(~loc=[|17, 31|], ~title="A Higher Level Operation Hlists", ()),
          CodeSlide.range(~loc=[|17, 24|], ~title="First, a Helper", ()),
          CodeSlide.range(~loc=[|25, 31|], ~title="A Better Interface for Mapping Types", ()),
          CodeSlide.range(~loc=[|33, 43|], ~title="Using the Interface", ()),
          CodeSlide.range(~loc=[|33, 40|], ~title="Creating an Hlist", ()),
          CodeSlide.range(~loc=[|40, 41|], ~title="Mapping Over Specific Types", ()),
          CodeSlide.range(~loc=[|41, 42|], ~title="Printing the List", ()),
          CodeSlide.range(~loc=[|44, 50|], ~title="Output", ()),
          CodeSlide.range(~loc=[|33, 43|], ~title="Analysis of the GADT Interface", ())
        |] />

      <Slide>
        <Heading>
          (s("A quick note on \"Hlists\""))
        </Heading>
        <Notes>
          <ul>
            <li>(s("what we defined is a \"dynamic hlist\" (runtime encoded)"))</li>
            <li>(s("mention \"static hlists\" abstractly"))</li>
          </ul>
        </Notes>
      </Slide>

      <Slide><Heading size=2>(s("Another example: Dynamic Dispatch"))</Heading></Slide>

      <CodeSlide
        lang="java"
        code={"\
public interface DatabaseInterface<D> {
  String[] keys();
  D get(String str);
  void set(String str, D data);
}

public StringDatabase implements DatabaseInterface<String> {
  // ...
}

public IntDatabase implements DatabaseInterface<Int> {
  // ...
}"}
        ranges=[|
          CodeSlide.range(~loc=[|0, 13|], ~title="Dynamic Dispatch in OOP", ())
        |] />

      <Slide>
        <Heading size=2>
          (s("Approaching the Problem in OCaml/ReasonML"))
        </Heading>
        <Notes>
          <ul>
            <li>(s("could use classes, but bad choice (low community knowledge, leaky abstraction)"))</li>
            <li>(s("raw first class modules are too leaky and verbose by themselves"))</li>
            <li>(s("solution: first class modules with GADTs"))</li>
          </ul>
        </Notes>
      </Slide>

      <CodeSlide
        lang="reason"
        code={"\
let transfer =
  ( (module SrcDb):
      (module Database_intf
        with type t = 'srcDb
         and type data = 'src),
    srcDb: 'srcDb,
    (module DstDb):
      (module Database_intf
        with type t = 'dstDb
         and type data = 'dst),
    dstDb: 'dstDb,
    func: 'src => 'dst
  ): 'dstDb =>
    List.fold_left(
      (db, key) =>
        DstDb.set(db, key, func(SrcDb.get(srcDb, key)),
      dstDb,
      SrcDb.keys(srcDb)
    );



let transfer =
  ( srcDb: genericDatabase('src),
    dstDb: genericDatabase('dst),
    func: 'src => 'dst
  ): genericDatabase('dst) =>
     List.fold_left(
       (db, key) => set(db, key, func(get(srcDb, key))),
       dstDb,
       keys(srcDb)
     );"}
        ranges=[|
          CodeSlide.range(~loc=[|0, 19|], ~title="Without a Generalized Representation", ()),
          CodeSlide.range(~loc=[|21, 32|], ~title="With a Generalized Representation (Dynamic Dispatch)", ())
        |] />

      <CodeSlide
        lang="reason"
        code=dynamicDispatchCode
        ranges=[|
          CodeSlide.range(~loc=[|0, 8|], ~title="A Signature for Databases", ()),
          CodeSlide.range(~loc=[|9, 14|], ~title="A Generalized Representation for Databases", ()),
          CodeSlide.range(~loc=[|15, 26|], ~title="Signature Supersets", ()),
          CodeSlide.range(~loc=[|27, 37|], ~title="A Functor for Generalizing Database Implementations", ()),
          CodeSlide.range(~loc=[|38, 58|], ~title="Wrapping Generalized Databases with Dynamic Dispatch", ()),
          CodeSlide.range(~loc=[|59, 69|], ~title="Creating a High Level Function", ()),
          CodeSlide.range(~loc=[|70, 93|], ~title="A Helper for Defining In Memory Databases", ()),
          CodeSlide.range(~loc=[|94, 100|], ~title="Defining Some Database Implementations", ()),
          CodeSlide.range(~loc=[|101, 112|], ~title="Using the Interface", ()),
          CodeSlide.range(~loc=[|113, 117|], ~title="Output", ())
        |] />

      <Slide>
        <Heading>(s("Other Uses of GADTs"))</Heading>
        <Notes>
          <ul>
            <li>(s("vects"))</li>
            <li>(s("static gadts"))</li>
          </ul>
        </Notes>
      </Slide>

      <CodeSlide
        lang="reason"
        code={"\
let zip_list =
  ( x: list('a),
    y: list('b)
  ): list(('a, 'b)) =>
    ...

let zip_vect =
  ( type n,
    x: vect('a, n),
    y: vect('b, n)
  ): vect('a * 'b, Peano.add(n, n)) =>
    ...

// compiles
zip_vect([1, 2, 3], [\"a\", \"b\", \"c\"]);

// does not compile
zip_vect([1, 2], [\"a\", \"b\", \"c\"]);"}
        ranges=[|
          CodeSlide.range(~loc=[|0, 5|], ~title="Zip on Lists", ()),
          CodeSlide.range(~loc=[|6, 12|], ~title="Zip on Vects", ()),
          CodeSlide.range(~loc=[|13, 18|], ~title="Compile Time Checking", ())
        |]  />

      <CodeSlide
        lang="reason"
        code={"\
type transaction('a) =
  | GetAccount(id): transaction(account)
  | GetPost(id): transaction(post)
  | CreatePost(transaction(account), post): transaction(post);

let perform = (type a, transaction(a)): a =>
  ...

// compiles
let new_post: post = perform(CreatePost(GetAccount(0), {...}));

// does not compile
let account: account = perform(CreatePost(GetAccount(0), {...}));
let new_post: post = perform(CreatePost(GetPost(0), {...}));"}
        ranges=[|
          CodeSlide.range(~loc=[|0, 7|], ~title="Type Safe DSLs", ()),
          CodeSlide.range(~loc=[|8, 14|], ~title="Compile Time Checking", ()),
        |]  />

      <Slide>
        <Heading>(s("Questions?"))</Heading>
        <Text>(s("email: nathan@o1labs.org"))</Text>
      </Slide>
    </Deck>
  }
};
