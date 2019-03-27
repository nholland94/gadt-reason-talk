// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var Pervasives = require("bs-platform/lib/js/pervasives.js");

function print(witness, value) {
  var str;
  switch (witness) {
    case 0 : 
        str = String(value);
        break;
    case 1 : 
        str = Pervasives.string_of_float(value);
        break;
    case 2 : 
        str = "\"" + (value + "\"");
        break;
    
  }
  console.log(str);
  return /* () */0;
}

exports.print = print;
/* No side effect */