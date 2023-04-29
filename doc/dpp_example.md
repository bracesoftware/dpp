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

using::system.rem,"Basic println example.";
using::console.println,"Hual is a fucking bitch";

public&form.testfunc;
do;
	using::console.println,"testfunc works.";
	using::console.println,"testfunc works.";
end;

public&form.NewTestFunc;
	do;
	using::console.println,"OH YEAH MAN";
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
	using::console.println,"testFunc was called.";
	return.str,"testFunc returned this.";
end;

const::define.str,LMAO,"Lmao";

public&form.disableDebug;
do;
	using::console.println,"Debug disabled";
	return.str,LMAO;
end;

using::console.println,testFunc;
using::console.println,disableDebug;

using::system.rem,"===================CALLBACKS===================";

auto&form.OnGameModeInit;
do;
	using::console.println,"OnGameModeInit works";
	return.int,1;
end;

public&form.OnGameModeExit;
do;
	using::console.println,"OnGameModeExit works";
	return.bool,true;
end;

import::module,"vars";
```

`test.dpp`:
```pawn
using::console.println,"Test is imported.";

using::console.println,"interesting...";

const::define.str,TEST_STRING,"TEST_STRING value works!";

using::console.println,TEST_STRING;

const::define.str,OMG,"OMG";
using::console.println,OMG;

const::define.int,"saa",1;
const::define.int, a s ,1;
const::define.int,e		,1;
```

`vars.dpp`:
```pawn
var::define.str,myvar,"myvar worked.";

using::console.println,myvar;

var::set.str,myvar,"myvar worked again.";

using::console.println,myvar;

if.equ,1,1->using::console.println,"1 is 1";
if.notequ,2,1->using::console.println,"2 is not 1";
if.notequ,1,1->using::console.println,"1 is not 1";
if.equ,1,100->using::console.println,"1 is 100";

if.equ,myvar,"myvar worked."->using::console.println,myvar;
if.equ,false,true->using::console.println,"false is equal to true";
```