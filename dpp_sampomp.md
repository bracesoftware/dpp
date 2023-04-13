# Supported callbacks

## `OnGameModeInit`
Code:

```cpp
using::system.rem,"OnGameModeInit should be called by itself.";
decl::func.OnGameModeInit;
decl::begin;
using::console.cout,"OnGameModeInit works";
decl::end;
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

# Supported functions