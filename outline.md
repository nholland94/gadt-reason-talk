- quotes from https://andreas.github.io/2017/11/29/type-safe-graphql-with-ocaml-part-1/
- https://github.com/reasonml-community/bs-socket.io/tree/gadt/example

- type witness
  - adt version w/ simple function
  - gadt version w/ same simple function
  // - no real advantage yet, but let's explore a new problem: type witness + parameterized type (Map.t)
  // - adt version
  //   - requires translation between types and redefinition
  // - gadt version
  //   - neat and composable
  - no real advantage yet, so why do this?
  - example: dynamic heterogeneous lists
  - adt version can be achieved, but you can't easily define a type specific map or filter
  - gadt version can achieve both
  - there are static heterogeneous lists as well, but they are complex, so we will elide them for now
- dynamic dispatch over key value databases
