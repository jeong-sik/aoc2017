let thing = (~a=1, b, c) => {
 a + b + c; 
}

Js.log(thing(3, 2))

let r = () => {
  3
}
let r' = () => {
  3
}

Js.log(r());

Js.log(r'());