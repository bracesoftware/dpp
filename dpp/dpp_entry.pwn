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

#pragma warning disable 204
#pragma warning disable 211
#include <a_samp>
#pragma dynamic 215750000
enum dpp_enumset{console_pkg}
#define DPP_DEBUG 1
new dpp_config[dpp_enumset];

#include "dpp_modules/dpp_header"
#include "dpp_modules/dpp_interpreter"

main()
{
	dpp_execute();
	return 1;
}