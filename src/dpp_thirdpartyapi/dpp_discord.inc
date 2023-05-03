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
        if(!strcmp(funcgroup[1], "TEST"))
        {
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