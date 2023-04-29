# Variables
- Unlike constants, variables can change their value at any time.

- Like constants, variables may be integers, booleans and strings.

```pawn
var::define.str,myvar,"myvar worked.";
```

To change its value, use:

```pawn
var::set.str,myvar,"myvar worked again.";
```

To undefine it, use:

```pawn
var::undef.str,myvar;
```