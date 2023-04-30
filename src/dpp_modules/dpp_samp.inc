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
    if(dpp_config[samp_comp] == 0)
    {
        return 1;
    }

    for(new i; i < dpp_maxfuncs; i++)
    {
        if(!strcmp(dpp_funcname[i], "OnGameModeInit"))
        {
            if(dpp_autoform[i] == 0) return 1;
            if(dpp_hookform[i] == 0)
            {
                dpp_processfunc = i;
                dpp_subexecute(dpp_funccodeblock[i],i);
                dpp_debug("dpp_funccodeblock[i]:%s",dpp_funccodeblock[999]);
                dpp_debug("\"OnGameModeInit\" called.");

                if(dpp_option_hooking == 1)
                {
                    for(new hookfuncid; hookfuncid < dpp_maxfuncs; hookfuncid++)
                    {
                        if(!strcmp(dpp_funcname[hookfuncid], "OnGameModeInit"))
                        {
                            if(dpp_hookform[hookfuncid] == 1)
                            {
                                dpp_returned[hookfuncid] = 0;
                                dpp_processfunc = hookfuncid;
                                dpp_subexecute(dpp_funccodeblock[hookfuncid],hookfuncid);
                                dpp_debug("dpp_funccodeblock[hookfuncid]:%s",dpp_funccodeblock[999]);
                            }
                        }
                    }
                }
            }
            return 1;
        }
    }

    return 1;
}

public OnGameModeExit()
{
    if(dpp_config[samp_comp] == 0)
    {
        return 1;
    }

    for(new i; i < dpp_maxfuncs; i++)
    {
        if(!strcmp(dpp_funcname[i], "OnGameModeExit"))
        {
            if(dpp_autoform[i] == 0) return 1;
            dpp_processfunc = i;
            dpp_subexecute(dpp_funccodeblock[i],i);
            dpp_debug("dpp_funccodeblock[i]:%s",dpp_funccodeblock[999]);
            dpp_debug("\"OnGameModeInit\" called.");
            if(dpp_hookform[i] == 0)
            {
                if(dpp_option_hooking == 1)
                {
                    for(new hookfuncid; hookfuncid < dpp_maxfuncs; hookfuncid++)
                    {
                        if(!strcmp(dpp_funcname[hookfuncid], "OnGameModeExit"))
                        {
                            if(dpp_hookform[hookfuncid] == 1)
                            {
                                dpp_returned[hookfuncid] = 0;
                                dpp_processfunc = hookfuncid;
                                dpp_subexecute(dpp_funccodeblock[hookfuncid],hookfuncid);
                                dpp_debug("dpp_funccodeblock[hookfuncid]:%s",dpp_funccodeblock[999]);
                            }
                        }
                    }
                }
            }
            return 1;
        }
    }

    return 1;
}

///////////// FUNCS

stock SetMaxPlayers(maxplayers)
{
    new rconcmd[50];
    format(rconcmd, 50, "maxplayers %i", maxplayers);
    return SendRconCommand(rconcmd);
}