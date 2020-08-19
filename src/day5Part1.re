module Exit {
  type t = {
    input: array(int),
    mutable count: int,
    mutable position: int
  }
  /*
    mutable 을 빼고 처리할 수 없을까? 
    https://reasonml.github.io/docs/en/record#updating-records-spreading
    이것을 참고?
  */

  let initialize = (array, ~count, ~position) => {
    { input: array, count, position }
  }
  
  let isExit = ({input, position}) => Js.Array2.length(input) <= position || position < 0 

  let next = (value, t) => {
    switch (value) {
      | 0 => Js.Array2.unsafe_set(t.input, t.position, value + 1)
      | _ => {
        Js.Array2.unsafe_set(t.input, t.position, value + 1)
        t.position = t.position + value
        }
      }
  }

  // enhancer를 어떻게 해볼까 
  let rec play = (t, ~enhancer=?, ()) => {
    switch (isExit(t)) {
      | true => t
      | false => {
        t.count = t.count + 1
        switch (enhancer) {
          | _ => {
            Js.Array2.unsafe_get(t.input, t.position)
            ->next(t)
          }
        }
        play(t, ())
      }
    }
  }
}

let input = Node.Fs.readFileAsUtf8Sync("day5Part1.input")
  ->Js.String2.split("\n")
  ->Js.Array2.map(Pervasives.int_of_string)


// Only Part 1
Exit.initialize(input, ~count=0, ~position=0)->Exit.play(())->Js.log
