/*
 *
 * D++ Scripting Language
 *     Made for a SA:MP server
 *
 * Entry point
 *
 * 
 * - by: DEntisT, (c) 2022
 *
 */

#pragma dynamic 215750000
#pragma warning disable 204
#pragma warning disable 211
#pragma option -;+
#define DPP_DEBUG 1
#define dpp_maxfuncs 1000

// REQUIRED.
#include <open.mp>

enum dpp_enumset
{
	console_pkg,
	system_pkg
};

new dpp_config[dpp_enumset];
new dpp_currentfuncid = 0;
new dpp_validfunc[dpp_maxfuncs];
new dpp_funcname[dpp_maxfuncs][64];
new dpp_funccodeblock[dpp_maxfuncs][1024];
new dpp_interpreter = 1;

//OPTIONS

new dpp_option_debug = 0;

#include "dpp_modules/dpp_header.inc"
#include "dpp_modules/dpp_interpreter.inc"

main()
{
	dpp_execute("script.dpp");
	return 1;
}