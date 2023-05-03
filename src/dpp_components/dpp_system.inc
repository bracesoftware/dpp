/*
*
* D++ Scripting Language
*     Made for a SA:MP server
*
* Component impl: system
*
* 
* - by: DEntisT, (c) 2022
*
*/


forward dpp_processsystem(funcgroup[][],args[][]);
public dpp_processsystem(funcgroup[][],args[][])
{
    if(!strcmp(funcgroup[0], "using::system"))
    {
        if(dpp_config[system_comp] == 0)
        {
            dpp_error("Component \"system\" is not imported.",);
            return 1;
        }
        // If the function used it "print"
        if(!strcmp(funcgroup[1], "rem"))
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

            // do nothing, this is a comment
            return 1;
        }
        if(!strcmp(funcgroup[1], "arginit"))
        {
            for(new i; i < dpp_maxfuncs; i++)
            {
                if(!strcmp(dpp_funcname[i], args[1]))
                {
                    if(dpp_hookform[i] == 0)
                    {
                        for(new argid; argid < dpp_maxformargs; argid++)
                        {
                            strmid(dpp_args[i][argid][dpp_argvalue],
                                args[argid+1+1],
                                0,
                                dpp_argcharsize,
                                dpp_argcharsize);
                        }
        
                        if(dpp_option_hooking == 1)
                        {
                            for(new hookfuncid; hookfuncid < dpp_maxfuncs; hookfuncid++)
                            {
                                if(!strcmp(dpp_funcname[hookfuncid], args[1]))
                                {
                                    if(dpp_hookform[hookfuncid] == 1)
                                    {
                                        for(new argid; argid < dpp_maxformargs; argid++)
                                        {
                                            /*strmid(dpp_args[hookfuncid][argid][dpp_argname],
                                                dpp_args[i][argid][dpp_argname],
                                                0,
                                                dpp_argcharsize,
                                                dpp_argcharsize);*/
                                            strmid(dpp_args[hookfuncid][argid][dpp_argvalue],
                                                args[argid+1+1],
                                                0,
                                                dpp_argcharsize,
                                                dpp_argcharsize);
                                        }
                                    }
                                }
                            }
                        }
                        return 1;
                    }
                }
            }
            dpp_error("Form \"%s\" is not registered.",args[1]);
        }
        else
        {
            dpp_error("Unknown form in the component \"system\".",);
            return 0;
        }
    }
    return 0;
}