# Example

`script.dpp`:
```cpp
pragma::option.debug,false;

import::package.console;
import::package.system;
import::package.samp;
import::file,"test";

using::system.rem,"Basic cout example.";
using::console.cout,"Hual is a fucking bitch";

decl::func.testfunc;
do;
	using::console.cout,"testfunc works.";
	using::console.cout,"testfunc works.";
end;

using::user.testfunc;

using::system.rem,"=================== NATIVES ===================";

using::samp.SetGameModeText,"d++ test";

using::system.rem,"===================CALLBACKS===================";

decl::func.OnGameModeInit;
do;
	using::console.cout,"OnGameModeInit works";
end;

decl::func.OnGameModeExit;
do;
	using::console.cout,"OnGameModeExit works";
end;
```

`test.dpp`:
```cpp
using::console.cout,"Test is imported.";

using::console.cout,"interesting...";
```