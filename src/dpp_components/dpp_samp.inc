/*
*
* D++ Scripting Language
*     Made for a SA:MP server
*
* Component impl: samp
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
                dpp_debug("dpp_funccodeblock[i]:%s",dpp_funccodeblock[i]);
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
                                dpp_debug("dpp_funccodeblock[hookfuncid]:%s",dpp_funccodeblock[hookfuncid]);
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
            dpp_debug("dpp_funccodeblock[i]:%s",dpp_funccodeblock[i]);
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
                                dpp_debug("dpp_funccodeblock[hookfuncid]:%s",dpp_funccodeblock[hookfuncid]);
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

forward dpp_processsamp(funcgroup[][],args[][]);
public dpp_processsamp(funcgroup[][],args[][])
{
    if(!strcmp(funcgroup[0], "using::samp"))
    {
        if(dpp_config[samp_comp] == 0)
        {
            dpp_error("Component \"samp\" is not imported.",);
            return 1;
        }
        if(!strcmp(funcgroup[1], "SetGameModeText"))
        {
            new mul, str[dpp_argcharsize];
            strmid(str, args[1], 0, dpp_argcharsize);
            for(new i; i < strlen(args[1]); i++)
            {
                if(args[1][i] == '\"') mul++, strdel(args[1], i, i+1);
            }
            if(mul == 0)
            {
                dpp_error("You need to use '\"' to start a string.",);
                return 1;
            }
            if(mul != 2)
            {
                dpp_error("Argument error; [%i] \"%s\"", mul, args[1]);
                return 1;
            }

            SetGameModeText(args[1]);
            return 1;
        }

        if(!strcmp(funcgroup[1], "SetMaxPlayers"))
        {
            if(!dpp_isnumeric(args[1]))
            {
                dpp_error("Argument error; value must be an integer.",);
                return 1;
            }

            SetMaxPlayers(strval(args[1]));
            return 1;
        }

        else
        {
            dpp_error("Unknown form in the component \"samp\".",);
            return 1;
        }
    }
    return 0;
}