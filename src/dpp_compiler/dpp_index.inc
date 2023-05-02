/*
*
* D++ Scripting Language
*     Made for a SA:MP server
*
* Compiling System Entry point
*
* 
* - by: DEntisT, (c) 2022
*
*/

stock void:dpp_writecompileddata(const file[],const data[]) 
{
    new File:LogFile = fopen(file, io_append);

    fwrite(LogFile, data);

    fclose(LogFile);
}

stock dpp_compile(const script[])
{
    print("                                        ");
    print("|======================================|");
    print("                                        ");
    print("                   D++                  ");
    print("         Compiler is loading...         ");
    print("                                        ");
    printf("         Version: %i.%i.%i-R%i         ", DPP_VERSION_MAJOR,DPP_VERSION_MINOR,DPP_VERSION_PATCH,DPP_VERSION_RELEASE);
    print("                                        ");
    print("               By: DEntisT              ");
    print("                                        ");
    print("|======================================|");
    print("                                        ");
    print("                                        ");
    //dpp_print("Interpreter version %i.%i.%i-R%i - by: DEntisT",DPP_VERSION_MAJOR,DPP_VERSION_MINOR,DPP_VERSION_PATCH,DPP_VERSION_RELEASE);
    if(fexist("index.dppc")) fremove("index.dppc");
    dpp_print("Compiling \"%s\"...",script);
    print("                                        ");
    print("                                        ");
    new File:file = fopen(script, io_read), rlen;
    //new codelines[dpp_maxcodelines][1024];
    if(file)
    {
        while(rlen = fread(file, content))
        {
            for(new i; i < strlen(content); i++)
            {
                //if(content[i] == ';' && content[i+1] == ' ') strdel(content, i+1, i+2);
                if(content[i] == '\t') strdel(content, i, i+1);
                if(content[i] == '\n') content[i] = ';'; //strdel(content, i, i+1);
            }
            dpp_debug("content: '%s'", content);
            //dpp_parsecode(content, codelines);
            //dpp_debug("Executing:\n\n%s", content);
            dpp_writecompileddata("index.dppc", content);
        }
    }

    else if(!file)
    {
        dpp_error("Invalid file.",);
        return 1;
    }
    dpp_nullcomment();
    print("                                        ");
    print("                                        ");
    //dpp_print("Interpreter version %i.%i.%i-R%i - by: DEntisT",DPP_VERSION_MAJOR,DPP_VERSION_MINOR,DPP_VERSION_PATCH,DPP_VERSION_RELEASE);
    
    dpp_print("File \"%s\" compiled successfully.",script);
    print("                                        ");
    print("                                        ");
    dpp_compiled = 1;
    return 1;
}