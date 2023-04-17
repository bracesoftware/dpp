<p align="center">
  <img width="200" align="center" src="dpp_logo.png">
</p>
<h1 align = "center">Welcome to the <b>D++</b> Wiki</h1>
<h3 align = "center">
  The Simplest Multi-purpose Programming Language
</h3>

## Introduction
:zap: ¤ D++ is a simple scripting language written in Pawn. It is made purely for fun and with an intention to learn more about Pawn itself, thus D++ should not be taken as a serious language. However, the language itself is still impressive considering it is written in Pawn.

- For the impatient, here is the example code:
```pawn
import::package.console;
import::package.system;

using::system.rem,"Basic cout example.";
using::console.cout,"Hello World";
```

- Code output:

```
[12:44:50] >> D++ | INFO: Interpreter version 0.0.1-R1 - by: DEntisT
[12:44:50] >> D++ | INFO: Executing the entry script...
[12:44:50]                                                
[12:44:50] |====================| script.dpp |====================|
[12:44:50]                                                
[12:44:50] Hello World
[12:44:50]                                                
[12:44:50] |==============================================|
[12:44:50]                                                
[12:44:50] >> D++ | INFO: The interpreter reached the EOS point.
```
## Documentation

### The language

- Options you can modify using `pragma::option` - [read here](doc/dpp_options.md).
- Importable packages and functions - [read here](doc/dpp_packages.md).
- Variables and constants - [see here](doc/dpp_const.md).
- Function calling and value returning - [see here](doc/dpp_returns.md).

### Other info

- Examples - [see here](doc/dpp_example.md).
- SA:MP and open.mp scripting - [see here](doc/dpp_sampomp.md).


### Worried about the latest updates?

Just regularly check the [workflow runs](https://github.com/samp-api/dpp/actions)! Always select the latest **successful** workflow to download the latest build artifacts from.