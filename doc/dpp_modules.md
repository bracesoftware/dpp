# Modules
- In Pawn, you can include files. In D++, those files are called your script modules. If you want to make your `*.dpp` file a module, just make a `modules` folder in your `scriptfiles` and move it there.

Afterwards you may import your module:
```cpp
#include:module_name;
```

Make sure not to add the `*.dpp` extension to the `module_name`.