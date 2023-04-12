# Example

`script.dpp`:
```cpp
import::package.console;
import::package.system;
import::file,"test";

using::system.rem,"Basic cout example.";
using::console.cout,"Hual is a fucking bitch";

decl::func.testfunc;
decl::begin;
using::console.cout,"testfunc works.";
decl::end;

using::user.testfunc;
```

`test.dpp`:
```cpp
using::console.cout,"Test is imported.";

using::console.cout,"interesting...";
```