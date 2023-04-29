# Constants
- In computer programming, a constant is a value that should not be altered by the program during normal execution, i.e., the value is constant.

- You also may make constants in D++:

```pawn
const::define.int,MY_FIRST_CONST,1;
```

This is an integer constant, to undefine it:

```pawn
const::undef.int,MY_FIRST_CONST;
```

You also may create boolean and string constants:

```pawn
const::define.bool,MY_FIRST_CONST,true;
const::define.str,MY_FIRST_CONST,"string";

const::undef.bool,MY_FIRST_CONST,1;
const::undef.str,MY_FIRST_CONST,1;
```