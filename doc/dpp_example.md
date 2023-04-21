# Example

`script.dpp`:
```pawn
import::package.console;


const::define.bool,DEBUG_OPTION,false;

pragma::option.debug,DEBUG_OPTION;

import::package.system;
import::package.samp;
import::file,"test";

using::system.rem,"Basic cout example.";
using::console.cout,"Hual is a fucking bitch";

decl::func.testfunc;
{
	using::console.cout,"testfunc works.";
	using::console.cout,"testfunc works.";
}

using::user.testfunc;

using::system.rem,"=================== NATIVES ===================";

using::system.rem,"a_samp for D++";

const::define.int,MAX_PLAYERS,1000;
const::define.int,MAX_ACTORS,1000;
const::define.int,MAX_VEHICLES,2000;

using::samp.SetGameModeText,"d++ test";
using::samp.SetMaxPlayers,MAX_PLAYERS;

using::system.rem,"===================FUNCS===================";

decl::func.testFunc;
{
	using::console.cout,"testFunc was called.";
	return.str,"testFunc returned this.";
}

const::define.str,LMAO,"Lmao";

decl::func.disableDebug;
{
	using::console.cout,"Debug disabled";
	return.str,LMAO;
}

using::console.cout,testFunc;
using::console.cout,disableDebug;

using::system.rem,"===================CALLBACKS===================";

decl::func.OnGameModeInit;
{
	using::console.cout,"OnGameModeInit works";
	return.int,1;
}

decl::func.OnGameModeExit;
{
	using::console.cout,"OnGameModeExit works";
	return.bool,true;
}
```

`test.dpp`:
```pawn
using::console.cout,"Test is imported.";

using::console.cout,"interesting...";
```