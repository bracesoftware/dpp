/*
 *
 * D++ Scripting Language
 *     Made for a SA:MP server
 *
 * Utils
 *
 * 
 * - by: DEntisT, (c) 2022
 *
*/

#define dpp_isinrange(%0,%1,%2) (((%0)-((%1)+cellmin))<((%2)-((%1)+cellmin))) 
// creds Y_Less

stock bool:dpp_isnumeric(const str[]) // creds Y_Less
{
    new
        i = -1;
    if (ispacked(str))
    {
        if (str{0} == '-') ++i;
        while (dpp_isinrange(str{++i}, '0', '9' + 1)) {}
        return !str{i};
    }
    else
    {
        if (str[0] == '-') ++i;
        while (dpp_isinrange(str[++i], '0', '9' + 1)) {}
        return !str[i];
    }
}