# Constants

You can create constants and use them in your code. Constants can be integers, booleans and strings!

## Integers

```pawn
const::define.int,TEST_INT,1;

```


## Booleans

```pawn
const::define.bool,DEBUG_OPTION,false;

pragma::option.debug,DEBUG_OPTION;
```

## Strings

```pawn
const::define.str,TEST_STRING,"TEST_STRING value works!";

using::console.cout,TEST_STRING;
```