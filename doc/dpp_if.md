# If-expressions
- The if-expression allows you to make a logical comparison between a value and what you expect by testing for a condition and returning a result if that condition is true or false.

- If-expressions are also possible in D++:

```pawn
if.equ,1,1->using::console.println,"1 is 1";
```

You also may compare variables, consants and vice-versa.

```pawn
var::define.str,myvar,"myvar worked.";

if.equ,myvar,"myvar worked."->using::console.println,myvar;
```

## If-methods

If-method is a new term used to describe the way how are you comparing the 2 elements, there are few if-methods:

- `equ` - check if 2 elements are equal.
- `notequ` - check if 2 elements are not equal.