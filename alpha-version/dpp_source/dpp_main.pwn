/*
* D++ Language
*
* (c) Copyright - 2022, DEntisT
*
* Interpreter driver.
*
*/

#pragma dynamic 215750000
#pragma option -;+
#define dpp_configfile "dpp_settings.cfg"
#include <a_samp>
enum dpp_cfg{
filetoconfig[32],
execdebug,
console_pkg,
user_pkg,
import_backtrace}
new dpp_config[dpp_cfg];

#define dpp_version "1.0"
// Core:
#include "dpp_interpreter\dpp_core.inc"

stock main()
{
	dpp_init();
	dpp_execute("script.dpp");
	printf("Value of MyVariable: %i", get Integer("MyVariable"));
	printf("Data of MyFunction: %s", g_FunctionCache[0][data]);
}