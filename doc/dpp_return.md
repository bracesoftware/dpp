# Value returning

- A return statement causes execution to leave the current function and resume at the point in the code immediately after where the function was called. Return statements in many languages allow a function to specify a return value to be passed back to the code that called the function.

### `return`

- In D++, to return a value it means to execute the code and give the result output, after returning a value, code block execution will stop.

```pawn
public&form.MyForm;
{;
	console.println,"Hello World";
	return.int,1;
	console.println, "This code won't be executed";
};

console.cout,MyForm;
system.rem,"Thing above will print 1";
```


### `yield&return`

- `yield` return will do the same thing as a normal return, the difference is that the code block won't stop being executed until `};` or `return..,..;`.

```pawn
public&form.MyForm;
{;
	console.println,"Hello World";
	yield&return.int,1;
	console.println, "This code will be executed too";
};

console.cout,MyForm;
system.rem,"Thing above will print 1";
```