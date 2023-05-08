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
    new
        iscomment = 0;

    if(!strcmp(line,"/*"))
    {
        iscomment = 1;
    }
    if(!strcmp(line,"*/"))
    {
        iscomment = 0;
    }
    if(iscomment == 1)
    {
        return 1;
    }
    if(dpp_terminated == 1)
    {
        return 1;
    }
    if(isnull(line))
    {
        return 1;
    }
    new codeblockline[1024];
    new
        args[20][dpp_argcharsize], 
        funcgroup[2][1024],
        args_const[20][dpp_argcharsize];

    new extracode[3000];
    new line2[3000];
    new dpp_funcfound;
    
    strmid(line2, line, 0, strlen(line), strlen(line));
    dpp_checkforconditionals(line, line2, extracode, "->");

    dpp_parseline(line, args, ',');
    dpp_parseline(args[0], funcgroup, '.');

    for(new i; i < 15; i++)
    {
        strmid(args_const[i], args[i],0,dpp_argcharsize,dpp_argcharsize);
    }

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

    for(new i; i < 20; i++)
    {
        format(process_bcktrc,sizeof process_bcktrc,"\n\targs[%i]: '%s'",i,args[i]);    
        strcat(process_backtrace, process_bcktrc);
    }

    format(process_bcktrc,sizeof process_bcktrc,"\n\textracode: '%s'",extracode);    
    strcat(process_backtrace, process_bcktrc);

    dpp_debug("%s", process_backtrace);

    for(new i; i < strlen(funcgroup[0]); i++)
    {
        if(funcgroup[0][i] == '\t') strdel(funcgroup[0], i,i+1);
        if(funcgroup[0][i] == '\n') strdel(funcgroup[0], i,i+1);
        if(funcgroup[0][i] == ' ') strdel(funcgroup[0], i,i+1);
    }
    for(new i; i < strlen(funcgroup[1]); i++)
    {
        if(funcgroup[1][i] == '\t') strdel(funcgroup[1], i,i+1);
        if(funcgroup[1][i] == '\n') strdel(funcgroup[1], i,i+1);
        if(funcgroup[1][i] == ' ') strdel(funcgroup[1], i,i+1);
    }

    if(!strcmp(funcgroup[0], "exit"))
    {
        dpp_terminated = 1;
        dpp_print("Process terminated; restart the machine.");
        return 1;
    }

    if(!strcmp(funcgroup[0], "end"))
    {
        dpp_sysreturned = 0;
        dpp_interpreter = 1;
        return 1;
    }

    if(!strcmp(funcgroup[0], "do"))
    {
        dpp_interpreter = 0;
        return 1;
    }

    //if(dpp_sysreturned == 1) return 1;


    ///////////////////////////////////////////////////////
    ////
    ////
    ////            IMPL
    ////
    ////
    ///////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            FORM SYS
    ////
    ////
    ///////////////////////////////////////////////////////



    if(!strcmp(funcgroup[0], "public&form"))
    {
        new isautoform = 0;
        new arguments[2][1024];
        dpp_parseline(funcgroup[1],arguments,'?');
        //system autoforms
        if(dpp_config[system_comp] == 1)
        {
            if(!strcmp(funcgroup[1], "main")) isautoform = 1;
        }
        //samp autoforms
        if(dpp_config[samp_comp] == 1)
        {
            if(!strcmp(funcgroup[1], "OnGameModeInit")) isautoform = 1;
            if(!strcmp(funcgroup[1], "OnGameModeExit")) isautoform = 1;
        }
        //discord api autoforms
        if(dpp_apis[discord] == 1)
        {
            if(!strcmp(funcgroup[1], "discord_init")) isautoform = 1;
        }

        if(isautoform == 1)
        {
            dpp_warning("'%s' is a name of an existing auto form.", funcgroup[1]);
        }

        dpp_createfunc(arguments[0],arguments[1]);
        return 1;
    }
    if(!strcmp(funcgroup[0], "auto&form"))
    {
        new arguments[2][1024];
        dpp_parseline(funcgroup[1],arguments,'?');
        dpp_createfunc(arguments[0],arguments[1],1);
        return 1;
    }
    if(!strcmp(funcgroup[0], "hook&form"))
    {
        new arguments[2][1024];
        dpp_parseline(funcgroup[1],arguments,'?');
        dpp_createfunc(arguments[0],arguments[1],0,1);
        return 1;
    }
    if(!strcmp(funcgroup[0], "native&form"))
    {
        dpp_regnativeform(funcgroup[1]);
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
        if(!strcmp(funcgroup[0], "const::define") || !strcmp(funcgroup[0], "const::undef") ||
            !strcmp(funcgroup[0], "var::define") || !strcmp(funcgroup[0], "var::undef") ||
            !strcmp(funcgroup[0], "var::set") ||
                (!strcmp(funcgroup[0], "using::system") && !strcmp(funcgroup[1], "arginit")) ||
                (!strcmp(funcgroup[0], "using::files") && !strcmp(funcgroup[1], "read"))){
            if(i == 1)
            {
                dpp_argclasscheck(args[i]);
                dpp_argformargcheck(args[i]);
                i = 2;
            }
        }

        dpp_removeslashes(args[i]);
        dpp_argclasscheck(args[i]);
        dpp_argarraycheck(args[i]);
        dpp_argfunccheck(args[i]);
        dpp_argvarcheck(args[i]);
        dpp_argmathcheck(args[i]);
        dpp_argformargcheck(args[i]);

        dpp_formatarg(args[i]);
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            CLASS SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "public&class"))
    {
        dpp_createclass(funcgroup[1]);
        return 1;
    }
    if(!strcmp(funcgroup[0], "hook&class"))
    {
        dpp_hookclass(funcgroup[1]);
        return 1;
    }
    if(!strcmp(funcgroup[0], "class"))
    {
        if(!strcmp(funcgroup[1],"end"))
        {
            dpp_workingclassid = dpp_invalidclass;
        }
        return 1;
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            CONDITIONAL-EXPRESSIONS SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(dpp_isconditional == 1)
    {
        dpp_isconditional = 0;
        dpp_parseline(line2, args, ',');
        dpp_parseline(args[0], funcgroup, '.');

        for(new i; i < 15; i++)
        {
            strmid(args_const[i], args[i],0,dpp_argcharsize,dpp_argcharsize);
        }
        
        for(new i; i < 10; i++)
        {
            if(!strcmp(funcgroup[0], "const::define") || !strcmp(funcgroup[0], "const::undef") ||
                !strcmp(funcgroup[0], "var::define") || !strcmp(funcgroup[0], "var::undef") ||
                !strcmp(funcgroup[0], "var::set") || 
                (!strcmp(funcgroup[0], "using::system") && !strcmp(funcgroup[1], "arginit")) ||
                (!strcmp(funcgroup[0], "using::files") && !strcmp(funcgroup[1], "read")))
                {
                    if(i == 1)
                    {
                        dpp_argclasscheck(args[i]);
                        dpp_argformargcheck(args[i]);
                        i = 2;
                    }
                }

            dpp_removeslashes(args[i]);
            dpp_argclasscheck(args[i]);
            dpp_argarraycheck(args[i]);
            dpp_argfunccheck(args[i]);
            dpp_argvarcheck(args[i]);
            dpp_argmathcheck(args[i]);
            dpp_argformargcheck(args[i]);

            dpp_formatarg(args[i]);
        }
        // IF CHECKS
        //if.equ,1,1->using::console.cout,"1 is 1";
        if(!strcmp(funcgroup[0], "if"))
        {
            if(!strcmp(funcgroup[1], "equ"))
            {
                if(!strcmp(args[1], args[2]))
                {
                    dpp_subexecute2(extracode);
                }
                return 1;
            }

            if(!strcmp(funcgroup[1], "notequ"))
            {
                if(strcmp(args[1], args[2]))
                {
                    dpp_subexecute2(extracode);
                }
                return 1;
            }
            dpp_error("Unknown if-expression method : \"%s\"",funcgroup[1]);
        }
        // WHILE LOOPS
        //while.notequ,testvar,1->var::set.int,testvar,add?testvar:1&using::console.println,"{testvar}";
        if(!strcmp(funcgroup[0], "while"))
        {
            new 
                whileloopcode[2][1024];
            
            dpp_parseline(extracode,whileloopcode,'&');
            if(!strcmp(funcgroup[1], "equ"))
            {
                do
                {
                    for(new whilecodeid; whilecodeid < 2; whilecodeid++)
                    {
                        dpp_subexecute2(whileloopcode[whilecodeid]);
                    }

                    for(new i; i < 15; i++)
                    {
                        strmid(args[i], args_const[i],0,dpp_argcharsize,dpp_argcharsize);

                        dpp_removeslashes(args[i]);
                        dpp_argclasscheck(args[i]);
                        dpp_argarraycheck(args[i]);
                        dpp_argfunccheck(args[i]);
                        dpp_argvarcheck(args[i]);
                        dpp_argmathcheck(args[i]);
                        dpp_argformargcheck(args[i]);
                        dpp_formatarg(args[i]);
                    }

                    //dpp_print("While loop backtrace\nconst arg 1 : %s\t\t| const arg 2 : %s\narg 1 : %s\t\t| arg 2 : %s",args_const[1],args_const[2],args[1],args[2]);
                }
                while(dpp_strcmp(args[1], args[2]));
                return 1;
            }

            if(!strcmp(funcgroup[1], "notequ"))
            {
                do
                {
                    for(new whilecodeid; whilecodeid < 2; whilecodeid++)
                    {
                        dpp_subexecute2(whileloopcode[whilecodeid]);
                    }

                    for(new i; i < 15; i++)
                    {
                        strmid(args[i], args_const[i],0,dpp_argcharsize,dpp_argcharsize);
                        
                        dpp_removeslashes(args[i]);
                        dpp_argclasscheck(args[i]);
                        dpp_argarraycheck(args[i]);
                        dpp_argfunccheck(args[i]);
                        dpp_argvarcheck(args[i]);
                        dpp_argmathcheck(args[i]);
                        dpp_argformargcheck(args[i]);
                        dpp_formatarg(args[i]);
                    }

                    //dpp_print("While loop backtrace\nconst arg 1 : %s\t\t| const arg 2 : %s\narg 1 : %s\t\t| arg 2 : %s",args_const[1],args_const[2],args[1],args[2]);
                }
                while(!dpp_strcmp(args[1], args[2]));
                return 1;
            }
            dpp_error("Unknown while-loop method : \"%s\"",funcgroup[1]);
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
        
        if(!strcmp(funcgroup[1], "hooking"))
        {
            dpp_argarraycheck(args[1]);
            if(!strcmp(args[1], "false"))
            {
                dpp_option_hooking = 0;
                dpp_print("Hooking system has been disabled.");
                return 1;
            }
            if(!strcmp(args[1], "true"))
            {
                dpp_option_hooking = 1;
                dpp_print("Hooking system has been enabled.");
                return 1;
            }

            if(!strcmp(args[1], "default"))
            {
                dpp_option_hooking = 1;
                dpp_print("Hooking system has been enabled.");
                return 1;
            }
            else
            {
                dpp_error("Wrong option value at \"%s\"; value can be either 'true' or 'false'.\nCurrent value: '%s'", line,args[1]);
            }
            return 1;
        }
        //dpp_option_escapechar
        if(!strcmp(funcgroup[1], "ctrlchar"))
        {
            dpp_argarraycheck(args[1]);

            if(!strcmp(args[1], "default"))
            {
                dpp_option_escapechar = '\\';
                return 1;
            }
            dpp_option_escapechar = args[1][0];
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
    ////            COMPONENT SYS
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
        if(!strcmp(funcgroup[1], "math"))
        {
            dpp_config[math_comp] = 1;
            return 1;
        }
        if(!strcmp(funcgroup[1], "files"))
        {
            dpp_config[files_comp] = 1;
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
    ////            API SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "import::api"))
    {
        if(!strcmp(funcgroup[1], "discord"))
        {
            dpp_apis[discord] = 1;
            return 1;
        }
        
        else
        {
            dpp_error("Unknown API \"%s\".", funcgroup[1]);
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
                if(dpp_hookform[i] == 0)
                {
                    for(new argid; argid < dpp_maxformargs; argid++)
                    {
                        strmid(dpp_args[i][argid][dpp_argvalue],
                            args[argid+1],
                            0,
                            dpp_argcharsize,
                            dpp_argcharsize);
                    }
                    dpp_returned[i] = 0;
                    dpp_processfunc = i;
                    dpp_subexecute(dpp_funccodeblock[i], i);
                    dpp_debug("dpp_funccodeblock[i]:%s",dpp_funccodeblock[i]);

                    if(dpp_option_hooking == 1)
                    {
                        for(new hookfuncid; hookfuncid < dpp_maxfuncs; hookfuncid++)
                        {
                            if(!strcmp(dpp_funcname[hookfuncid], funcgroup[1]))
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
                                            args[argid+1],
                                            0,
                                            dpp_argcharsize,
                                            dpp_argcharsize);
                                    }
                                    dpp_returned[hookfuncid] = 0;
                                    dpp_processfunc = hookfuncid;
                                    dpp_subexecute(dpp_funccodeblock[hookfuncid], hookfuncid);
                                    dpp_debug("dpp_funccodeblock[hookfuncid]:%s",dpp_funccodeblock[hookfuncid]);
                                }
                            }
                        }
                    }
                    return 1;
                }
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
            dpp_sysreturned = 1;
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
                dpp_sysreturned = 1;
                return 1;
            }
            if(!strcmp(args[1], "false"))
            {
                dpp_returned[dpp_processfunc] = 1;
                dpp_returntype[dpp_processfunc] = dpp_rtn_type_bool;
                dpp_funcreturn_bool[dpp_processfunc] = 0;

                dpp_processfunc = 0;
                dpp_sysreturned = 1;
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
            dpp_sysreturned = 1;
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

    if(dpp_funcfound == 0)
    {
        dpp_funcfound = CallLocalFunction("dpp_processconsole", "ss", funcgroup,args);
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            SYSTEM comp FUNC SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(dpp_funcfound == 0)
    {
        dpp_funcfound = CallLocalFunction("dpp_processsystem", "ss", funcgroup,args);
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            SAMP comp FUNC SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(dpp_funcfound == 0)
    {
        dpp_funcfound = CallLocalFunction("dpp_processsamp", "ss", funcgroup,args);
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            MATH comp FUNC SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(dpp_funcfound == 0)
    {
        dpp_funcfound = CallLocalFunction("dpp_processmath", "ss", funcgroup,args);
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            FILES comp FUNC SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(dpp_funcfound == 0)
    {
        dpp_funcfound = CallLocalFunction("dpp_processfiles", "ss", funcgroup,args);
    }
    



    ///////////////////////////////////////////////////////
    ////
    ////
    ////            DISCORD API FUNC SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(dpp_funcfound == 0)
    {
        dpp_funcfound = CallLocalFunction("dpp_processdiscord", "ss", funcgroup,args);
    }

    ////////////////////
    if(dpp_funcfound == 0)
    {
        if(strlen(line) > 5)
        {
            dpp_error("Unknown element \"%s\".", line);
        }
    }
    return 1;
}

stock dpp_subprocess(const line[])
{
    dpp_process(line);
    return 1;
}