# Example

`index.dpp`:
```pawn
import::component.console;

pragma::option.warnings,default;

const::define.bool,DEBUG_OPTION,false;

pragma::option.debug,DEBUG_OPTION;

import::component.system;
import::component.samp;
import::module,"test";

using::system.rem,"Basic cout example.";
using::console.cout,"Hual is a fucking bitch";

public&form.testfunc;
do;
	using::console.cout,"testfunc works.";
	using::console.cout,"testfunc works.";
end;

public&form.NewTestFunc;
	do;
	using::console.cout,"OH YEAH MAN";
end;

using::user.testfunc;
using::user.NewTestFunc;

using::system.rem,"=================== NATIVES ===================";

using::system.rem,"a_samp for D++";

const::define.int,MAX_PLAYERS,1000;
const::define.int,MAX_ACTORS,1000;
const::define.int,MAX_VEHICLES,2000;

using::samp.SetGameModeText,"d++ test";
using::samp.SetMaxPlayers,MAX_PLAYERS;

using::system.rem,"===================FUNCS===================";

public&form.testFunc;
do;
	using::console.cout,"testFunc was called.";
	return.str,"testFunc returned this.";
end;

const::define.str,LMAO,"Lmao";

public&form.disableDebug;
do;
	using::console.cout,"Debug disabled";
	return.str,LMAO;
end;

using::console.cout,testFunc;
using::console.cout,disableDebug;

using::system.rem,"===================CALLBACKS===================";

auto&form.OnGameModeInit;
do;
	using::console.cout,"OnGameModeInit works";
	return.int,1;
end;

public&form.OnGameModeExit;
do;
	using::console.cout,"OnGameModeExit works";
	return.bool,true;
end;

import::module,"vars";
```

`test.dpp`:
```pawn
using::console.cout,"Test is imported.";

using::console.cout,"interesting...";

const::define.str,TEST_STRING,"TEST_STRING value works!";

using::console.cout,TEST_STRING;

const::define.str,OMG,"OMG";
using::console.cout,OMG;

const::define.int,"saa",1;
const::define.int, a s ,1;
const::define.int,e		,1;
```

`vars.dpp`:
```pawn
var::define.str,myvar,"myvar worked.";

using::console.cout,myvar;

var::set.str,myvar,"myvar worked again.";

using::console.cout,myvar;

if.equ,1,1->using::console.cout,"1 is 1";
if.notequ,2,1->using::console.cout,"2 is not 1";
if.notequ,1,1->using::console.cout,"1 is not 1";
if.equ,1,100->using::console.cout,"1 is 100";

if.equ,myvar,"myvar worked."->using::console.cout,myvar;
if.equ,false,true->using::console.cout,"false is equal to true";
```