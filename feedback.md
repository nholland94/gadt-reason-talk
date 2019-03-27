= graphql slides
= extra gadt examples

* mention reason syntax on opening slide
- why even care about GADTs
* goal: I don't expect to give you a complete understanding, but I hope to motivate you
* problem prompt: strongly statically typed without gadts create leaky abstractions
* ~ base64 strings in a list (before sending to api)
  % could be records

* variants == ADTs
* gadt slide: "if you see this colon, that's a gadt"
  * don't try to understand this
  * simplify the example
- ? graphql example w/ + w/o gadt interface
% start with a list, then introduce heterogeneous list
* show goal comparison for hlist twice (once at beginning, again right before adt impl)
- explain map\_equal\_witness

* show goal before dynamic dispatch
  * compare against manual first class module
- dynamic dispatch gloss over details
  - remind people that this is only what the library maintainer deals with
- show dynamic dispatch interface at end
- little vect example
- perf + safety improvements

- lift up the gadt description
- motivate partial\_map
