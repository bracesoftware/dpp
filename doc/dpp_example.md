# Example

`index.dpp`:
```pawn
import::package.console;


const::define.bool,DEBUG_OPTION,false;

pragma::option.debug,DEBUG_OPTION;

import::package.system;
import::package.samp;
import::file,"test";

using::system.rem,"Basic cout example.";
using::console.cout,"Hual is a fucking bitch";

public&func.testfunc;
do;
	using::console.cout,"testfunc works.";
	using::console.cout,"testfunc works.";
end;

public&func.NewTestFunc;
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

public&func.testFunc;
do;
	using::console.cout,"testFunc was called.";
	return.str,"testFunc returned this.";
end;

const::define.str,LMAO,"Lmao";

public&func.disableDebug;
do;
	using::console.cout,"Debug disabled";
	return.str,LMAO;
end;

using::console.cout,testFunc;
using::console.cout,disableDebug;

using::system.rem,"===================CALLBACKS===================";

public&func.OnGameModeInit;
do;
	using::console.cout,"OnGameModeInit works";
	return.int,1;
end;

public&func.OnGameModeExit;
do;
	using::console.cout,"OnGameModeExit works";
	return.bool,true;
end;

import::file,"vars";
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
```