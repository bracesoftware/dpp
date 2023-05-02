# Interpreter components
- Functions in D++ are called **forms**; to use certain *native forms*, you need to import standard built-in components into your code. For example - to use `cout`, you need to have a `console` interpreter component imported. Below, you can find the full list of available components.

---------------------------------------------------------------------------------------------------------

## Component: `console`
- Provides console-related forms.

Import the component using:
```pawn
import::component.console;
```

### Form: `cout`
- Character output.

```pawn
using::console.cout,1;
```

### Form: `println`
- Text line output.

```pawn
using::console.cout,"Hello World!";
```

---------------------------------------------------------------------------------------------------------

## Component: `system`
- Provides random, usually internal, forms.

Import the component using:
```pawn
import::component.system;
```

### Form: `rem`
- Comments.
```pawn
using::system.rem,"SOME TEXT";
```

### Form: `arginit`
- Used to initialize the arguments.

```pawn
public&form.arginit_test?playerid&string;
do;
	return.int,1;
end;

using::system.arginit,arginit_test,1,"Hello!";
```

---------------------------------------------------------------------------------------------------------

### Automated user form: `main`

- Called when the code gets executed.

```pawn
auto&form.main;
do;
	using::console.println,"Hello World from main";
	return.int,1;
end;
```


---------------------------------------------------------------------------------------------------------

## Component: `samp`
- Provides a set of forms used to interact with the SAMP or open.mp server.

Import the component using:
```pawn
import::component.samp;
```

### Form: `SetGameModeText`

- Set the gamemode text.

```pawn
using::samp.SetGameModeText,"d++ test";
```

---------------------------------------------------------------------------------------------------------

### Automated user form: `OnGameModeInit`

- In SA:MP and open.mp these are also known as **callbacks**. In D++ they're automated user forms, and are called by the D++ interpreter when a certain event happens in SA:MP. So for example, when the gamemode starts loading, automated form will get called.

```pawn
using::system.rem,"OnGameModeInit should be called by itself.";

auto&form.OnGameModeInit;
do;
	using::console.println,"OnGameModeInit works";
end;
```

### Automated user form: `OnGameModeExit`

- Called when the gamemode unloads.

```pawn
auto&form.OnGameModeExit;
do;
	using::console.println,"OnGameModeExit works";
end;
```

---------------------------------------------------------------------------------------------------------