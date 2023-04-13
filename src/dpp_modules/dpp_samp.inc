/*
 *
 * D++ Scripting Language
 *     Made for a SA:MP server
 *
 * Support for San Andreas Multiplayer
 *
 * 
 * - by: DEntisT, (c) 2022
 *
 */

DPP_GAMEMODEINIT();
public DPP_GAMEMODEINIT()
{
	for(new i; i < dpp_maxfuncs; i++)
	{
		if(!strcmp(dpp_funcname[i], "OnGameModeInit"))
		{
			dpp_subexecute(dpp_funccodeblock[i]);
			dpp_debug("dpp_funccodeblock[i]:%s",dpp_funccodeblock[999]);
			dpp_debug("\"OnGameModeInit\" called.");
			return 1;
		}
	}

	return 1;
}