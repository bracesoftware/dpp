# Function calling and returns

Code:
```pawn
decl::func.testFunc;
{
	using::console.cout,"testFunc was called.";
	return.str,"testFunc returned this.";
}

using::console.cout,testFunc;
```
Output:
```
...
[19:06:57] [Info] testFunc was called.
[19:06:57] [Info] testFunc returned this.
[19:06:57] [Info]                                                
[19:06:57] [Info] |==============================================|
[19:06:57] [Info]                                                
[19:06:57] [Info] >> D++ | INFO: The interpreter reached the EOS point.
```

You can also return booleans and strings!

```pawn
decl::func.testFunc;
{
	return.int,1;
}

decl::func.testFunc;
{
	return.bool,true;
}
```