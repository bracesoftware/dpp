**NOTE**: This is an old alpha version of D++, which had a really bad codebase which was making new updates really hard to make, thus it only contained the variable system and the `print` function, also this version never had a multi-line support which means you could write code in only one line. All these cons were really frustrating so I decided to make a rewrite which - as you can see - now has many features.

# D++
:zap: ¤ D++ programming language written in Pawn.
 © & ® BRACE™

# Introduction to `D++`
- D++ is a simple and small programming language written in Pawn by DEntisT in 2021.

## Quick Start
- To start, we're going to make simple "Hello World" program in `script.dpp`.
- `script.dpp`:
```pawn
import::package.console; using::console.print,"Hello World";
```
Output:
```
[14:05:43]                                         
[14:05:43] |======================================|
[14:05:43]                                         
[14:05:43]             The D++ Language            
[14:05:43]           System is loading...          
[14:05:43]                                         
[14:05:43]                By: DEntisT              
[14:05:43]                                         
[14:05:43] |======================================|
[14:05:43]                                         
[14:05:43]                                         
[14:05:43]                                         
[14:05:43] =====================[script.dpp]=====================
[14:05:43] Hello World
[14:05:43] =====================[EOS]=====================
```
- We can also import other files.
- `include.dpp`
```pawn
using::console.Print,"include.dpp is imported";
```

- `script.dpp`
```pawn
import::file,"include";

option::debug,1;

using::console.print,"Hello World";
using::console.print,"I am really cool string";
```

- You can also enable a debug mode using `option` keyword.

Output:
```
[14:05:43]                                         
[14:05:43] |======================================|
[14:05:43]                                         
[14:05:43]             The D++ Language            
[14:05:43]           System is loading...          
[14:05:43]                                         
[14:05:43]                By: DEntisT              
[14:05:43]                                         
[14:05:43] |======================================|
[14:05:43]                                         
[14:05:43]                                         
[14:05:43]                                         
[14:05:43] =====================[script.dpp]=====================
[14:05:43] include.dpp is imported
[14:05:43] Hello World
[14:05:43] I am really cool string
[14:05:43] =====================[EOS]=====================
```

- You can also create variables and assign data to them.
```pawn
decl::var.int,MyVariable; var::set.int,MyVariable,200;
```
