/*
*
* D++ Scripting Language
*     Made for a SA:MP server
*
* Entry point
*
* 
* - by: DEntisT, (c) 2022
*
*/

#pragma dynamic 21575000000000
#pragma warning disable 204
#pragma warning disable 211
#pragma option -;+

#define dpp_invalidclass 100
#define DPP_VERSION_MAJOR 5
#define DPP_VERSION_MINOR 0
#define DPP_VERSION_PATCH 0
#define DPP_VERSION_RELEASE 1
#define DPP_INVALID_INLINE_ID 0
#define DPP_INVALID_FORM_ID 0

#define DPP_DEBUG 1
#define DPP_BRACES 0

#define dpp_maxcodelines 2048
#define dpp_maxformatlen 2048

#define dpp_maxformargs 10

#define dpp_maxconst 100
#define dpp_maxfuncs 100
#define dpp_maxinline 100
#define dpp_maxvar 100
#define dpp_maxclass 100

#define dpp_argcharsize 100

#define dpp_const_type_int 1
#define dpp_const_type_bool 2
#define dpp_const_type_str 3

#define dpp_var_type_int 1
#define dpp_var_type_bool 2
#define dpp_var_type_str 3

#define dpp_rtn_type_int 1
#define dpp_rtn_type_bool 2
#define dpp_rtn_type_str 3

#define dpp_maxnatives 100

new subcontent[16000];
new content[16000];

// REQUIRED.
#include <open.mp>

//THIRD PARTY API
#include "dpp_natives/dpp_dcc.inc"

enum dpp_enumset
{
    console_comp,
    system_comp,
    samp_comp,
    math_comp,
    files_comp
};

new dpp_config[dpp_enumset];

enum dpp_enumset2
{
    discord
};

new dpp_apis[dpp_enumset2];

//const
enum __dpp_const_val
{
    const_valid,
    const_name[64],
    const_type,
    integervalue,
    /*bool:*/boolvalue,
    Float:floatvalue,
    stringvalue[256]
}
new dpp_constdata[dpp_maxconst][__dpp_const_val];

//vars
enum __dpp_var_val
{
    var_valid,
    var_name[64],
    var_type,
    integervalue,
    /*bool:*/boolvalue,
    Float:floatvalue,
    stringvalue[256]
}

new dpp_vardata[dpp_maxvar][__dpp_var_val];

//inline
new dpp_inlineinterpreter = 1;
new dpp_currentinlineid = DPP_INVALID_INLINE_ID;
new dpp_validinline[dpp_maxinline];
new dpp_inlinebaseform[dpp_maxinline];
new dpp_inlinename[dpp_maxinline][64];
new dpp_inlinecodeblock[dpp_maxinline][1024];


//bunch of crap
new dpp_currentfuncid = DPP_INVALID_FORM_ID;
new dpp_validfunc[dpp_maxfuncs];
new dpp_funcname[dpp_maxfuncs][64];
new dpp_funccodeblock[dpp_maxfuncs][1024];
new dpp_autoform[dpp_maxfuncs];
new dpp_hookform[dpp_maxfuncs];
enum __dpp_argcache
{
    dpp_argname[32],
    dpp_argvalue[1024]
}
new dpp_args[dpp_maxfuncs][dpp_maxformargs][__dpp_argcache];

new dpp_validnativef[dpp_maxnatives];
new dpp_nativeformname[dpp_maxnatives][64];

new dpp_validclass[dpp_maxclass];
new dpp_classname[dpp_maxclass][64];
new dpp_workingclassid = dpp_invalidclass;

new dpp_funcreturn_int[dpp_maxfuncs];
new dpp_funcreturn_bool[dpp_maxfuncs];
new dpp_funcreturn_str[dpp_maxfuncs][1024];

new dpp_returned[dpp_maxfuncs];
new dpp_returntype[dpp_maxfuncs];

new dpp_processfunc = DPP_INVALID_FORM_ID;
new dpp_isconditional = 0;

new dpp_interpreter = 1;

new File:dpp_filehandle;
new dpp_fhandleused = 0;

// project config

new dpp_projname[128];
new dpp_stackoutput = 0;

// process cache

new dpp_terminated = 0;
new dpp_sysreturned = 0;

new dpp_warningcount = 0;
new dpp_errorcount = 0;

//OPTIONS

new dpp_option_debug = 0;
new dpp_option_warnings = 1;
new dpp_option_hooking = 1;
new dpp_option_escapechar = '\\';
new dpp_option_allspc = 0;

// data
new dpp_compiling_pass = 1;
new dpp_compiled = 0;
new dpp_lastclass;

//includes
#include "dpp_modules/dpp_header.inc"
#include "dpp_modules/dpp_proj.inc"
#include "dpp_modules/dpp_utils.inc"
#include "dpp_modules/dpp_const.inc"
#include "dpp_modules/dpp_vars.inc"
#include "dpp_modules/dpp_mathimpl.inc"
#include "dpp_modules/dpp_class.inc"
#include "dpp_modules/dpp_inline.inc"
#include "dpp_modules/dpp_interpreter.inc"

//compiler sys
#include "dpp_compiler/dpp_index.inc"

// component impl
#include "dpp_components/dpp_system.inc"
#include "dpp_components/dpp_console.inc"
#include "dpp_components/dpp_samp.inc"
#include "dpp_components/dpp_math.inc"
#include "dpp_components/dpp_files.inc"

//api impl
#include "dpp_thirdpartyapi/dpp_discord.inc"

main()
{
    strmid(dpp_projname,"Unnamed project",0,128,128);
    dpp_nullcomment();
    dpp_nullcomment();
    dpp_compile("index.dpp");
    main_again();
    return 1;   
}

stock main_again()
{
    if(dpp_compiled == 1)
    {
        dpp_execute("index.dppc");
    }
    dpp_nullcomment();
    dpp_nullcomment();
    dpp_comment();
    dpp_print("The SA:MP/open.mp script will continue running in the background.");
    dpp_comment();
    dpp_nullcomment();
    dpp_nullcomment();
    CallLocalFunction("DPP_GAMEMODEINIT", "");
    CallLocalFunction("DPP_discord_init", "");
    if(dpp_stackoutput == 1)
    {
        CallLocalFunction("dpp_dostackoutput", "");
    }
    return 1;
}

dpp_dostackoutput();
public dpp_dostackoutput()
{
    new stackfile[512],argfile[256];
    if(fexist("stackoutput.dpplog")) fremove("stackoutput.dpplog");
    dpp_nullcomment();
    dpp_comment();
    dpp_print("Loading the stack...");
    dpp_print("Loading the forms stack...");
    dpp_comment();
    dpp_savelog("stackoutput.dpplog","===============================================================");
    dpp_savelog("stackoutput.dpplog","FORMS");
    dpp_savelog("stackoutput.dpplog","===============================================================");
    for(new i; i < dpp_maxfuncs; i++)
    {
        format(stackfile,sizeof stackfile,"ID : %i | VALID : %i | NAME: \"%s\"\n\n",
            i,
            dpp_validfunc[i],
            dpp_funcname[i]);
        for(new argid; argid < dpp_maxformargs; argid++)
        {
            format(argfile, sizeof argfile, "\n\nARG[%i] NAME : \"%s\" | ARG[%i] VALUE : \"%s\"",
                argid,dpp_args[i][argid][dpp_argname],
                argid,dpp_args[i][argid][dpp_argvalue]);
            strcat(stackfile, argfile);
        }
        dpp_savelog("stackoutput.dpplog",stackfile);
    }
    dpp_comment();
    dpp_print("Loading the const stack...");
    dpp_comment();
    dpp_savelog("stackoutput.dpplog","===============================================================");
    dpp_savelog("stackoutput.dpplog","CONSTANTS");
    dpp_savelog("stackoutput.dpplog","===============================================================");
    for(new i; i < dpp_maxconst; i++)
    {
        format(stackfile,sizeof stackfile,"ID : %i | VALID : %i | NAME: \"%s\"",
            i,
            dpp_constdata[i][const_valid],
            dpp_constdata[i][const_name]);
        dpp_savelog("stackoutput.dpplog",stackfile);
    }
    dpp_comment();
    dpp_print("Loading the vars stack...");
    dpp_comment();
    dpp_savelog("stackoutput.dpplog","===============================================================");
    dpp_savelog("stackoutput.dpplog","VARS");
    dpp_savelog("stackoutput.dpplog","===============================================================");
    for(new i; i < dpp_maxvar; i++)
    {
        format(stackfile,sizeof stackfile,"ID : %i | VALID : %i | NAME: \"%s\"",
            i,
            dpp_vardata[i][var_valid],
            dpp_vardata[i][var_name]);
        dpp_savelog("stackoutput.dpplog",stackfile);
    }
    dpp_comment();
    dpp_print("Loading the class stack...");
    dpp_comment();
    dpp_savelog("stackoutput.dpplog","===============================================================");
    dpp_savelog("stackoutput.dpplog","CLASSES");
    dpp_savelog("stackoutput.dpplog","===============================================================");
    for(new i; i < dpp_maxclass; i++)
    {
        format(stackfile,sizeof stackfile,"ID : %i | VALID : %i | NAME: \"%s\"",
            i,
            dpp_validclass[i],
            dpp_classname[i]);
        dpp_savelog("stackoutput.dpplog",stackfile);
    }

    return 1;
}

DPP_ProcessCode(line[]); public DPP_ProcessCode(line[])
{
    dpp_process(line);
    return 1;
}