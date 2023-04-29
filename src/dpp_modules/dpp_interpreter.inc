/*
 *
 * D++ Scripting Language
 *     Made for a SA:MP server
 *
 * Interpreter/"compiler"
 *
 * 
 * - by: DEntisT, (c) 2022
 *
 */

new process_backtrace[2048];
new process_bcktrc[1024];

stock dpp_process(const line[])
{
    if(dpp_terminated == 1)
    {
        return 1;
    }
    if(isnull(line))
    {
        return 1;
    }
    new codeblockline[1024];
    new args[10][dpp_argcharsize], funcgroup[2][20];

    new extracode[3000];
    new line2[3000];
    
    strmid(line2, line, 0, strlen(line), strlen(line));
    dpp_checkforifexpression(line, line2, extracode, "->");
    
    dpp_parseline(line, args, ',');
    dpp_parseline(args[0], funcgroup, '.');

    //using::console.cout,"Hello World";

    //  funcgroup[0]    using::console
    //  funcgroup[1]    cout
    //  args[1]         "Hello World"

    //Cleanup:
    format(process_backtrace,sizeof process_backtrace,
        "Process backtrace:");
    format(process_bcktrc,sizeof process_bcktrc,"");

    format(process_bcktrc,sizeof process_bcktrc,"\n\tline: '%s'",line); 
    strcat(process_backtrace, process_bcktrc);

    for(new i; i < 2; i++)
    {
        format(process_bcktrc,sizeof process_bcktrc,"\n\tfuncgroup[%i]: '%s'",i,funcgroup[i]);  
        strcat(process_backtrace, process_bcktrc);
    }

    for(new i; i < 10; i++)
    {
        format(process_bcktrc,sizeof process_bcktrc,"\n\targs[%i]: '%s'",i,args[i]);    
        strcat(process_backtrace, process_bcktrc);
    }

    format(process_bcktrc,sizeof process_bcktrc,"\n\textracode: '%s'",extracode);    
    strcat(process_backtrace, process_bcktrc);

    dpp_debug("%s", process_backtrace);

    if(!strcmp(funcgroup[0], "public&form"))
    {
        new isautoform = 0;
        if(!strcmp(funcgroup[1], "OnGameModeInit")) isautoform = 1;
        if(!strcmp(funcgroup[1], "OnGameModeExit")) isautoform = 1;

        if(isautoform == 1)
        {
            dpp_warning("'%s' is a name of an existing auto form.", funcgroup[1]);
        }

        dpp_createfunc(funcgroup[1]);
        return 1;
    }
    if(!strcmp(funcgroup[0], "auto&form"))
    {
        dpp_createfunc(funcgroup[1], 1);
        return 1;
    }
    if(!strcmp(funcgroup[0], "do"))
    {
        dpp_interpreter = 0;
        return 1;
    }
    if(!strcmp(funcgroup[0], "end"))
    {
        dpp_interpreter = 1;
        return 1;
    }
    if(!strcmp(funcgroup[0], "exit"))
    {
        dpp_terminated = 1;
        dpp_print("Process terminated; restart the machine.");
        return 1;
    }

    #if DPP_BRACES == 1
    new line_wo_brace[1024];
    new char_idx = strlen(funcgroup[0]) - 1;
    if(funcgroup[0][char_idx] == '{')
    {
        dpp_interpreter = 0;
        strmid(line_wo_brace, line, 0, strlen(line));
        strdel(line_wo_brace, 0, 1);
        return 1;
    }
    if(funcgroup[0][char_idx] == '}')
    {
        dpp_interpreter = 1;
        return 1;
    }
    #endif



    if(dpp_interpreter == 0)
    {
        format(codeblockline, sizeof codeblockline, "%s;", line);
        #if DPP_BRACES == 1
        format(codeblockline, sizeof codeblockline, "%s;", line_wo_brace);
        #endif
        dpp_debug("codeblockline:%s",codeblockline);
        dpp_debug("dpp_currentfuncid:%i",dpp_currentfuncid);
        strcat(dpp_funccodeblock[dpp_currentfuncid], codeblockline);
        return 1;
    }

    for(new i; i < 10; i++)
    {
        dpp_argarraycheck(args[i]);
        dpp_argfunccheck(args[i]);
        dpp_argvarcheck(args[i]);
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            IF-EXPRESSIONS SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(dpp_isifexp == 1) //if.equ,1,1->using::console.cout,"1 is 1";
    {
        dpp_isifexp = 0;
        dpp_parseline(line2, args, ',');
        dpp_parseline(args[0], funcgroup, '.');
        
        for(new i; i < 10; i++)
        {
            dpp_argarraycheck(args[i]);
            dpp_argfunccheck(args[i]);
            dpp_argvarcheck(args[i]);
        }

        if(!strcmp(funcgroup[0], "if"))
        {
            if(!strcmp(funcgroup[1], "equ"))
            {
                if(!strcmp(args[1], args[2]))
                {
                    dpp_subexecute(extracode);
                }
                return 1;
            }

            if(!strcmp(funcgroup[1], "notequ"))
            {
                if(strcmp(args[1], args[2]))
                {
                    dpp_subexecute(extracode);
                }
                return 1;
            }
            dpp_error("Unknown if-expression element : \"%s\"",funcgroup[1]);
        }
        return 1;
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            CONST SYS
    ////
    ////
    ///////////////////////////////////////////////////////


    if(!strcmp(funcgroup[0], "const::define"))
    {
        if(!strcmp(funcgroup[1], "int"))
        {
            if(!dpp_isnumeric(args[2]))
            {
                dpp_error("Argument error; value must be an integer.",);
                return 0;
            }

            dpp_createintconst(args[1],strval(args[2]));
            return 1;
        }
        if(!strcmp(funcgroup[1], "bool"))
        {
            if(strcmp(args[2],"true") && strcmp(args[2],"false"))
            {
                dpp_error("Argument error; value must be either 'true' or 'false'.",);
                return 0;
            }

            new dpp_boolval;


            if(!strcmp(args[2], "false"))
            {
                dpp_boolval = 0;
            }
            if(!strcmp(args[2], "true"))
            {
                dpp_boolval = 1;
            }

            dpp_createboolconst(args[1],dpp_boolval);
            return 1;
        }
        if(!strcmp(funcgroup[1], "str"))
        {
            new mul2, str2[dpp_argcharsize];
            strmid(str2, args[2], 0, dpp_argcharsize);
            for(new i; i < strlen(args[2]); i++)
            {
                if(args[2][i] == '\"') mul2++, strdel(args[2], i, i+1);
            }
            if(mul2 == 0)
            {
                dpp_error("You need to use '\"' to start a string.",);
                return 0;
            }
            if(mul2 != 2)
            {
                dpp_error("Argument error; [%i] \"%s\"", mul2, args[2]);
                return 0;
            }

            dpp_createstrconst(args[1],args[2]);
            return 1;
        }
        
        else
        {
            dpp_error("Unknown symbol type \"%s\".", funcgroup[1]);
            return 0;
        }
    }

    if(!strcmp(funcgroup[0], "const::undef"))
    {
        if(!strcmp(funcgroup[1], "int"))
        {
            dpp_deleteintconst(args[1]);
            return 1;
        }
        if(!strcmp(funcgroup[1], "bool"))
        {
            dpp_deleteboolconst(args[1]);
            return 1;
        }
        if(!strcmp(funcgroup[1], "str"))
        {
            dpp_deletestrconst(args[1]);
            return 1;
        }
        
        else
        {
            dpp_error("Unknown symbol type \"%s\".", funcgroup[1]);
            return 0;
        }
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            VAR SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "var::define"))
    {
        if(!strcmp(funcgroup[1], "int"))
        {
            if(!dpp_isnumeric(args[2]))
            {
                dpp_error("Argument error; value must be an integer.",);
                return 0;
            }

            dpp_createintvar(args[1],strval(args[2]));
            return 1;
        }
        if(!strcmp(funcgroup[1], "bool"))
        {
            if(strcmp(args[2],"true") && strcmp(args[2],"false"))
            {
                dpp_error("Argument error; value must be either 'true' or 'false'.",);
                return 0;
            }

            new dpp_boolval;


            if(!strcmp(args[2], "false"))
            {
                dpp_boolval = 0;
            }
            if(!strcmp(args[2], "true"))
            {
                dpp_boolval = 1;
            }

            dpp_createboolvar(args[1],dpp_boolval);
            return 1;
        }
        if(!strcmp(funcgroup[1], "str"))
        {
            new mul2, str2[dpp_argcharsize];
            strmid(str2, args[2], 0, dpp_argcharsize);
            for(new i; i < strlen(args[2]); i++)
            {
                if(args[2][i] == '\"') mul2++, strdel(args[2], i, i+1);
            }
            if(mul2 == 0)
            {
                dpp_error("You need to use '\"' to start a string.",);
                return 0;
            }
            if(mul2 != 2)
            {
                dpp_error("Argument error; [%i] \"%s\"", mul2, args[2]);
                return 0;
            }

            dpp_createstrvar(args[1],args[2]);
            return 1;
        }
        
        else
        {
            dpp_error("Unknown symbol type \"%s\".", funcgroup[1]);
            return 0;
        }
    }

    if(!strcmp(funcgroup[0], "var::undef"))
    {
        if(!strcmp(funcgroup[1], "int"))
        {
            dpp_deleteintvar(args[1]);
            return 1;
        }
        if(!strcmp(funcgroup[1], "bool"))
        {
            dpp_deleteboolvar(args[1]);
            return 1;
        }
        if(!strcmp(funcgroup[1], "str"))
        {
            dpp_deletestrvar(args[1]);
            return 1;
        }
        
        else
        {
            dpp_error("Unknown symbol type \"%s\".", funcgroup[1]);
            return 0;
        }
    }

    if(!strcmp(funcgroup[0], "var::set"))
    {
        if(!strcmp(funcgroup[1], "int"))
        {
            if(!dpp_isnumeric(args[2]))
            {
                dpp_error("Argument error; value must be an integer.",);
                return 0;
            }

            dpp_setintvar(args[1],strval(args[2]));
            return 1;
        }
        if(!strcmp(funcgroup[1], "bool"))
        {
            if(strcmp(args[2],"true") && strcmp(args[2],"false"))
            {
                dpp_error("Argument error; value must be either 'true' or 'false'.",);
                return 0;
            }

            new dpp_boolval;


            if(!strcmp(args[2], "false"))
            {
                dpp_boolval = 0;
            }
            if(!strcmp(args[2], "true"))
            {
                dpp_boolval = 1;
            }

            dpp_setboolvar(args[1],dpp_boolval);
            return 1;
        }
        if(!strcmp(funcgroup[1], "str"))
        {
            new mul2, str2[dpp_argcharsize];
            strmid(str2, args[2], 0, dpp_argcharsize);
            for(new i; i < strlen(args[2]); i++)
            {
                if(args[2][i] == '\"') mul2++, strdel(args[2], i, i+1);
            }
            if(mul2 == 0)
            {
                dpp_error("You need to use '\"' to start a string.",);
                return 0;
            }
            if(mul2 != 2)
            {
                dpp_error("Argument error; [%i] \"%s\"", mul2, args[2]);
                return 0;
            }

            dpp_setstrvar(args[1],args[2]);
            return 1;
        }
        
        else
        {
            dpp_error("Unknown symbol type \"%s\".", funcgroup[1]);
            return 0;
        }
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            PRAGMA OPT SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "pragma::option"))
    {
        if(!strcmp(funcgroup[1], "debug"))
        {
            dpp_argarraycheck(args[1]);
            if(!strcmp(args[1], "false"))
            {
                dpp_option_debug = 0;
                dpp_print("Debug has been disabled.");
                return 1;
            }
            if(!strcmp(args[1], "true"))
            {
                dpp_option_debug = 1;
                dpp_print("Debug has been enabled.");
                return 1;
            }

            if(!strcmp(args[1], "default"))
            {
                dpp_option_debug = 0;
                dpp_print("Debug has been disabled.");
                return 1;
            }
            else
            {
                dpp_error("Wrong option value at \"%s\"; value can be either 'true' or 'false'.\nCurrent value: '%s'", line,args[1]);
            }
            return 1;
        }
        if(!strcmp(funcgroup[1], "warnings"))
        {
            dpp_argarraycheck(args[1]);
            if(!strcmp(args[1], "false"))
            {
                dpp_option_warnings = 0;
                dpp_print("Warning system has been disabled.");
                return 1;
            }
            if(!strcmp(args[1], "true"))
            {
                dpp_option_warnings = 1;
                dpp_print("Warning system has been enabled.");
                return 1;
            }

            if(!strcmp(args[1], "default"))
            {
                dpp_option_warnings = 1;
                dpp_print("Warning system has been enabled.");
                return 1;
            }
            else
            {
                dpp_error("Wrong option value at \"%s\"; value can be either 'true' or 'false'.\nCurrent value: '%s'", line,args[1]);
            }
            return 1;
        }
        
        else
        {
            dpp_error("Unknown option \"%s\".", funcgroup[1]);
            return 0;
        }
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            PACKAGE SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "import::component"))
    {
        if(!strcmp(funcgroup[1], "console"))
        {
            dpp_config[console_comp] = 1;
            return 1;
        }
        if(!strcmp(funcgroup[1], "system"))
        {
            dpp_config[system_comp] = 1;
            return 1;
        }
        if(!strcmp(funcgroup[1], "samp"))
        {
            dpp_config[samp_comp] = 1;
            return 1;
        }
        else
        {
            dpp_error("Unknown component \"%s\".", funcgroup[1]);
            return 0;
        }
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            IMPORT SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "import::module"))
    {
        for(new i; i < strlen(args[1]); i++)
        {
            if(args[1][i] == '\"') strdel(args[1], i, i+1);
        }
        new filename[64];
        format(filename, sizeof filename, "modules/%s.dpp", args[1]);
        if(fexist(filename)) return dpp_executefile(filename);
        else
        {
            dpp_error("Cannot read from module: \"%s\"", filename);
            return 0;
        }
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            USER FUNC SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "using::user"))
    {
        for(new i; i < dpp_maxfuncs; i++)
        {
            if(!strcmp(dpp_funcname[i], funcgroup[1]))
            {
                dpp_returned[i] = 0;
                dpp_processfunc = i;
                dpp_subexecute(dpp_funccodeblock[i]);
                dpp_debug("dpp_funccodeblock[i]:%s",dpp_funccodeblock[999]);
                return 1;
            }
        }
        dpp_error("Form \"%s\" isn't registered.", funcgroup[1]);
        return 1;
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            RETURN SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "return"))
    {
        if(dpp_processfunc == 0)
        {
            dpp_error("Expression \"return\" can be only used inside a form code block.",);
            return 1;
        }
        if(!strcmp(funcgroup[1], "int"))
        {
            if(!dpp_isnumeric(args[1]))
            {
                dpp_error("Return value must be an integer.",);
                return 1;
            }

            new int_return = strval(args[1]);

            dpp_returned[dpp_processfunc] = 1;
            dpp_returntype[dpp_processfunc] = dpp_rtn_type_int;
            dpp_funcreturn_int[dpp_processfunc] = int_return;

            dpp_processfunc = 0;
            return 1;
        }
        if(!strcmp(funcgroup[1], "bool"))
        {
            if(!strcmp(args[1], "true"))
            {
                dpp_returned[dpp_processfunc] = 1;
                dpp_returntype[dpp_processfunc] = dpp_rtn_type_bool;
                dpp_funcreturn_bool[dpp_processfunc] = 1;

                dpp_processfunc = 0;
                return 1;
            }
            if(!strcmp(args[1], "false"))
            {
                dpp_returned[dpp_processfunc] = 1;
                dpp_returntype[dpp_processfunc] = dpp_rtn_type_bool;
                dpp_funcreturn_bool[dpp_processfunc] = 0;

                dpp_processfunc = 0;
                return 1;
            }
            else
            {
                dpp_error("Return value must be either \"true\" or \"false\".",);
            }

            return 1;
        }
        if(!strcmp(funcgroup[1], "str"))
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
                return 0;
            }
            if(mul != 2)
            {
                dpp_error("Argument error; [%i] \"%s\"", mul, args[1]);
                return 0;
            }

            dpp_returned[dpp_processfunc] = 1;
            dpp_returntype[dpp_processfunc] = dpp_rtn_type_str;
            strmid(dpp_funcreturn_str[dpp_processfunc],args[1],0,
                dpp_argcharsize,dpp_argcharsize);

            dpp_debug("dpp_funcreturn_str[dpp_processfunc] : \"%s\"\nargs[1] : \"%s\"",dpp_funcreturn_str[dpp_processfunc],args[1]);

            dpp_processfunc = 0;
            return 1;
        }

        else
        {
            dpp_error("Unknown return type \"%s\".", funcgroup[1]);
        }
        return 1;
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            CONSOLE comp FUNC SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "using::console"))
    {
        if(dpp_config[console_comp] == 0)
        {
            dpp_error("Component \"console\" is not imported.",);
            return 1;
        }
        // If the function used it "print"
        if(!strcmp(funcgroup[1], "cout"))
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
                return 0;
            }
            if(mul != 2)
            {
                dpp_error("Argument error; [%i] \"%s\"", mul, args[1]);
                return 0;
            }

            //dpp_debug("Line \"%s\" successfully executed.", line);
            print(args[1]);
            return 1;
        }
        else
        {
            dpp_error("Unknown form in the component \"console\".",);
            return 0;
        }
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            SYSTEM comp FUNC SYS
    ////
    ////
    ///////////////////////////////////////////////////////

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
                return 0;
            }
            if(mul != 2)
            {
                dpp_error("Argument error; [%i] \"%s\"", mul, args[1]);
                return 0;
            }

            // do nothing, this is a comment
            return 1;
        }
        else
        {
            dpp_error("Unknown form in the component \"system\".",);
            return 0;
        }
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            SAMP comp FUNC SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    
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
                return 0;
            }
            if(mul != 2)
            {
                dpp_error("Argument error; [%i] \"%s\"", mul, args[1]);
                return 0;
            }

            SetGameModeText(args[1]);
            return 1;
        }

        if(!strcmp(funcgroup[1], "SetMaxPlayers"))
        {
            if(!dpp_isnumeric(args[1]))
            {
                dpp_error("Argument error; value must be an integer.",);
                return 0;
            }

            SetMaxPlayers(strval(args[1]));
            return 1;
        }

        else
        {
            dpp_error("Unknown form in the component \"samp\".",);
            return 0;
        }
    }
    
    if(strlen(line) > 5)
    {
        dpp_error("Unknown element \"%s\".", line);
    }
    return 1;
}

stock dpp_subprocess(const line[])
{
    dpp_process(line);
    return 1;
}