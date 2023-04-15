# Supported callbacks

## `OnGameModeInit`

Code:

```pawn
using::system.rem,"OnGameModeInit should be called by itself.";

decl::func.OnGameModeInit;
do;
	using::console.cout,"OnGameModeInit works";
end;
```

Output:
```
[08:47:02] [Info] |==============================================|
[08:47:02] [Info]                                                
[08:47:02] [Info] >> D++ | INFO: The interpreter reached the EOS point.
[08:47:02] [Info]                                                
[08:47:02] [Info]                                                
[08:47:02] [Info] |==============================================|
[08:47:02] [Info] >> D++ | INFO: The SAMP script will continue running in the background.
[08:47:02] [Info] |==============================================|
[08:47:02] [Info]                                                
[08:47:02] [Info]                                                
[08:47:02] [Info] OnGameModeInit works
[08:47:02] [Info] Legacy Network started on port 7777
```

## `OnGameModeExit`

Code:

```pawn
decl::func.OnGameModeExit;
do;
	using::console.cout,"OnGameModeExit works";
end;
```

Output:
```
[08:47:02] [Info] |==============================================|
[08:47:02] [Info]                                                
[08:47:02] [Info] >> D++ | INFO: The interpreter reached the EOS point.
[08:47:02] [Info]                                                
[08:47:02] [Info]                                                
[08:47:02] [Info] |==============================================|
[08:47:02] [Info] >> D++ | INFO: The SAMP script will continue running in the background.
[08:47:02] [Info] |==============================================|
[08:47:02] [Info]                                                
[08:47:02] [Info]                                                
[08:47:02] [Info] Legacy Network started on port 7777
[08:47:02] [Info] OnGameModeExit works
```

# Supported functions

Note that before using these functions you must import the `samp` package first:
```pawn
import::package.samp;
```

## `SetGameModeText`

Code:

```pawn
using::samp.SetGameModeText,"d++ test";
```

Output:

```
Gamemode text will be updated to "d++ test".
```