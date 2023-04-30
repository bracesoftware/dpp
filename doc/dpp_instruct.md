# Instructions
- In D++, instructions are small form-like arguments which have a simple task to do. For example, mathematical expressions such as division, multiplication and so on. Components can also contain them predefined.

---------------------------------------------------------------------------------------------------------

## Component: `math`
You'll need to import the `math` component to use math instructions.

### Instruction: `add`
- Addition.
```pawn
using::console.cout,add?1:1;
```

### Instruction: `sub`
- Subtraction.
```pawn
using::console.cout,sub?1:1;
```

### Instruction: `mul`
- Multiplication.
```pawn
using::console.cout,mul?1:1;
```

### Instruction: `div`
- Division.
```pawn
using::console.cout,div?1:1;
```

### Instruction: `exp`
- Exponentiation.
```pawn
using::console.cout,exp?1:1;
```

---------------------------------------------------------------------------------------------------------

Little example:

```pawn
if.equ,div?5:5,add?1:0->using::console.println,"Math test passed!";
```

You may also use constants, variables and user forms as an instruction arguments:

```pawn
var::define.int,MATHVAR,add?1:1;
using::console.cout,MATHVAR;

var::define.int,MATHVAR22,add?6:MATHVAR;
using::console.cout,MATHVAR22;
```