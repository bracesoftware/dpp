/*
*
* D++ Scripting Language
*     Made for a SA:MP server
*
* Support for classes
*
* 
* - by: DEntisT, (c) 2022
*
*/

#define dpp_classelement_var 0
#define dpp_classelement_const 1
#define dpp_classelement_form 2

stock dpp_argclasscheck(arg[])
{
    new 
        newvalue[dpp_argcharsize],
        classvalid = 0,
        classelementvalid[3] = {0,0,0},
        funcgroup[2][100];
    dpp_parseline(arg, funcgroup, ':');

    for(new i = 1; i < dpp_maxclass; i++)
    {
        if(!strcmp(dpp_classname[i],funcgroup[0]) && dpp_validclass[i] == 1)
        {
            classvalid = 1;
            break;
        }
    }

    for(new i = 1; i < dpp_maxfuncs; i++)
    {
        if(!strcmp(dpp_funcname[i],funcgroup[1]) && dpp_validfunc[i] == 1)
        {
            classelementvalid[dpp_classelement_form] = 1;
            break;
        }
    }

    for(new i = 1; i < dpp_maxconst; i++)
    {
        if(!strcmp(dpp_constdata[i][const_name],funcgroup[1]) && dpp_constdata[i][const_valid] == 1)
        {
            classelementvalid[dpp_classelement_const] = 1;
            break;
        }
    }

    for(new i = 1; i < dpp_maxvar; i++)
    {
        if(!strcmp(dpp_vardata[i][var_name],funcgroup[1]) && dpp_vardata[i][var_valid] == 1)
        {
            classelementvalid[dpp_classelement_var] = 1;
            break;
        }
    }

    if(classvalid == 1 && (classelementvalid[0] == 1 || classelementvalid[1] == 1 || classelementvalid[2] == 1))
    {
        if(classelementvalid[dpp_classelement_var] == 1)
        {
            format(newvalue,sizeof(newvalue),"DPPCv@%s_%s",funcgroup[0],funcgroup[1]);
            strmid(arg, newvalue, 0, dpp_argcharsize,dpp_argcharsize);
            return 1;
        }
        if(classelementvalid[dpp_classelement_const] == 1)
        {
            format(newvalue,sizeof(newvalue),"DPPCc@%s_%s",funcgroup[0],funcgroup[1]);
            strmid(arg, newvalue, 0, dpp_argcharsize,dpp_argcharsize);
            return 1;
        }
        if(classelementvalid[dpp_classelement_form] == 1)
        {
            format(newvalue,sizeof(newvalue),"DPPCf@%s_%s",funcgroup[0],funcgroup[1]);
            strmid(arg, newvalue, 0, dpp_argcharsize,dpp_argcharsize);
            return 1;
        }
    }

    dpp_debug("Class backtrace:\n\tfuncgroup[0] : '%s'\n\tfuncgroup[1] : '%s'\n\targ : '%s'",funcgroup[0],funcgroup[1],arg);
    return 1;
}

stock dpp_createclass(const name[])
{
    for(new i = 1; i < dpp_maxclass; i++)
    {
        if(dpp_validclass[i] == 0)
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
                dpp_error("Invalid class name.",);
                return 1;
            }

            dpp_validclass[i] = 1;
            strmid(dpp_classname[i], name, 0, strlen(dpp_classname[i]), strlen(dpp_classname[i]));
            dpp_workingclassid = i;
            return 1;
        }
    }
    return 1;
}

stock dpp_hookclass(const name[])
{
    for(new i = 1; i < dpp_maxclass; i++)
    {
        if(!strcmp(dpp_classname[i],name) && dpp_validclass[i] == 1)
        {
            dpp_workingclassid = i;
            return 1;
        }
    }
    dpp_error("Class \"%s\" does not exist.",name);
    return 1;
}