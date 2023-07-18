/*
*
* D++ Scripting Language
*     Made for a SA:MP server
*
* Component impl: data
*
* 
* - by: DEntisT, (c) 2022
*
*/

forward dpp_processdata(funcgroup[][],args[][],args_const[][]);
public dpp_processdata(funcgroup[][],args[][],args_const[][])
{
    if(!strcmp(funcgroup[0], "data"))
    {
        if(dpp_config[data_comp] == 0)
        {
            dpp_error("Component \"data\" is not imported.",);
            return 1;
        }
        if(!strcmp(funcgroup[1], "sscanf"))
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

            //dpp_warning("sscanf debug 1",);

            for(new i = 2; i < 10; i++)
            {
                dpp_argclasscheck(args_const[i]);
            }

            //dpp_warning("sscanf debug 2",);

            new args_sscanf[8][dpp_maxstrsize], dpp_varid[8];
            dpp_parseline(args[1], args_sscanf, '-');

            //dpp_warning("sscanf debug 3",);

            for(new i = 2; i < 10; i++)
            {
                for(new j; j < dpp_maxvar; j++)
                {
                    if(!strcmp(args_const[i], dpp_vardata[j][var_name]))
                    {
                        if(dpp_vardata[j][var_valid] == 1)
                        {
                            dpp_varid[i] = j;
                            break;
                        }
                    }
                }
            }

            //dpp_warning("sscanf debug 4",);

            for(new i = 2; i < 10; i++)
            {
                if(isnull(args_sscanf[i-2])) continue;
                dpp_vardata[dpp_varid[i]][integervalue] = strval(args_sscanf[i-2]);
                //dpp_error("var_name: '%s' | dpp_varid[%i]: '%i' | args_sscanf[%i]: '%s'",dpp_vardata[dpp_varid[i]][var_name],i,dpp_varid[i],i-2,args_sscanf[i-2]);
                strmid(dpp_vardata[dpp_varid[i]][stringvalue],args_sscanf[i-2],0,dpp_maxstrsize,dpp_maxstrsize);
            }

            //dpp_warning("sscanf debug 5",);
            return 1;
        }

        else
        {
            dpp_error("Unknown form in the component \"data\".",);
            return 1;
        }
    }
    return 0;
}