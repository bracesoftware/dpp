# Miscellaneous

## `exit`

Use this to terminate the interpreter, after it was terminated, you'll need to restart the interpreter to run the code again.

```pawn
exit;
```

## String formatting
- You can format any string argument in any form.

```pawn
var::define.str,test,"Test string";

console.println,"{test}";
```

Output:
```
Test string
```

```pawn
public&form.testfunction?message;
do;
	console.println,message@testfunction;
end;

user.testfunction,"{test}";
```

Output:
```
Test string
```