open Belt;
let regex = [%re "/[a-z|() | ]+/g"];

module Program = {
  type t = {
    name: string,
    number: string,
    subPrograms: Set.String.t,
  };
  let make = (t: array(string)) => {
    let head = Array.getUnsafe(t, 0);
    let name = Array.getUnsafe(Js.String2.split(head, " "), 0);
    let number = Js.String2.replaceByRe(head, regex, "");
    switch (t[1]) {
    | Some(v) => {
        name,
        number,
        subPrograms: Set.String.fromArray(Js.String2.split(v, ", ")),
      }
    | None => {name, number, subPrograms: Set.String.empty}
    };
  };

  // 팀원분의 도움을 받았다!
  // currentProgram 
  // Set.String.has 의 존재 확인
  let rec findBottom = (currentProgram, programs) => {
    let parentProgram =
      programs->List.getBy(b => {
        Set.String.has(b.subPrograms, currentProgram.name)
      });

    // Todo 다시 list 로 만들어 넣기 for rec
    switch (parentProgram) {
    | None => currentProgram.name
    | Some(v) => findBottom(v, programs)
    };
  };
};


let input =
  Node.Fs.readFileAsUtf8Sync("./day7.input")
  ->Js.String2.split("\n")
  ->Array.map(Js.String.split(" -> "))
  ->Array.map(Program.make)
  ->List.fromArray
  ->List.keep(p => Set.String.size(p.subPrograms) > 0);

  // Array.map 순회를 더 줄일 방법은 없을까

  // Only Part1
Js.log(Program.findBottom(input->List.getExn(0), input));
