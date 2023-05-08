/*
*
* D++ Scripting Language
*     Made for a SA:MP server
*
* Support for vars
*
* 
* - by: DEntisT, (c) 2022
*
*/


stock dpp_argvarcheck(arg[])
{
    new newvalue[dpp_argcharsize];
    for(new i; i < dpp_maxvar; i++)
    {
        if(!strcmp(dpp_vardata[i][var_name], arg))
        {
            if(dpp_vardata[i][var_valid] == 1)
            {
                if(dpp_vardata[i][var_type] == dpp_var_type_int)
                {
                    format(newvalue, dpp_argcharsize, "%i", 
                        dpp_vardata[i][integervalue]);
                }
                if(dpp_vardata[i][var_type] == dpp_var_type_bool)
                {
                    if(dpp_vardata[i][boolvalue] == 1)
                    {
                        strmid(arg, "true", 0, dpp_argcharsize, dpp_argcharsize);
                    }
                    if(dpp_vardata[i][boolvalue] == 0)
                    {
                        strmid(arg, "false", 0, dpp_argcharsize, dpp_argcharsize);
                    }
                }
                if(dpp_vardata[i][var_type] == dpp_var_type_str)
                {
                    format(newvalue, dpp_argcharsize, "\"%s\"", 
                        dpp_vardata[i][stringvalue]);
                }
                dpp_debug("argarraycheck debug\n\tarr : '%s'\n\targ : '%s'\n\tnewvalue : '%s'", dpp_vardata[i][var_name], arg, newvalue);
                if(dpp_vardata[i][var_type] != dpp_var_type_bool)
                {
                    strmid(arg, newvalue, 0, dpp_argcharsize, dpp_argcharsize);
                }
                dpp_debug("argarraycheck debug 2\n\tarr : '%s'\n\targ : '%s'\n\tnewvalue : '%s'", dpp_vardata[i][var_name], arg, newvalue);
                return 1;
            }
        }
    }
    return 1;
}

///////////////////////////CREATE/////////////////////////////

stock dpp_createintvar(name[], value)
{
    for(new i; i < dpp_maxvar; i++)
    {
        if(dpp_vardata[i][var_valid] == 0)
        {
            new name_error;

            for(new x; x < strlen(name); x++)
            {
                if(name[x] == '\"') name_error = 1;
                if(name[x] == ' ') name_error = 1;
                if(name[x] == '\t') name_error = 1;
            }
            if(dpp_isnumeric(name)) name_error = 1;
            if(name_error == 1)
            {
                dpp_error("Invalid symbol name.",);
                return 1;
            }

            if(dpp_workingclassid != dpp_invalidclass)
            {
                new newvalue[dpp_argcharsize];
                format(newvalue,sizeof(newvalue),"DPPCv@%s_%s",dpp_classname[dpp_workingclassid],name);
                strmid(name, newvalue, 0, dpp_argcharsize,dpp_argcharsize);
            }

            dpp_debug("variable \"%s\" assigned a value : %i",name,value);
            strmid(dpp_vardata[i][var_name], name, 0, 64);
            dpp_vardata[i][integervalue] = value;
            dpp_vardata[i][var_type] = dpp_var_type_int;
            dpp_vardata[i][var_valid] = 1;
            return 1;
        }
    }
    return 1;
}

stock dpp_createboolvar(name[], value)
{
    for(new i; i < dpp_maxvar; i++)
    {
        if(dpp_vardata[i][var_valid] == 0)
        {
            new name_error;

            for(new x; x < strlen(name); x++)
            {
                if(name[x] == '\"') name_error = 1;
                if(name[x] == ' ') name_error = 1;
                if(name[x] == '\t') name_error = 1;
            }
            if(dpp_isnumeric(name)) name_error = 1;
            if(name_error == 1)
            {
                dpp_error("Invalid symbol name.",);
                return 1;
            }

            if(dpp_workingclassid != dpp_invalidclass)
            {
                new newvalue[dpp_argcharsize];
                format(newvalue,sizeof(newvalue),"DPPCv@%s_%s",dpp_classname[dpp_workingclassid],name);
                strmid(name, newvalue, 0, dpp_argcharsize,dpp_argcharsize);
            }

            dpp_debug("variable \"%s\" assigned a value : %s",name,value ? "true" : "false");
            strmid(dpp_vardata[i][var_name], name, 0, 64);
            dpp_vardata[i][boolvalue] = value;
            dpp_vardata[i][var_type] = dpp_var_type_bool;
            dpp_vardata[i][var_valid] = 1;
            return 1;
        }
    }
    return 1;
}

stock dpp_createstrvar(name[], const value[])
{
    for(new i; i < dpp_maxvar; i++)
    {
        if(dpp_vardata[i][var_valid] == 0)
        {
            new name_error;

            for(new x; x < strlen(name); x++)
            {
                if(name[x] == '\"') name_error = 1;
                if(name[x] == ' ') name_error = 1;
                if(name[x] == '\t') name_error = 1;
            }
            if(dpp_isnumeric(name)) name_error = 1;
            if(name_error == 1)
            {
                dpp_error("Invalid symbol name.",);
                return 1;
            }

            if(dpp_workingclassid != dpp_invalidclass)
            {
                new newvalue[dpp_argcharsize];
                format(newvalue,sizeof(newvalue),"DPPCv@%s_%s",dpp_classname[dpp_workingclassid],name);
                strmid(name, newvalue, 0, dpp_argcharsize,dpp_argcharsize);
            }

            dpp_debug("variable \"%s\" assigned a value : \"%s\"",name,value);
            strmid(dpp_vardata[i][var_name], name, 0, 64);
            strmid(dpp_vardata[i][stringvalue], value, 0, 256);
            dpp_vardata[i][var_type] = dpp_var_type_str;
            dpp_vardata[i][var_valid] = 1;
            return 1;
        }
    }
    return 1;
}

///////////////////////////SET///////////////////////////////

stock dpp_setintvar(const name[], value)
{
    for(new i; i < dpp_maxvar; i++)
    {
        if(!strcmp(dpp_vardata[i][var_name], name) && dpp_vardata[i][var_valid] == 1)
        {
            dpp_debug("\"%s\" value changed to \"%i\"", name, value);
            dpp_vardata[i][integervalue] = value;
            return 1;
        }
    }
    dpp_error("INT : Unable to find a variable: '%s'",name);
    return 1;
}

stock dpp_setboolvar(const name[], value)
{
    for(new i; i < dpp_maxvar; i++)
    {
        if(!strcmp(dpp_vardata[i][var_name], name) && dpp_vardata[i][var_valid] == 1)
        {
            dpp_debug("\"%s\" value changed to \"%s\"", name, value ? "true" : "false");
            dpp_vardata[i][boolvalue] = value;
            return 1;
        }
    }
    dpp_error("BOOL : Unable to find a variable: '%s'",name);
    return 1;
}

stock dpp_setstrvar(const name[], const value[])
{
    for(new i; i < dpp_maxvar; i++)
    {
        if(!strcmp(dpp_vardata[i][var_name], name) && dpp_vardata[i][var_valid] == 1)
        {
            dpp_debug("\"%s\" value changed to \"%s\"", name, value);
            strmid(dpp_vardata[i][stringvalue], value, 0, 256);
            return 1;
        }
    }
    dpp_error("STR : Unable to find a variable: '%s'",name);
    return 1;
}



///////////////////////////DELETE///////////////////////


stock dpp_deleteintvar(const name[])
{
    for(new i; i < dpp_maxvar; i++)
    {
        if(!strcmp(dpp_vardata[i][var_name], name))
        {
            if(dpp_vardata[i][var_valid] == 1)
            {
                if(dpp_vardata[i][var_type] != dpp_var_type_int)
                {
                    dpp_error("variable \"%s\" is not an integer.", name);
                    return 1;
                }

                strmid(dpp_vardata[i][var_name], "unknown", 0, 64);
                dpp_vardata[i][var_valid] = 0;
                dpp_vardata[i][integervalue] = 0;
                return 1;
            }
        }
        dpp_error("variable \"%s\" not found.", name);
    }
    return 1;
}

stock dpp_deleteboolvar(const name[])
{
    for(new i; i < dpp_maxvar; i++)
    {
        if(!strcmp(dpp_vardata[i][var_name], name))
        {
            if(dpp_vardata[i][var_valid] == 1)
            {
                if(dpp_vardata[i][var_type] != dpp_var_type_bool)
                {
                    dpp_error("variable \"%s\" is not a boolean.", name);
                    return 1;
                }

                strmid(dpp_vardata[i][var_name], "unknown", 0, 64);
                dpp_vardata[i][var_valid] = 0;
                dpp_vardata[i][boolvalue] = 0;
                return 1;
            }
        }
        dpp_error("variable \"%s\" not found.", name);
    }
    return 1;
}

stock dpp_deletestrvar(const name[])
{
    for(new i; i < dpp_maxvar; i++)
    {
        if(!strcmp(dpp_vardata[i][var_name], name))
        {
            if(dpp_vardata[i][var_valid] == 1)
            {
                if(dpp_vardata[i][var_type] != dpp_var_type_str)
                {
                    dpp_error("variable \"%s\" is not a string.", name);
                    return 1;
                }

                strmid(dpp_vardata[i][var_name], "unknown", 0, 64);
                dpp_vardata[i][var_valid] = 0;
                strmid(dpp_vardata[i][stringvalue], "empty", 0, 256);
                return 1;
            }
        }
        dpp_error("variable \"%s\" not found.", name);
    }
    return 1;
}