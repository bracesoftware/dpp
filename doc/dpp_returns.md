# Function calling and returns

Code:
```pawn
public&func.testFunc;
do;
	using::console.cout,"testFunc was called.";
	return.str,"testFunc returned this.";
end;

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
public&func.testFunc;
do;
	return.int,1;
end;

public&func.testFunc;
do;
	return.bool,true;
end;
```