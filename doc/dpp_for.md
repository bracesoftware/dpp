# For-loops

- In computer science a for-loop or for loop is a control flow statement for specifying iteration. Specifically, a for loop functions by running a section of code repeatedly until a certain condition has been satisfied.

## Example

```pawn
var::define.int,forlooptestvar,0;
if.equ,1,1->for.int&var,forlooptestvar,10->using::console.println,"For loop id {forlooptestvar}";
```

Output:

```
For loop id 1
For loop id 2
For loop id 3
For loop id 4
For loop id 5
For loop id 6
For loop id 7
For loop id 8
For loop id 9
For loop id 10
```