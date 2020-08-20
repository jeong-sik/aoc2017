open Belt

let check = line => {
  let orignLength = Array.length(line);
  let s0 = Set.String.fromArray(line)
  let arr = s0->Set.String.toArray
  orignLength == Array.length(arr)
}

let input = Node.Fs.readFileAsUtf8Sync("day4.input")
  ->Js.String2.split("\n")
  ->Array.map(line => Js.String2.split(line, " ")->check)
  ->Array.keep(v => v)
  ->Array.length

// part1
Js.log(input)

// part2
// to be continue...
