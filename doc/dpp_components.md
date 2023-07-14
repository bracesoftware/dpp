# Interpreter components
- Functions in D++ are called **forms**; to use certain *native forms*, you need to import standard built-in components into your code. For example - to use `cout`, you need to have a `console` interpreter component imported. Below, you can find the full list of available components.

## Contents
- [`console`](#component-console)
- [`system`](#component-system)
- [`samp`](#component-samp)
- [`files`](#component-files)
- [`misc`](#component-misc)

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

### Form: `SendClientMessage`

- Send a message to a player.

```pawn
using::samp.SendClientMessage,playerid@OnPlayerConnect,0,"Welcome to the D++ server";
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

### Automated user form: `OnPlayerConnect`

- Called when a certain player connects to the server.

```pawn
auto&form.OnPlayerConnect?playerid;
do;
	using::samp.SendClientMessage,playerid@OnPlayerConnect,0,"Welcome to the D++ server";
end;
```

### Automated user form: `OnPlayerDisconnect`

- Called when a certain player disconnects from the server.

```pawn

auto&form.OnPlayerDisconnect?playerid&reason;
do;
	using::console.println,"Player {playerid@OnPlayerDisconnect} disconnected | Reason: {reason@OnPlayerDisconnect}";
	return.int,1;
end;
```

**WARNING**: For some unknown reason, Windows can crash when the form is called with reason `1`.


---------------------------------------------------------------------------------------------------------


## Component: `files`
- Provides file-related forms.

Import the component using:
```pawn
import::component.files;
```

### Form: `open_for_write`
- Opens a file with an intention to write data into it. File is created if it does not exist.

```pawn
using::files.open_for_write,"file_name.txt";
```

### Form: `open_for_read`
- Opens a file with an intention to read data from it. File is created if it does not exist.

```pawn
using::files.open_for_read,"file_name.txt";
```

### Form: `open_for_append`
- Opens a file with an intention to append data into it. File is created if it does not exist.

```pawn
using::files.open_for_append,"file_name.txt";
```

### Form: `read`
- Reads data from the opened file and stores it into a variable.

```pawn
var::define.str,dest_string,"something that should change";
using::files.read,dest_string;
```

### Form: `write`
- Writes data into the opened file.

```pawn
using::files.write,"wrote this into file_name.txt";
```

### Form: `close`
- Closes the opened file.

```pawn
using::files.close;
```

### Form: `delete`

- Deletes a certain file.

```pawn
using::files.delete,"newfile.omg";
```

---------------------------------------------------------------------------------------------------------


## Component: `misc`
- Provides miscellaneous forms.

Import the component using:
```pawn
import::component.misc;
```

### Form: `swap`
- Swaps two's variable values.

```pawn
using::misc.swap,var1,var2;
```

**NOTE**: Now variable `var1` will have the value `var2` had, and `var2` will have the value `var1` had.