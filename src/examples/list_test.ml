type ('a, 'n) vect =
  | []: ('a, unit) vect
  | (::): 'a * ('a, 'n) vect -> ('a, unit -> 'n) vect

type 'a list =
  | [] of unit
  | (::) of 'a * 'a list
