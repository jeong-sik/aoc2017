open Belt
let regex = [%re "/[a-z|() ]+/g"]

module Program {
  type t = {
    name: string,
    number: string,    
    subPrograms: array(string)
  }
  let make = (t: array(string)) => {
    let head = Array.getUnsafe(t, 0)
    let name = Array.getUnsafe(Js.String2.split(head, " "), 0)
    let number = Js.String2.replaceByRe(head, regex, "")
    switch (Array.get(t, 1)) {
      | Some(v) => {
        {
          name,
          number,
          subPrograms: Js.String2.split(v, ",")}
      }
      | None => { name, number, subPrograms: [||]}
    }
  }
  let findBottom = (t) => {
    // WIP
    switch(List.getBy(t, (p => p.name == "ugml"))) { 
      | Some(v) => v.name
      | None => ""
    }
    
  }
}

let input =
   Node.Fs.readFileAsUtf8Sync("./day7-test.input")
   ->Js.String2.split("\n")
   ->Array.map(Js.String.split(" -> "))
   ->Array.map(Program.make)
   ->List.fromArray
  //  ->ArrayLabels.to_list
  //  ->List.map(l => l)->List.toArray
  //  ->ArrayLabels.map(~f=Program.make)
  
   
// let l = [""]
// let af = List.get(l, 1)
// let b = List.toArray(List.map(l, bb => bb));


Js.log(Program.findBottom(input))