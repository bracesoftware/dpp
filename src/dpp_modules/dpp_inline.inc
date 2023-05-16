/*
*
* D++ Scripting Language
*     Made for a SA:MP server
*
* Inline forms
*
* 
* - by: DEntisT, (c) 2022
*
*/

stock dpp_createinline(const name[], baseformid)
{
    for(new i; i < dpp_maxinline; i++)
    {
        if(dpp_validinline[i] == 0)
        {
            dpp_validinline[i] = 1;
            strmid(dpp_inlinename[i], name, 0, 64, 64);
            dpp_inlinebaseform[i] = baseformid;
            dpp_currentinlineid = i;
            return 1;
        }
    }
    return 1;
}

stock dpp_clearformstack(formid)
{
    for(new i; i < dpp_maxinline; i++)
    {
        if(dpp_inlinebaseform[i] == formid)
        {
            dpp_validinline[i] = 0;
            return 1;
        }
    }
    return 1;
}