/*
 *
 * D++ Scripting Language
 *     Made for a SA:MP server
 *
 * Functions/header
 *
 * 
 * - by: DEntisT, (c) 2022
 *
 */

#define dpp_header 1

#define dpp_info dpp_print
#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#define dpp_execheader%0(%1) print("|====================| "%1" |====================|")
#define dpp_comment%0(%1) print("|==============================================|")
#define dpp_nullcomment%1(%1) print("                                               ")
#define dpp_print%0(%1) printf(">> D++ | INFO: "%1)
#if DPP_DEBUG == 1
#define dpp_debug%0(%1) if(dpp_option_debug==1)printf(">> D++ | DEBUG: "%1)
#elseif DPP_DEBUG == 0
#define dpp_debug%0(%1)%2;
#endif

new
    dpp_error_str[1024];

#define __line,) __line)


#define dpp_error%0(%1,%2) format(dpp_error_str,sizeof dpp_error_str,">> D++ | ERROR (dpp.amx @ %s:%i): "%1,__file,__line,%2)&& \
    print(dpp_error_str)&&dpp_incerrcnt()
 //printf(">> D++ | ERROR (dpp.amx @ %s:%i): %s",__file,__line,%1)
#define dpp_warning%0(%1) if(dpp_option_warnings==1)dpp_incwarncnt()&&printf(">> D++ | WARNING: "%1)

stock dpp_incerrcnt()
{
    dpp_errorcount = dpp_errorcount+1;
    return 1;
}

stock dpp_incwarncnt()
{
    dpp_warningcount = dpp_warningcount+1;
    return 1;
}

stock dpp_parsecode(const code[], destln[][])
{
    new 
        i, 
        start,
        index,
        len;

    // Lets assume code = "decl::end;"

    while(i <= strlen(code)) // do this down there while 'i' is smaller than length of "decl::end;"
    {
        /*if(strcmp(code, "{")) // if at certain point i reaches the ';' char, or it reaches the end,then:
        {
            len = strmid(destln[index], "{", start, i, 128); // store "decl::end" without a ';' into destln 
            destln[index][len] = 0; // clear the last char
            start = i+1; // set start to be for 1 bigger
            index++; // set an index to be for  1 bigger
        }
        if(strcmp(code, "}")) // if at certain point i reaches the ';' char, or it reaches the end,then:
        {
            len = strmid(destln[index], "}", start, i, 128); // store "decl::end" without a ';' into destln 
            destln[index][len] = 0; // clear the last char
            start = i+1; // set start to be for 1 bigger
            index++; // set an index to be for  1 bigger
        }*/

        if(code[i] == ';' || i == strlen(code)) // if at certain point i reaches the ';' char, or it reaches the end,then:
        {
            len = strmid(destln[index], code, start, i, 128); // store "decl::end" without a ';' into destln 
            destln[index][len] = 0; // clear the last char
            start = i+1; // set start to be for 1 bigger
            index++; // set an index to be for  1 bigger
        }
        i++;
        
        if(strlen(code) != 0)
        {
            dpp_debug("Parsecode backtrace:\n\tcode: '%s'\n\ti: %i\n\tstart: %i\n\tindex: %i\n\tlen: %i\n\tdestln[%i]: '%s'\n\tlen (destln[%i]): %i",code,i,start,index,len,index,destln[index],index,strlen(destln[index]));
        }
    }
    return 1;
}

stock dpp_parseline(const code[], destln[][], delimiter)
{
    new 
        i, 
        start,
        index,
        len;

    while(i <= strlen(code))
    {
        if(code[i] == delimiter || i == strlen(code))
        {
            len = strmid(destln[index], code, start, i, 128);
            destln[index][len] = 0;
            start = i+1;
            index++;
        }
        i++;
    }
    return 1;
}

stock dpp_checkforifexpression(const code[], dest1[], dest2[], const delimiter[])
{
    new
        delimiter_start,
        delimiter_end;
    
    for(new i; i < strlen(code); i++)
    {
        if(code[i] == delimiter[0] && code[i+1] == delimiter[1])
        {
            dpp_isifexp = 1;
            delimiter_start = i;
            delimiter_end = i+1;
            strmid(dest1, code, 0, delimiter_start, 3000);
            strmid(dest2, code, delimiter_end+1, strlen(code), 3000);

            // strmid(dest[], const source[], start, end, maxlength=sizeof dest)

            dpp_debug("Code : \"%s\" was split into destln1 : \"%s\" and destln2 : \"%s\"",code,dest1,dest2);
            return 1;
        }
    }
    return 1;
}

stock dpp_extract(const src[], dest[], startchar, endchar)
{
    new
        start,
        end;

    for(new i; i < strlen(src); i++)
    {
        if(src[i] == startchar) start = i;
        if(src[i] == endchar) end = i;
    }

    strmid(dest, src, start, end, strlen(src));
    dpp_debug("Extracted : \"%s\"",dest);
    return 1;
}

stock dpp_createfunc(funcname[], autoform = 0, hookform = 0)
{
    new alreadyexists;
    for(new i; i < dpp_maxfuncs; i++)
    {
        if(!strcmp(dpp_funcname[i], funcname))
        {
            if(dpp_validfunc[i] == 1) alreadyexists = 1;
        }
    }   
    for(new i; i < dpp_maxfuncs; i++)
    {
        if(dpp_validfunc[i] == 0)
        {
            if(alreadyexists == 1 && hookform == 0)
            {
                dpp_error("Form \"%s\" already exists.",funcname);
                return 1;
            }
            if(hookform == 1)
            {
                dpp_hookform[i] = 1;
            }
            if(autoform == 1)
            {
                dpp_autoform[i] = 1;
            }
            dpp_currentfuncid = i;
            dpp_validfunc[i] = 1;

            if(dpp_workingclassid != 0)
            {
                new newvalue[dpp_argcharsize];
                format(newvalue,sizeof(newvalue),"DPPCf@%s_%s",dpp_classname[dpp_workingclassid],funcname);
                strmid(funcname, newvalue, 0, dpp_argcharsize,dpp_argcharsize);
            }

            strmid(dpp_funcname[i], funcname, 0, 64);
            dpp_debug("funcgroup[1]:%s",funcname);
            dpp_debug("dpp_funcname[i]:%s",dpp_funcname[i]);
            dpp_debug("dpp_currentfuncid:%i",dpp_currentfuncid);
            return 1;
        }
    }
    return 1;
}

new content[16000];

stock dpp_execute(const script[])
{
    print("                                        ");
    print("|======================================|");
    print("                                        ");
    print("                   D++                  ");
    print("         Interpreter is loading...      ");
    print("                                        ");
    printf("        Version: %i.%i.%i-R%i          ", DPP_VERSION_MAJOR,DPP_VERSION_MINOR,DPP_VERSION_PATCH,DPP_VERSION_RELEASE);
    print("                                        ");
    print("               By: DEntisT              ");
    print("                                        ");
    print("|======================================|");
    print("                                        ");
    print("                                        ");
    //dpp_print("Interpreter version %i.%i.%i-R%i - by: DEntisT",DPP_VERSION_MAJOR,DPP_VERSION_MINOR,DPP_VERSION_PATCH,DPP_VERSION_RELEASE);
    #if DPP_DEBUG == 1
    dpp_print("Debug component loaded...");
    #endif
    dpp_print("Executing the entry script...");
    dpp_nullcomment();
    dpp_execheader("index.dpp");
    dpp_nullcomment();

    new File:file = fopen(script, io_read), rlen;
    new codelines[1024][1024];
    if(file)
    {
        while(rlen = fread(file, content))
        {
            for(new i; i < strlen(content); i++)
            {
                if(content[i] == ';' && content[i+1] == ' ') strdel(content, i+1, i+2);
                if(content[i] == '\t') strdel(content, i, i+1);
                if(content[i] == '\n') strdel(content, i, i+1);
            }
            dpp_debug("content: '%s'", content);
            dpp_parsecode(content, codelines);
            //dpp_debug("Executing:\n\n%s", content);
            for(new i; i < 1024; i++)
            {
                if(!isnull(codelines[i])) dpp_debug("codelines[%i]: '%s'",i, codelines[i]);
                if(dpp_terminated == 1)
                {
                    break;
                }
                dpp_process(codelines[i]);
            }
        }
        CallLocalFunction("DPP_ENTRYPOINT", "");
    }

    else if(!file)
    {
        dpp_error("Invalid file.",);
    }
    dpp_nullcomment();
    dpp_comment();
    dpp_nullcomment();
    dpp_print("The interpreter reached the EOS point.");
    dpp_print("Process finished with %i errors and %i warnings.", dpp_errorcount,dpp_warningcount);
    return 1;
}

new subcontent[16000];

stock dpp_executefile(const script[])
{
    new File:file = fopen(script, io_read), rlen;
    new codelines[1024][1024];
    if(file)
    {
        while(rlen = fread(file, subcontent))
        {
            for(new i; i < strlen(subcontent); i++)
            {
                if(subcontent[i] == ';' && subcontent[i+1] == ' ') strdel(subcontent, i+1, i+2);
                if(subcontent[i] == '\t') strdel(subcontent, i, i+1);
                if(subcontent[i] == '\n') strdel(subcontent, i, i+1);
            }
            dpp_parsecode(subcontent, codelines);
            for(new i; i < 1024; i++)
            {
                dpp_process(codelines[i]);
            }
        }
    }
    else if(!file)
    {
        dpp_error("Invalid file.",);
    }
    return 1;
}

stock dpp_subexecute(const code[], funcid)
{
    #pragma unused funcid
    //if(dpp_returned[funcid] == 0) return 1;
    new codelines[1024][1024];

    dpp_parsecode(code, codelines);
    //dpp_debug("Executing:\n\n%s", code);
    for(new i; i < 1024; i++)
    {
        dpp_subprocess(codelines[i]);
    }
    return 1;
}

stock dpp_subexecute2(const code[])
{
    new codelines[1024][1024];

    dpp_parsecode(code, codelines);
    //dpp_debug("Executing:\n\n%s", code);
    for(new i; i < 1024; i++)
    {
        dpp_subprocess(codelines[i]);
    }
    return 1;
}


///////////////FUNC CALLING/////////////////////
stock dpp_argfunccheck(arg[])
{
    new newvalue[dpp_argcharsize];
    for(new i; i < dpp_maxfuncs; i++)
    {
        if(!strcmp(dpp_funcname[i], arg))
        {
            if(dpp_validfunc[i] == 1)
            {
                dpp_returned[i] = 0;
                dpp_processfunc = i;
                dpp_subexecute(dpp_funccodeblock[i],i);
                dpp_debug("dpp_funccodeblock[i]:%s",dpp_funccodeblock[999]);

                /////////////////////////////////////

                if(dpp_returntype[i] == dpp_rtn_type_int)
                {
                    format(newvalue, dpp_argcharsize, "%i", 
                        dpp_funcreturn_int[i]);
                }
                if(dpp_returntype[i] == dpp_rtn_type_bool)
                {
                    if(dpp_funcreturn_bool[i] == 1)
                    {
                        strmid(arg, "true", 0, dpp_argcharsize, dpp_argcharsize);
                    }
                    if(dpp_funcreturn_bool[i] == 0)
                    {
                        strmid(arg, "false", 0, dpp_argcharsize, dpp_argcharsize);
                    }
                }
                if(dpp_returntype[i] == dpp_rtn_type_str)
                {
                    format(newvalue, dpp_argcharsize, "\"%s\"", 
                        dpp_funcreturn_str[i]);
                }
                
                if(dpp_returntype[i] != dpp_rtn_type_bool)
                {
                    strmid(arg, newvalue, 0, dpp_argcharsize, dpp_argcharsize);
                }
                return 1;
            }
        }
    }
    return 1;
}

// system autoforms

DPP_ENTRYPOINT();
public DPP_ENTRYPOINT()
{
    if(dpp_config[system_comp] == 0)
    {
        return 1;
    }
    
    for(new i; i < dpp_maxfuncs; i++)
    {
        if(!strcmp(dpp_funcname[i], "main"))
        {
            if(dpp_autoform[i] == 0) return 1;
            if(dpp_hookform[i] == 0)
            {
                dpp_processfunc = i;
                dpp_subexecute(dpp_funccodeblock[i],i);
                dpp_debug("dpp_funccodeblock[i]:%s",dpp_funccodeblock[999]);
                dpp_debug("\"main\" called.");

                if(dpp_option_hooking == 1)
                {
                    for(new hookfuncid; hookfuncid < dpp_maxfuncs; hookfuncid++)
                    {
                        if(!strcmp(dpp_funcname[hookfuncid], "main"))
                        {
                            if(dpp_hookform[hookfuncid] == 1)
                            {
                                dpp_returned[hookfuncid] = 0;
                                dpp_processfunc = hookfuncid;
                                dpp_subexecute(dpp_funccodeblock[hookfuncid],hookfuncid);
                                dpp_debug("dpp_funccodeblock[hookfuncid]:%s",dpp_funccodeblock[999]);
                            }
                        }
                    }
                }
            }
            return 1;
        }
    }

    return 1;
}