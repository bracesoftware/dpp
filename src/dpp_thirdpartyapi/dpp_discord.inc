/*
*
* D++ Scripting Language
*     Made for a SA:MP server
*
* Api impl: discord
*
* 
* - by: DEntisT, (c) 2022
*
*/


DPP_discord_init();
public DPP_discord_init()
{
    if(dpp_apis[discord] == 0)
    {
        return 1;
    }

    for(new i; i < dpp_maxfuncs; i++)
    {
        if(!strcmp(dpp_funcname[i], "discord_init"))
        {
            if(dpp_autoform[i] == 0) return 1;
            if(dpp_hookform[i] == 0)
            {
                dpp_processfunc = i;
                dpp_subexecute(dpp_funccodeblock[i],i);
                dpp_debug("dpp_funccodeblock[i]:%s",dpp_funccodeblock[i]);

                if(dpp_option_hooking == 1)
                {
                    for(new hookfuncid; hookfuncid < dpp_maxfuncs; hookfuncid++)
                    {
                        if(!strcmp(dpp_funcname[hookfuncid], "discord_init"))
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

forward dpp_processdiscord(funcgroup[][],args[][]);
public dpp_processdiscord(funcgroup[][],args[][])
{
    if(!strcmp(funcgroup[0], "using::discord"))
    {
        if(dpp_apis[discord] == 0)
        {
            dpp_error("API \"discord\" is not imported.",);
            return 1;
        }
        if(dpp_isnativereg(funcgroup[1]) == 0)
        {
            dpp_error("Native API form \"%s\" not registered.",funcgroup[1]);
            return 1;
        }
        if(!strcmp(funcgroup[1], "discord_bot_send_message"))
        {
            if(!dpp_isnumeric(args[1]))
            {
                dpp_error("Argument error; [argid - 1] \"%s\"", args[1]);
                return 1;
            }

            new mul, str[dpp_argcharsize];
            strmid(str, args[2], 0, dpp_argcharsize);
            for(new i; i < strlen(args[2]); i++)
            {
                if(args[2][i] == '\"') mul++, strdel(args[2], i, i+1);
            }
            if(mul == 0)
            {
                dpp_error("You need to use '\"' to start a string.",);
                return 1;
            }
            if(mul != 2)
            {
                dpp_error("Argument error; [%i] \"%s\"", mul, args[2]);
                return 1;
            }

            new DCC_Channel:channel = DCC_FindChannelById(args[1]);

            if(channel == DCC_INVALID_CHANNEL)
            {
                dpp_apierror("discord","Unknown channel.",);
                return 1;
            }

            //native DCC_SendChannelMessage(DCC_Channel:channel, const message[], const callback[] = "", const format[] = "", {Float, _}:...);
            DCC_SendChannelMessage(channel,args[2]);
            return 1;
        }

        else
        {
            dpp_error("Unknown form in the API \"discord\".",);
            return 1;
        }
    }
    return 0;
}