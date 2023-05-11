# `return`

- In D++, to return a value it means to execute the code and give the result output, after returning a value, code block execution will stop.

```pawn
public&form.MyForm;
do;
	using::console.println,"Hello World";
	return.int,1;
	using::console.println, "This code won't be executed";
end;

using::console.cout,MyForm;
using::system.rem,"Thing above will print 1";
```


# `yield&return`

- `yield` return will do the same thing as a normal return, the difference is that the code block won't stop being executed until `end;` or `return..,..;`.

```pawn
public&form.MyForm;
do;
	using::console.println,"Hello World";
	yield&return.int,1;
	using::console.println, "This code will be executed too";
end;

using::console.cout,MyForm;
using::system.rem,"Thing above will print 1";
```