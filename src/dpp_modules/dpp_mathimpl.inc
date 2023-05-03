/*
*
* D++ Scripting Language
*     Made for a SA:MP server
*
* Support for matematical operations
*
* 
* - by: DEntisT, (c) 2022
*
*/

stock dpp_argmathcheck(arg[])
{
    // using::console.cout,add?1:1
    new newvalue[dpp_argcharsize];
    new funcgroup[2][100], operands[2][50];
    dpp_parseline(arg, funcgroup, '?');
    dpp_parseline(funcgroup[1], operands, ':');

    if(!dpp_isnumeric(operands[0]) || !dpp_isnumeric(operands[1]))
    {
        for(new i; i < 2; i++)
        {
            dpp_argarraycheck(operands[i]);
            dpp_argfunccheck(operands[i]);
            dpp_argvarcheck(operands[i]);
        }
    }

    if(!strcmp(funcgroup[0], "add"))
    {
        if(dpp_config[math_comp] == 0)
        {
            dpp_error("Component \"math\" is not imported.",);
            return 1;
        }
        format(newvalue, sizeof newvalue, "%i", 
            strval(operands[0])+strval(operands[1]));
        return format(arg, strlen(arg), newvalue);
    }
    if(!strcmp(funcgroup[0], "sub"))
    {
        if(dpp_config[math_comp] == 0)
        {
            dpp_error("Component \"math\" is not imported.",);
            return 1;
        }
        format(newvalue, sizeof newvalue, "%i", 
            strval(operands[0])-strval(operands[1]));
        return format(arg, strlen(arg), newvalue);
    }
    if(!strcmp(funcgroup[0], "mul"))
    {
        if(dpp_config[math_comp] == 0)
        {
            dpp_error("Component \"math\" is not imported.",);
            return 1;
        }
        format(newvalue, sizeof newvalue, "%i", 
            strval(operands[0])*strval(operands[1]));
        return format(arg, strlen(arg), newvalue);
    }
    if(!strcmp(funcgroup[0], "div"))
    {
        if(dpp_config[math_comp] == 0)
        {
            dpp_error("Component \"math\" is not imported.",);
            return 1;
        }
        format(newvalue, sizeof newvalue, "%i", 
            strval(operands[0])/strval(operands[1]));
        return format(arg, strlen(arg), newvalue);
    }
    if(!strcmp(funcgroup[0], "exp"))
    {
        if(dpp_config[math_comp] == 0)
        {
            dpp_error("Component \"math\" is not imported.",);
            return 1;
        }
        format(newvalue, sizeof newvalue, "%i", 
            floatpower(Float:strval(operands[0]), Float:strval(operands[1])));
        return format(arg, strlen(arg), newvalue);
    }
    return 1;
}

stock __dpp_domath(math_operator, operand1, operand2)
{
    if(math_operator == '+')
    {
        return floatround(Float:(operand1+operand2));
    }
    if(math_operator == '-')
    {
        return floatround(Float:(operand1-operand2));
    }
    if(math_operator == '*')
    {
        return floatround(Float:(operand1*operand2));
    }
    if(math_operator == '/')
    {
        return floatround(Float:(operand1/operand2));
    }
    if(math_operator == '^')
    {
        return floatround(Float:(operand1^operand2));
    }
    return 0;
}