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

stock dpp_process(line[])
{
    #if DPP_LOGPROCESSES == 1
    if(dpp_processfunc != dpp_lastvalueprcfunc)
    {
        dpp_print("dpp_processfunc was changed to %i",dpp_processfunc);
    }
    #endif
    dpp_lastvalueprcfunc = dpp_processfunc;
    if(dpp_option_allspc == 1 && dpp_compiling_pass == 3) for(new i; i < 100; i++)
    {
        dpp_deletespaces(line);
    }
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
        args[dpp_maxargsc][dpp_argcharsize], 
        funcgroup[3][1024],
        vargroup[2][256],
        args_const[dpp_maxargsc][dpp_argcharsize],
        structgroup[2][512],
        dirgroup[2][256];

    new 
        nativegroup[2][1024],
        arggroup[2][1024],
        funcgroup_form[3][1024],
        args_form[dpp_maxargsc][dpp_argcharsize],
        args_fconst[dpp_maxargsc][dpp_argcharsize];

    new extracode[3000];
    new line2[3000];
    new dpp_funcfound;
    
    strmid(line2, line, 0, strlen(line), strlen(line));
    dpp_checkforconditionals(line, line2, extracode, "->");
    dpp_checkforobjinit(line, line2, extracode, "<-");

    //console.println.log("Hello World")testvar;
    //  nativegroup[0]  console.println.log
    //  nativegroup[1]  "Hello World")testvar

    dpp_parseline(line,dirgroup,':');
    dpp_parseline(line,nativegroup, '(');

    dpp_parseline(line, args, ',');
    dpp_parseline(args[0], funcgroup, '.');
    dpp_parseline(args[1], vargroup, '=');

    dpp_parseline(nativegroup[0], funcgroup_form, '.');
    dpp_parseline(nativegroup[1], arggroup, ')');
    dpp_parseline(arggroup[0], args_form, ',');

    /*printf("NATIVEGROUP 0: '%s'", nativegroup[0]);
    printf("NATIVEGROUP 1: '%s'", nativegroup[1]);
    printf("ARGGROUP 0: '%s'", arggroup[0]);
    printf("ARGGROUP 1: '%s'", arggroup[1]);
    printf("funcgroup_form 0: '%s'", funcgroup_form[0]);
    printf("funcgroup_form 1: '%s'", funcgroup_form[1]);
    printf("funcgroup_form 2: '%s'", funcgroup_form[2]);
    printf("args_form 0: '%s'", args_form[0]);
    printf("args_form 1: '%s'", args_form[1]);
    printf("args_form 2: '%s'", args_form[2]);*/

    //console.println(func);

    for(new i; i < dpp_maxargsc; i++)
    {
        strmid(args_const[i], args[i],0,dpp_argcharsize,dpp_argcharsize);
    }

    /*for(new i = dpp_maxargsc-1; i != 0; i--)
    {
        strmid(args_form[i], args_form[i-1],0,dpp_argcharsize,dpp_argcharsize);
    }*/

    for(new i; i < dpp_maxargsc; i++)
    {
        strmid(args_fconst[i], args_form[i],0,dpp_argcharsize,dpp_argcharsize);
    }    

    if(dpp_compiling_pass == 1)
    {
        //dpp_compilerprint("Compiling the MAIN#%c-%ith sequence...", line[0], strlen(line));
        dpp_writecompileddata("index.dppc", line);
        return 1;
    }
    if(dpp_compiling_pass == 2)
    {
        if(!strcmp(dirgroup[0], "#include"))
        {
            /*for(new i; i < strlen(args[1]); i++)
            {
                if(args[1][i] == '\"') strdel(args[1], i, i+1);
            }*/
            new filename[64];
            /*for(new args1idx; args1idx < strlen(args[1]); args1idx ++)
            {
                if(args[1][args1idx] == ';') strdel(args[1], args1idx, args1idx+1);
                if(args[1][args1idx] == '\n') strdel(args[1], args1idx, args1idx+1);
            }*/
            format(filename, sizeof filename, "modules/%s.dpp", dirgroup[1]);
            if(fexist(filename))// return dpp_executefile(filename);
            {
                new File:file = fopen(filename, io_read), rlen;
                new codelines[dpp_maxcodelines][1024];
                if(file)
                {
                    while(rlen = fread(file, subcontent))
                    {
                        for(new i; i < strlen(subcontent); i++)
                        {
                            if(subcontent[i] == ';' && subcontent[i+1] == ' ') strdel(subcontent, i+1, i+2);
                            if(subcontent[i] == '\t') strdel(subcontent, i, i+1);
                            if(subcontent[i] == '\n') subcontent[i] = ';';
                        }
                        //dpp_compilerprint("Compiling the MDL#%c-%ith sequence...", subcontent[0], strlen(subcontent));
                        dpp_writecompileddata("index.dppc", subcontent);
                        /*dpp_parsecode(subcontent, codelines);
                        for(new i; i < dpp_maxcodelines; i++)
                        {
                            if(strlen(codelines[i]) < 4) continue;
                            //dpp_process(codelines[i]);
                            strcat(codelines[i], "\n");
                            for(new x; x < strlen(codelines[i]); x++)
                            {
                                if(codelines[i][x] == '\t') strdel(codelines[i], x, x+1);
                                if(codelines[i][x] == '\n') codelines[i][x] = ';';
                            }
                            dpp_compilerprint("Compiling the MDL#%c-%ith sequence...", codelines[i][0], strlen(codelines[i]));
                            dpp_writecompileddata("index.dppc", codelines[i]);
                        }*/
                    }
                }
            }
            else
            {
                dpp_error("Cannot read from module: \"%s\"", filename);
                return 1;
            }
            return 1;
        }
        //dpp_writecompileddata("index.dppc", line);
        return 1;
    }

    for(new i; i < 512; i++)
    {
        if(funcgroup[0][i] == '*')
        {
            dpp_parseline(funcgroup[0], structgroup, '*');
            break;
        }
    }

    //console.cout,"Hello World";

    //  funcgroup[0]    console
    //  funcgroup[1]    cout
    //  args[1]         "Hello World"

    //extern&struct*samp_command.StructName?arg1&arg2;

    //  structgroup[0]  extern&struct
    //  structgroup[1]  samp_command
    //  funcgroup[1]    StructName
    //  arguments       arg1&arg2

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

    if(dpp_strcmp(funcgroup[0], "<"))
    {
        dpp_workingclassid = dpp_lastclass;
        return 1;
    }

    if(dpp_strcmp(funcgroup[0], ">"))
    {
        dpp_workingclassid = dpp_invalidclass;
        return 1;
    }

    if(!strcmp(funcgroup[0], "}"))
    {
        if(dpp_event == dpp_event_form)
        {
            dpp_sysreturned = 0;
            dpp_currentfuncid = DPP_INVALID_FORM_ID;
            //dpp_processfunc = DPP_INVALID_FORM_ID;
            dpp_interpreter = 1;
        }
        if(dpp_event == dpp_event_task)
        {
            dpp_currenttaskid = DPP_INVALID_TASK_ID;
            dpp_taskinterpreter = 1;
        }
        return 1;
    }

    if(!strcmp(funcgroup[0], "{"))
    {
        if(dpp_event == dpp_event_form)
        {
            dpp_interpreter = 0;
            //dpp_processfunc = dpp_currentfuncid;
        }
        if(dpp_event == dpp_event_task)
        {
            dpp_taskinterpreter = 0;
        }
        return 1;
    }

    /*
    if(!strcmp(funcgroup[0], "inline"))
    {
        if(!strcmp(funcgroup[1],"end"))
        {
            dpp_currentinlineid = DPP_INVALID_FORM_ID;
            dpp_inlineinterpreter = 1;
            dpp_error("'dpp_inlineinterpreter' is updated to '%i'",dpp_inlineinterpreter);
            dpp_error("'dpp_currentinlineid' is updated to '%i'",dpp_currentinlineid);
        }
        if(!strcmp(funcgroup[1],"do"))
        {
            dpp_inlineinterpreter = 0;
            dpp_error("'dpp_inlineinterpreter' is updated to '%i'",dpp_inlineinterpreter);
        }
        return 1;
    }

    
    if(!strcmp(funcgroup[0], "task"))
    {
        if(!strcmp(funcgroup[1],"end"))
        {
            dpp_currenttaskid = DPP_INVALID_TASK_ID;
            dpp_taskinterpreter = 1;
        }
        if(!strcmp(funcgroup[1],"do"))
        {
            dpp_taskinterpreter = 0;
        }
        return 1;
    }

    if(!strcmp(funcgroup[0], "class"))
    {
        if(!strcmp(funcgroup[1],"end"))
        {
            dpp_workingclassid = dpp_invalidclass;
        }
        if(!strcmp(funcgroup[1],"do"))
        {
            dpp_workingclassid = dpp_lastclass;
        }
        return 1;
    }
    */

    if(dpp_interpreter == 0)
    {
        format(codeblockline, sizeof codeblockline, "%s;", line);
        dpp_debug("codeblockline:%s",codeblockline);
        dpp_debug("dpp_currentfuncid:%i",dpp_currentfuncid);
        strcat(dpp_funccodeblock[dpp_currentfuncid], codeblockline);
        return 1;
    }

    if(dpp_taskinterpreter == 0)
    {
        format(codeblockline, sizeof codeblockline, "%s;", line);
        dpp_debug("codeblockline:%s",codeblockline);
        dpp_debug("dpp_currenttaskid:%i",dpp_currenttaskid);
        strcat(dpp_taskcodeblock[dpp_currenttaskid], codeblockline);
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
        if(dpp_processfunc != DPP_INVALID_FORM_ID)
        {
            dpp_error("You can't create a form [\"%s\"] inside a form.",funcgroup[1]);
            return 1;
        }
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

        dpp_event = dpp_event_form;
        return 1;
    }
    if(!strcmp(funcgroup[0], "auto&form"))
    {
        if(dpp_processfunc != DPP_INVALID_FORM_ID)
        {
            dpp_error("You can't create a form [\"%s\"] inside a form.",funcgroup[1]);
            return 1;
        }
        new arguments[2][1024];
        dpp_parseline(funcgroup[1],arguments,'?');
        dpp_createfunc(arguments[0],arguments[1],1);

        dpp_event = dpp_event_form;
        return 1;
    }
    if(!strcmp(funcgroup[0], "hook&form"))
    {
        if(dpp_processfunc != DPP_INVALID_FORM_ID)
        {
            dpp_error("You can't create a form [\"%s\"] inside a form.",funcgroup[1]);
            return 1;
        }
        new arguments[2][1024];
        dpp_parseline(funcgroup[1],arguments,'?');
        dpp_createfunc(arguments[0],arguments[1],0,1);

        dpp_event = dpp_event_form;
        return 1;
    }
    if(!strcmp(funcgroup[0], "native&form"))
    {
        if(dpp_processfunc != DPP_INVALID_FORM_ID)
        {
            dpp_error("You can't create a form [\"%s\"] inside a form.",funcgroup[1]);
            return 1;
        }
        dpp_regnativeform(funcgroup[1]);
        return 1;
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            INLINE SYS
    ////
    ////
    ///////////////////////////////////////////////////////


    /*if(dpp_strcmp(funcgroup[0], "("))
    {
        dpp_inlineinterpreter = 0;
        return 1;
    }

    if(dpp_strcmp(funcgroup[0], ")"))
    {
        dpp_currentinlineid = DPP_INVALID_FORM_ID;
        dpp_inlineinterpreter = 1;
        return 1;
    }*/


    if(!strcmp(funcgroup[0], "inline&form"))
    {
        if(dpp_processfunc == DPP_INVALID_FORM_ID)
        {
            dpp_error("Unknown base form ID; unable to create an inline form.",);
            return 1;
        }
        CallLocalFunction("dpp_createinline", "si", funcgroup[1], dpp_processfunc);

        dpp_event = dpp_event_inline;
        return 1;
    }


    ///////////////////////////////////////////////////////
    ////
    ////
    ////            STRUCT SYS
    ////
    ////
    ///////////////////////////////////////////////////////


    if(!strcmp(structgroup[0], "extern&struct"))
    {
        if(!strcmp(structgroup[1], "samp_command"))
        {
            if(dpp_config[samp_comp] == 0)
            {
                dpp_error("Component \"samp\" is not imported.",);
                return 1;
            }
            if(dpp_processfunc != DPP_INVALID_FORM_ID)
            {
                dpp_error("You can't create a structured form [\"%s\"] inside a form.",funcgroup[1]);
                return 1;
            }
            new arguments[2][1024];
            dpp_parseline(funcgroup[1],arguments,'?');
            //dpp_error("samp_command struct created: \"%s\"",arguments[0]);
            dpp_createfunc(arguments[0],arguments[1], .struct = dpp_formstruct_sampcmd);

            dpp_event = dpp_event_form;
            return 1;
        }
        dpp_error("Unknown form structure type [\"%s\"].",structgroup[1]);
        return 1;
    }


    ///////////////////////////////////////////////////////
    ////
    ////
    ////            METHOD SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "form&method"))
    {
        if(dpp_processfunc != DPP_INVALID_FORM_ID)
        {
            dpp_error("You can't create a structured form [\"%s\"] inside a form.",funcgroup[1]);
            return 1;
        }
        new arguments[2][1024];
        dpp_parseline(funcgroup[1],arguments,'?');
        //dpp_error("samp_command struct created: \"%s\"",arguments[0]);
        dpp_createfunc(arguments[0],arguments[1], .method = 1);

        dpp_event = dpp_event_form;
        return 1;
    }

    CallLocalFunction("dpp_callmethod", "ss", funcgroup, args);

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            TASK SYS
    ////
    ////
    ///////////////////////////////////////////////////////



    if(!strcmp(funcgroup[0], "public&task"))
    {
        if(dpp_processfunc != DPP_INVALID_FORM_ID)
        {
            dpp_error("You can't create a task [\"%s\"] inside a form.",funcgroup[1]);
            return 1;
        }

        new arguments[2][1024];
        dpp_parseline(funcgroup[1],arguments,'#');
        dpp_createtask(arguments[0],strval(arguments[1]));

        dpp_event = dpp_event_task;
        return 1;
    }


    ///////////////////////////////////////////////////////
    ////
    ////
    ////            ARG REPLACEMENT SYS
    ////
    ////
    ///////////////////////////////////////////////////////


    dpp_argclasscheck(dirgroup[1]);
    dpp_argformargcheck(dirgroup[1]);

    for(new i; i < dpp_maxargsc; i++)
    {
        dpp_removeslashes(args[i]);
        dpp_argclasscheck(args[i]);
        dpp_argarraycheck(args[i]);
        dpp_argfunccheck(args[i]);
        dpp_argvarcheck(args[i]);
        dpp_argmathcheck(args[i]);
        dpp_argformargcheck(args[i]);
        dpp_argsystemval(args[i]);
        CallLocalFunction("dpp_arginstruct", "s", args[i]);

        dpp_formatarg(args[i]);
    }

    for(new i; i < dpp_maxargsc; i++)
    {
        dpp_argclasscheck(args_const[i]);
        dpp_argformargcheck(args_const[i]);
    }

    //////////////////////////////////////////
    for(new i; i < dpp_maxargsc; i++)
    {
        dpp_removeslashes(args_form[i]);
        dpp_argclasscheck(args_form[i]);
        dpp_argarraycheck(args_form[i]);
        dpp_argfunccheck(args_form[i]);
        dpp_argvarcheck(args_form[i]);
        dpp_argmathcheck(args_form[i]);
        dpp_argformargcheck(args_form[i]);
        dpp_argsystemval(args_form[i]);
        CallLocalFunction("dpp_arginstruct", "s", args_form[i]);

        dpp_formatarg(args_form[i]);
    }

    for(new i; i < dpp_maxargsc; i++)
    {
        dpp_argclasscheck(args_fconst[i]);
        dpp_argformargcheck(args_fconst[i]);
    }

    //////////////////////////////////////////

    for(new i; i < 2; i++)
    {
        if(i == 0)
        {
            dpp_argclasscheck(vargroup[i]);
            dpp_argformargcheck(vargroup[i]);
            i = 1;
        }

        dpp_removeslashes(vargroup[i]);
        dpp_argclasscheck(vargroup[i]);
        dpp_argarraycheck(vargroup[i]);
        dpp_argfunccheck(vargroup[i]);
        dpp_argvarcheck(vargroup[i]);
        dpp_argmathcheck(vargroup[i]);
        dpp_argformargcheck(vargroup[i]);
        dpp_argsystemval(vargroup[i]);
        CallLocalFunction("dpp_arginstruct", "s", vargroup[i]);

        dpp_formatarg(vargroup[i]);
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            RUNTIME DIRECTIVES
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(dirgroup[0], "#undef"))
    {
        dpp_deleteintconst(dirgroup[1]);
        dpp_deleteboolconst(dirgroup[1]);
        dpp_deletestrconst(dirgroup[1]);
        dpp_deleteiter(dirgroup[1]);
        dpp_deleteintvar(dirgroup[1]);
        dpp_deleteboolvar(dirgroup[1]);
        dpp_deletestrvar(dirgroup[1]);
        dpp_deletefunc(dirgroup[1]);
        return 1;
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

        dpp_event = dpp_event_class;
        return 1;
    }
    if(!strcmp(funcgroup[0], "hook&class"))
    {
        dpp_hookclass(funcgroup[1]);

        dpp_event = dpp_event_class;
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

        if(dpp_option_allspc == 1) for(new i; i < 100; i++)
        {
            dpp_deletespaces(line2);
        }
        if(dpp_option_allspc == 1) for(new i; i < 100; i++)
        {
            dpp_deletespaces(extracode);
        }

        dpp_parseline(line2, args, ',');
        dpp_parseline(args[0], funcgroup, '.');

        for(new i; i < 15; i++)
        {
            strmid(args_const[i], args[i],0,dpp_argcharsize,dpp_argcharsize);
        }
        
        for(new i; i < 15; i++)
        {
            if(dpp_option_allspc == 1) dpp_delexcspaces(args[i]);
            if(!strcmp(funcgroup[0], "const::define") || !strcmp(funcgroup[0], "const::undef") ||
                !strcmp(funcgroup[0], "var::define") || !strcmp(funcgroup[0], "var::undef") ||
                !strcmp(funcgroup[0], "var::set") || 
                (!strcmp(funcgroup[0], "system") && !strcmp(funcgroup[1], "arginit")) ||
                (!strcmp(funcgroup[0], "files") && !strcmp(funcgroup[1], "read")))
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
            dpp_argsystemval(args[i]);
            CallLocalFunction("dpp_arginstruct", "s", args[i]);

            dpp_formatarg(args[i]);
        }
        // IF CHECKS
        //if.equ,1,1->console.cout,"1 is 1";
        if(!strcmp(funcgroup[0], "if"))
        {
            dpp_skipelse = 0;
            if(!strcmp(funcgroup[1], "equ"))
            {
                if(!strcmp(args[1], args[2]))
                {
                    dpp_subexecute2(extracode);
                    dpp_skipelse = 1;
                }
                return 1;
            }

            if(!strcmp(funcgroup[1], "notequ"))
            {
                if(strcmp(args[1], args[2]))
                {
                    dpp_subexecute2(extracode);
                    dpp_skipelse = 1;
                }
                return 1;
            }

            if(!strcmp(funcgroup[1], "gt"))
            {
                if(strval(args[1]) > strval(args[2]))
                {
                    dpp_subexecute2(extracode);
                    dpp_skipelse = 1;
                }
                return 1;
            }

            if(!strcmp(funcgroup[1], "lt"))
            {
                if(strval(args[1]) < strval(args[2]))
                {
                    dpp_subexecute2(extracode);
                    dpp_skipelse = 1;
                }
                return 1;
            }

            if(!strcmp(funcgroup[1], "ge"))
            {
                if(strval(args[1]) >= strval(args[2]))
                {
                    dpp_subexecute2(extracode);
                    dpp_skipelse = 1;
                }
                return 1;
            }

            if(!strcmp(funcgroup[1], "le"))
            {
                if(strval(args[1]) <= strval(args[2]))
                {
                    dpp_subexecute2(extracode);
                    dpp_skipelse = 1;
                }
                return 1;
            }
            dpp_skipelse = 0;
            dpp_error("Unknown if-expression method : \"%s\"",funcgroup[1]);
        }
        if(!strcmp(funcgroup[0], "else"))
        {
            if(dpp_skipelse == 1)
            {
                return 1;
            }
            dpp_subexecute2(extracode);
            return 1;
        }
        // WHILE LOOPS
        //while.notequ,testvar,1->var::set.int,testvar,add?testvar:1&console.println,"{testvar}";
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
                        dpp_argsystemval(args[i]);
                        CallLocalFunction("dpp_arginstruct", "s", args[i]);

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
                        dpp_argsystemval(args[i]);
                        CallLocalFunction("dpp_arginstruct", "s", args[i]);

                        dpp_formatarg(args[i]);
                    }

                    //dpp_print("While loop backtrace\nconst arg 1 : %s\t\t| const arg 2 : %s\narg 1 : %s\t\t| arg 2 : %s",args_const[1],args_const[2],args[1],args[2]);
                }
                while(!dpp_strcmp(args[1], args[2]));
                return 1;
            }
            dpp_error("Unknown while-loop method : \"%s\"",funcgroup[1]);
        }
        //for loops
        if(!strcmp(funcgroup[0], "for"))
        {
            if(!strcmp(funcgroup[1], "int&var"))
            {
                new dpp_varid = -1;
                for(new i; i < dpp_maxvar; i++)
                {
                    if(!strcmp(args_const[1], dpp_vardata[i][var_name]))
                    {
                        if(dpp_vardata[i][var_valid] == 1)
                        {
                            dpp_varid = i;
                            break;
                        }
                    }
                }
                if(dpp_varid == -1)
                {
                    dpp_error("Unknown variable; can't loop.",);
                    return 1;
                }
                do
                {
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
                        dpp_argsystemval(args[i]);
                        CallLocalFunction("dpp_arginstruct", "s", args[i]);

                        dpp_formatarg(args[i]);
                    }

                    //dpp_error("Found a variable: '%s', supposed var: '%s'",dpp_vardata[dpp_varid][var_name],args_const[1]);
                    dpp_vardata[dpp_varid][integervalue]++;
                    dpp_subexecute2(extracode);
                }
                while(dpp_vardata[dpp_varid][integervalue] < strval(args[2]));
                return 1;
            }
            dpp_error("Unknown for-loop subject.",);
        }
        //foreach
        if(!strcmp(funcgroup[0], "foreach"))
        {
            if(!strcmp(funcgroup[1], "int&var"))
            {
                new dpp_varid = -1, dpp_iterid = -1;
                dpp_argclasscheck(args_const[1]);
                for(new i; i < dpp_maxvar; i++)
                {
                    if(!strcmp(args_const[1], dpp_vardata[i][var_name]))
                    {
                        if(dpp_vardata[i][var_valid] == 1)
                        {
                            dpp_varid = i;
                            break;
                        }
                    }
                }
                dpp_argclasscheck(args_const[2]);
                for(new i; i < dpp_maxiter; i++)
                {
                    if(!strcmp(args_const[2], dpp_itername[i]))
                    {
                        if(dpp_validiter[i] == 1)
                        {
                            dpp_iterid = i;
                            break;
                        }
                    }
                }
                if(dpp_iterid == -1 || dpp_varid == -1)
                {
                    dpp_error("Unknown variable or iterator; can't loop.",);
                    return 1;
                }

                //dpp_error("Found iterator '%s'; found variable '%s'",dpp_itername[dpp_iterid],dpp_vardata[dpp_varid][var_name]);
                
                for(new i; i < dpp_itersize[dpp_iterid]; i++)
                {
                    if(dpp_itervalues[dpp_iterid][i] != dpp_invaliditerval)
                    {
                        dpp_vardata[dpp_varid][integervalue] = dpp_itervalues[dpp_iterid][i];
                        dpp_subexecute2(extracode);
                    }
                }
                return 1;
            }
            dpp_error("Unknown foreach-loop subject.",);
        }
        //case
        if(!strcmp(funcgroup[0], "case"))
        {
            if(dpp_skipcase == 1)
            {
                return 1;
            }
            if(dpp_vardata[dpp_switchedvar][integervalue] == strval(args[1]))
            {
                dpp_skipcase = 1;
                dpp_subexecute2(extracode);
            }
        }
        //do
        if(!strcmp(funcgroup[0], "do"))
        {
            format(extracode, sizeof extracode, "%s;",extracode);
            strcat(dpp_inlinecodeblock[dpp_currentinlineid], extracode);
            //dpp_error("Added code '%s' to inline form [%i]",dpp_inlinecodeblock[dpp_currentinlineid],extracode);
            return 1;
        }
        return 1;
    } 

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            SWITCH SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "switch"))
    {
        new dpp_varid = -1;
        dpp_argclasscheck(args_const[1]);

        for(new i; i < dpp_maxvar; i++)
        {
            if(!strcmp(args_const[1], dpp_vardata[i][var_name]))
            {
                if(dpp_vardata[i][var_valid] == 1)
                {
                    dpp_varid = i;
                    break;
                }
            }
        }

        if(dpp_varid == -1)
        {
            dpp_error("Unknown variable; can't switch.",);
            return 1;
        }

        dpp_switchedvar = dpp_varid;

        return 1;
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            OBJECT SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "object"))
    {
        dpp_createobj(args[1]);
        return 1;
    }

    if(dpp_isobjinit == 1)
    {
        dpp_isobjinit = 0;

        if(dpp_option_allspc == 1) for(new i; i < 100; i++)
        {
            dpp_deletespaces(line2);
        }
        if(dpp_option_allspc == 1) for(new i; i < 100; i++)
        {
            dpp_deletespaces(extracode);
        }

        dpp_parseline(line2, args, ',');
        dpp_parseline(args[0], funcgroup, '.');

        for(new i; i < 15; i++)
        {
            strmid(args_const[i], args[i],0,dpp_argcharsize,dpp_argcharsize);
        }
        
        for(new i; i < 15; i++)
        {
            if(dpp_option_allspc == 1) dpp_delexcspaces(args[i]);
            if(!strcmp(funcgroup[0], "const::define") || !strcmp(funcgroup[0], "const::undef") ||
                !strcmp(funcgroup[0], "var::define") || !strcmp(funcgroup[0], "var::undef") ||
                !strcmp(funcgroup[0], "var::set") || 
                (!strcmp(funcgroup[0], "system") && !strcmp(funcgroup[1], "arginit")) ||
                (!strcmp(funcgroup[0], "files") && !strcmp(funcgroup[1], "read")))
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
            dpp_argsystemval(args[i]);
            CallLocalFunction("dpp_arginstruct", "s", args[i]);

            dpp_formatarg(args[i]);
        }

        // Check for object name

        dpp_argclasscheck(funcgroup[0]);

        dpp_objectid = -1;
        for(new i; i < dpp_maxobj; i++)
        {
            if(!strcmp(funcgroup[0], dpp_objname[i]))
            {
                if(dpp_validobj[i] == 1)
                {
                    dpp_objectid = i; 
                    break;
                }
            }
        }

        if(dpp_objectid == -1)
        {
            dpp_error("Unknown object: \"%s\"",funcgroup[0]);
            return 1;
        }

        dpp_subexecute2(extracode);
        return 1;
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            CONST SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    //const*new.int,myconst=1;
    if(!strcmp(structgroup[0], "const"))
    {
        if(!strcmp(structgroup[1], "new"))
        {
            if(!strcmp(funcgroup[1], "int"))
            {
                if(!dpp_isnumeric(vargroup[1]))
                {
                    dpp_error("Argument error; value must be an integer.",);
                    return 0;
                }

                dpp_createintconst(vargroup[0],strval(vargroup[1]));
                return 1;
            }
            if(!strcmp(funcgroup[1], "bool"))
            {
                if(strcmp(vargroup[1],"true") && strcmp(vargroup[1],"false"))
                {
                    dpp_error("Argument error; value must be either 'true' or 'false'.",);
                    return 0;
                }

                new dpp_boolval;


                if(!strcmp(vargroup[1], "false"))
                {
                    dpp_boolval = 0;
                }
                if(!strcmp(vargroup[1], "true"))
                {
                    dpp_boolval = 1;
                }

                dpp_createboolconst(vargroup[0],dpp_boolval);
                return 1;
            }
            if(!strcmp(funcgroup[1], "str"))
            {
                new mul2, str2[dpp_argcharsize];
                strmid(str2, vargroup[1], 0, dpp_argcharsize);
                for(new i; i < strlen(vargroup[1]); i++)
                {
                    if(vargroup[1][i] == '\"') mul2++, strdel(vargroup[1], i, i+1);
                }
                if(mul2 == 0)
                {
                    dpp_error("You need to use '\"' to start a string.",);
                    return 0;
                }
                if(mul2 != 2)
                {
                    dpp_error("Argument error; [%i] \"%s\"", mul2, vargroup[1]);
                    return 0;
                }

                dpp_createstrconst(vargroup[0],vargroup[1]);
                return 1;
            }
            
            else
            {
                dpp_error("Unknown symbol type \"%s\".", funcgroup[1]);
                return 0;
            }
        }
    }
    /*
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
    }*/

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            ITERATOR SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "iter::define"))
    {
        if(!dpp_isnumeric(args[2]))
        {
            dpp_error("Argument error; value must be an integer.",);
            return 0;
        }
        dpp_createiter(args[1],strval(args[2]));
        return 1;
    }

    if(!strcmp(funcgroup[0], "iter::add"))
    {
        if(!dpp_isnumeric(args[2]))
        {
            dpp_error("Argument error; value must be an integer.",);
            return 0;
        }
        dpp_addvalue(args[1],strval(args[2]));
        return 1;
    }

    if(!strcmp(funcgroup[0], "iter::remove"))
    {
        if(!dpp_isnumeric(args[2]))
        {
            dpp_error("Argument error; value must be an integer.",);
            return 0;
        }
        dpp_removevalue(args[1],strval(args[2]));
        return 1;
    }

    /*if(!strcmp(funcgroup[0], "iter::delete"))
    {
        dpp_deleteiter(args[1]);
        return 1;
    }*/


    ///////////////////////////////////////////////////////
    ////
    ////
    ////            VAR SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    //new.int,var=1;
    if(!strcmp(funcgroup[0], "new"))
    {
        if(!strcmp(funcgroup[1], "int"))
        {
            if(!dpp_isnumeric(vargroup[1]))
            {
                dpp_error("Argument error; value must be an integer.",);
                return 0;
            }

            dpp_createintvar(vargroup[0],strval(vargroup[1]));
            return 1;
        }
        if(!strcmp(funcgroup[1], "bool"))
        {
            if(strcmp(vargroup[1],"true") && strcmp(vargroup[1],"false"))
            {
                dpp_error("Argument error; value must be either 'true' or 'false'.",);
                return 0;
            }

            new dpp_boolval;



            if(!strcmp(vargroup[1], "false"))
            {
                dpp_boolval = 0;
            }
            if(!strcmp(vargroup[1], "true"))
            {
                dpp_boolval = 1;
            }

            dpp_createboolvar(vargroup[0],dpp_boolval);
            return 1;
        }
        if(!strcmp(funcgroup[1], "str"))
        {
            new mul2, str2[dpp_argcharsize];
            strmid(str2, vargroup[1], 0, dpp_argcharsize);
            for(new i; i < strlen(vargroup[1]); i++)
            {
                if(vargroup[1][i] == '\"') mul2++, strdel(vargroup[1], i, i+1);
            }
            if(mul2 == 0)
            {
                dpp_error("You need to use '\"' to start a string.",);
                return 0;
            }
            if(mul2 != 2)
            {
                dpp_error("Argument error; [%i] \"%s\"", mul2, vargroup[1]);
                return 0;
            }

            dpp_createstrvar(vargroup[0],vargroup[1]);
            return 1;
        }
        
        else
        {
            dpp_error("Unknown symbol type \"%s\".", funcgroup[1]);
            return 0;
        }
    }

    /*if(!strcmp(funcgroup[0], "undef"))
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
    }*/
    //set.int,var=1;
    if(!strcmp(funcgroup[0], "set"))
    {
        if(!strcmp(funcgroup[1], "int"))
        {
            if(!dpp_isnumeric(vargroup[1]))
            {
                dpp_error("Argument error; value must be an integer.",);
                return 0;
            }

            dpp_setintvar(vargroup[0],strval(vargroup[1]));
            return 1;
        }
        if(!strcmp(funcgroup[1], "bool"))
        {
            if(strcmp(vargroup[1],"true") && strcmp(vargroup[1],"false"))
            {
                dpp_error("Argument error; value must be either 'true' or 'false'.",);
                return 0;
            }

            new dpp_boolval;


            if(!strcmp(vargroup[1], "false"))
            {
                dpp_boolval = 0;
            }
            if(!strcmp(vargroup[1], "true"))
            {
                dpp_boolval = 1;
            }

            dpp_setboolvar(vargroup[0],dpp_boolval);
            return 1;
        }
        if(!strcmp(funcgroup[1], "str"))
        {
            new mul2, str2[dpp_argcharsize];
            strmid(str2, vargroup[1], 0, dpp_argcharsize);
            for(new i; i < strlen(vargroup[1]); i++)
            {
                if(vargroup[1][i] == '\"') mul2++, strdel(vargroup[1], i, i+1);
            }
            if(mul2 == 0)
            {
                dpp_error("You need to use '\"' to start a string.",);
                return 0;
            }
            if(mul2 != 2)
            {
                dpp_error("Argument error; [%i] \"%s\"", mul2, vargroup[1]);
                return 0;
            }

            dpp_setstrvar(vargroup[0],vargroup[1]);
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
        ////////////////////////////////////////////////
        //
        //                  DEBUG OPTION
        //
        ////////////////////////////////////////////////
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
        ////////////////////////////////////////////////
        //
        //                  warnings OPTION
        //
        ////////////////////////////////////////////////
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
        ////////////////////////////////////////////////
        //
        //                  HOOKING OPTION
        //
        ////////////////////////////////////////////////
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
        ////////////////////////////////////////////////
        //
        //                  ctrl char OPTION
        //
        ////////////////////////////////////////////////
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


        ////////////////////////////////////////////////
        //
        //                  allspc OPTION
        //
        ////////////////////////////////////////////////
        if(!strcmp(funcgroup[1], "allspc"))
        {
            dpp_argarraycheck(args[1]);
            if(!strcmp(args[1], "false"))
            {
                dpp_option_allspc = 0;
                dpp_print("Excessive space-tolerance disabled.");
                return 1;
            }
            if(!strcmp(args[1], "true"))
            {
                dpp_option_allspc = 1;
                dpp_print("Excessive space-tolerance enabled.");
                return 1;
            }

            if(!strcmp(args[1], "default"))
            {
                dpp_option_allspc = 0;
                dpp_print("Excessive space-tolerance disabled.");
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
    ////            COMPONENT SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "using"))
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
        if(!strcmp(funcgroup[1], "misc"))
        {
            dpp_config[misc_comp] = 1;
            return 1;
        }
        if(!strcmp(funcgroup[1], "data"))
        {
            dpp_config[data_comp] = 1;
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

    if(!strcmp(structgroup[0], "using"))
    {
        if(!strcmp(structgroup[1], "api"))
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
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            IMPORT SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(dirgroup[0], "#include"))
    {
        /*for(new i; i < strlen(args[1]); i++)
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
        }*/

        return 1;
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            USER/INLINE FUNC SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(dpp_funcfound == 0)
    {
        dpp_funcfound = CallLocalFunction("dpp_processuser", "sss", funcgroup_form,args_form,args_fconst);
    }

    CallLocalFunction("dpp_callmethod", "sss", funcgroup_form, args_form, args_fconst);

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            RETURN SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "return"))
    {
        if(dpp_processfunc == DPP_INVALID_FORM_ID)
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

            dpp_processfunc = DPP_INVALID_FORM_ID;
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

                dpp_processfunc = DPP_INVALID_FORM_ID;
                dpp_sysreturned = 1;
                return 1;
            }
            if(!strcmp(args[1], "false"))
            {
                dpp_returned[dpp_processfunc] = 1;
                dpp_returntype[dpp_processfunc] = dpp_rtn_type_bool;
                dpp_funcreturn_bool[dpp_processfunc] = 0;

                dpp_processfunc = DPP_INVALID_FORM_ID;
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

            dpp_processfunc = DPP_INVALID_FORM_ID;
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
    ////            YIELD RETURN SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(!strcmp(funcgroup[0], "yield&return"))
    {
        if(dpp_processfunc == DPP_INVALID_FORM_ID)
        {
            dpp_error("Expression \"yield&return\" can be only used inside a form code block.",);
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

            //dpp_returned[dpp_processfunc] = 1;
            dpp_returntype[dpp_processfunc] = dpp_rtn_type_int;
            dpp_funcreturn_int[dpp_processfunc] = int_return;

            return 1;
        }
        if(!strcmp(funcgroup[1], "bool"))
        {
            if(!strcmp(args[1], "true"))
            {
                //dpp_returned[dpp_processfunc] = 1;
                dpp_returntype[dpp_processfunc] = dpp_rtn_type_bool;
                dpp_funcreturn_bool[dpp_processfunc] = 1;

                return 1;
            }
            if(!strcmp(args[1], "false"))
            {
                //dpp_returned[dpp_processfunc] = 1;
                dpp_returntype[dpp_processfunc] = dpp_rtn_type_bool;
                dpp_funcreturn_bool[dpp_processfunc] = 0;

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

            //dpp_returned[dpp_processfunc] = 1;
            dpp_returntype[dpp_processfunc] = dpp_rtn_type_str;
            strmid(dpp_funcreturn_str[dpp_processfunc],args[1],0,
                dpp_argcharsize,dpp_argcharsize);

            dpp_debug("dpp_funcreturn_str[dpp_processfunc] : \"%s\"\nargs[1] : \"%s\"",dpp_funcreturn_str[dpp_processfunc],args[1]);

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
        dpp_funcfound = CallLocalFunction("dpp_processconsole", "ss", funcgroup_form,args_form);
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
        dpp_funcfound = CallLocalFunction("dpp_processsystem", "sss", funcgroup_form,args_form,args_fconst);
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
        dpp_funcfound = CallLocalFunction("dpp_processsamp", "ss", funcgroup_form,args_form);
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
        dpp_funcfound = CallLocalFunction("dpp_processmath", "ss", funcgroup_form,args_form);
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
        dpp_funcfound = CallLocalFunction("dpp_processfiles", "sss", funcgroup_form,args_form,args_fconst);
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            MISC comp FUNC SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(dpp_funcfound == 0)
    {
        dpp_funcfound = CallLocalFunction("dpp_processmisc", "sss", funcgroup_form,args_form,args_fconst);
    }

    ///////////////////////////////////////////////////////
    ////
    ////
    ////            DATA comp FUNC SYS
    ////
    ////
    ///////////////////////////////////////////////////////

    if(dpp_funcfound == 0)
    {
        dpp_funcfound = CallLocalFunction("dpp_processdata", "sss", funcgroup_form,args_form,args_fconst);
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
        dpp_funcfound = CallLocalFunction("dpp_processdiscord", "ss", funcgroup_form,args_form);
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

stock dpp_subprocess(line[])
{
    for(new i; i < 100; i++)
        dpp_deletespaces(line);
    
    dpp_process(line);
    return 1;
}

dpp_processuser(funcgroup[][],args[][],args_const[][]);
public dpp_processuser(funcgroup[][],args[][],args_const[][])
{
    if(!strcmp(funcgroup[0], "user"))
    {
        dpp_argclasscheck(funcgroup[1]);
        for(new i; i < dpp_maxfuncs; i++)
        {
            if(!strcmp(dpp_funcname[i], funcgroup[1]))
            {
                if(dpp_hookform[i] == 0)
                {
                    for(new argid; argid < dpp_maxformargs; argid++)
                    {
                        strmid(dpp_args[i][argid][dpp_argvalue],
                            args[argid],
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
                                            args[argid],
                                            0,
                                            dpp_argcharsize,
                                            dpp_argcharsize);
                                    }
                                    dpp_processfunc = hookfuncid;
                                    dpp_subexecute(dpp_funccodeblock[hookfuncid], hookfuncid);
                                    dpp_debug("dpp_funccodeblock[hookfuncid]:%s",dpp_funccodeblock[hookfuncid]);
                                }
                            }
                        }
                    }
                    dpp_clearformstack(dpp_processfunc); dpp_processfunc = DPP_INVALID_FORM_ID;
                    return 1;
                }
            }
        }
        if(dpp_processfunc == DPP_INVALID_FORM_ID)
        {
            dpp_error("Inline forms are meant to be used inside forms.",);
            return 1;
        }
        for(new i; i < dpp_maxinline; i++)
        {
            if(!strcmp(dpp_inlinename[i], funcgroup[1]))
            {
                if(dpp_validinline[i] == 1)
                {
                    //dpp_error("Inline: '%s' | Code: '%s'",funcgroup[1],dpp_inlinecodeblock[i]);
                    dpp_subexecute(dpp_inlinecodeblock[i]);
                    return 1;
                }
            }
        }
        dpp_error("Form \"%s\" isn't registered.", funcgroup[1]);
        return 0;
    }
    return 0;
}