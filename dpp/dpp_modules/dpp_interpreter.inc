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

/*
import::package.console;
using::console.cout("Hello World")
decl::func.myfunc;
decl::begin;
	using::console.print,"myfunc called.";
decl::end;
*/

stock dpp_process(const line[])
{
	new codeblockline[1024];
	new args[10][100], funcgroup[2][20];
	dpp_parseline(line, args, ',');
	dpp_parseline(args[0], funcgroup, '.');

	if(!strcmp(funcgroup[0], "decl::func"))
	{
		for(new i; i < dpp_maxfuncs; i++)
		{
			if(dpp_validfunc[i] == 0)
			{
				dpp_currentfuncid = i;
				dpp_validfunc[i] = 1;
				strins(dpp_funcname[i], funcgroup[1], 0, 64);
				dpp_debug("funcgroup[1]:%s",funcgroup[1]);
				dpp_debug("dpp_funcname[i]:%s",dpp_funcname[i]);
				dpp_debug("dpp_currentfuncid:%i",dpp_currentfuncid);
				return 1;
			}
		}
		return 1;
	}
	if(!strcmp(line, "decl::begin"))
	{
		dpp_interpreter = 0;
		return 1;
	}
	if(!strcmp(line, "decl::end"))
	{
		dpp_interpreter = 1;
		return 1;
	}
	if(dpp_interpreter == 0)
	{
		format(codeblockline, sizeof codeblockline, "%s;", line);
		dpp_debug("codeblockline:%s",codeblockline);
		dpp_debug("dpp_currentfuncid:%i",dpp_currentfuncid);
		strcat(dpp_funccodeblock[dpp_currentfuncid], codeblockline);
		return 1;
	}

	if(!strcmp(funcgroup[0], "import::package"))
	{
		if(!strcmp(funcgroup[1], "console"))
		{
			dpp_config[console_pkg] = 1;
			return 1;
		}
		if(!strcmp(funcgroup[1], "system"))
		{
			dpp_config[system_pkg] = 1;
			return 1;
		}
		else
		{
			dpp_error("Unknown package \"%s\".", funcgroup[1]);
			return 0;
		}
	}
	if(!strcmp(funcgroup[0], "import::file"))
	{
		for(new i; i < strlen(args[1]); i++)
		{
			if(args[1][i] == '\"') strdel(args[1], i, i+1);
		}
		new filename[64];
		format(filename, sizeof filename, "%s.dpp", args[1]);
		if(fexist(filename)) dpp_executefile(filename);
		else
		{
			dpp_error("Cannot read from file: \"%s\"", filename);
			return 0;
		}
	}
	if(!strcmp(funcgroup[0], "using::user"))
	{
		for(new i; i < dpp_maxfuncs; i++)
		{
			if(!strcmp(dpp_funcname[i], funcgroup[1]))
			{
				dpp_subexecute(dpp_funccodeblock[i]);
				dpp_debug("dpp_funccodeblock[i]:%s",dpp_funccodeblock[999]);
				return 1;
			}
		}
		dpp_error("Function \"%s\" isn't registered.", funcgroup[1]);
		return 1;
	}
	if(!strcmp(funcgroup[0], "using::console"))
	{
		if(dpp_config[console_pkg] == 0)
		{
			dpp_error("Package \"console\" is not imported.");
			return 1;
		}
		// If the function used it "print"
		if(!strcmp(funcgroup[1], "cout"))
		{
			new mul, str[100];
			strmid(str, args[1], 0, 100);
			for(new i; i < strlen(args[1]); i++)
			{
				if(args[1][i] == '\"') mul++, strdel(args[1], i, i+1);
			}
			if(mul == 0)
			{
				dpp_error("You need to use '\"' to start a string.");
				return 0;
			}
			if(mul != 2)
			{
				dpp_error("Argument error.");
				return 0;
			}

			//dpp_debug("Line \"%s\" successfully executed.", line);
			print(args[1]);
			return 1;
		}
		else
		{
			dpp_error("Unknown function in the package \"console\".");
			return 0;
		}
	}
	if(!strcmp(funcgroup[0], "using::system"))
	{
		if(dpp_config[system_pkg] == 0)
		{
			dpp_error("Package \"system\" is not imported.");
			return 1;
		}
		// If the function used it "print"
		if(!strcmp(funcgroup[1], "rem"))
		{
			new mul, str[100];
			strmid(str, args[1], 0, 100);
			for(new i; i < strlen(args[1]); i++)
			{
				if(args[1][i] == '\"') mul++, strdel(args[1], i, i+1);
			}
			if(mul == 0)
			{
				dpp_error("You need to use '\"' to start a string.");
				return 0;
			}
			if(mul != 2)
			{
				dpp_error("Argument error.");
				return 0;
			}

			// do nothing, this is a comment
			return 1;
		}
		else
		{
			dpp_error("Unknown function in the package \"system\".");
			return 0;
		}
	}
	return 1;
}

stock dpp_subprocess(const line[])
{
	new codeblockline[1024];
	new args[10][100], funcgroup[2][20];
	dpp_parseline(line, args, ',');
	dpp_parseline(args[0], funcgroup, '.');

	if(!strcmp(funcgroup[0], "decl::func"))
	{
		for(new i = 0; i < dpp_maxfuncs; i++)
		{
			if(dpp_validfunc[i] == 0)
			{
				dpp_currentfuncid = i;
				dpp_validfunc[i] = 1;
				strcat(dpp_funcname[i], funcgroup[1]);
				return 1;
			}
		}
		return 1;
	}
	if(!strcmp(line, "decl::begin"))
	{
		dpp_interpreter = 0;
		return 1;
	}
	if(!strcmp(line, "decl::end"))
	{
		dpp_interpreter = 1;
		return 1;
	}
	if(dpp_interpreter == 0)
	{
		format(codeblockline, sizeof codeblockline, "%s;", line);
		dpp_debug("codeblockline:%s",codeblockline);
		dpp_debug("dpp_currentfuncid:%i",dpp_currentfuncid);
		strcat(dpp_funccodeblock[dpp_currentfuncid], codeblockline);
		return 1;
	}

	if(!strcmp(funcgroup[0], "import::package"))
	{
		if(!strcmp(funcgroup[1], "console"))
		{
			dpp_config[console_pkg] = 1;
			//dpp_debug("Package \"console\" successfully imported.");
			return 1;
		}
		else
		{
			dpp_error("Unknown package \"%s\".", funcgroup[1]);
			return 0;
		}
	}
	if(!strcmp(funcgroup[0], "using::user"))
	{
		for(new i; i < dpp_maxfuncs; i++)
		{
			if(!strcmp(dpp_funcname[i], funcgroup[1]))
			{
				dpp_subexecute(dpp_funccodeblock[i]);
				dpp_debug("dpp_funccodeblock[i]:%s",dpp_funccodeblock[999]);
				return 1;
			}
		}
		dpp_error("Function \"%s\" isn't registered.", funcgroup[1]);
		return 1;
	}
	if(!strcmp(funcgroup[0], "using::console"))
	{
		if(dpp_config[console_pkg] == 0)
		{
			dpp_error("Package \"console\" is not imported.");
			return 1;
		}
		// If the function used it "print"
		if(!strcmp(funcgroup[1], "cout"))
		{
			new mul, str[100];
			strmid(str, args[1], 0, 100);
			for(new i; i < strlen(args[1]); i++)
			{
				if(args[1][i] == '\"') mul++, strdel(args[1], i, i+1);
			}
			if(mul == 0)
			{
				dpp_error("You need to use '\"' to start a string.");
				return 0;
			}
			if(mul != 2)
			{
				dpp_error("Argument error.");
				return 0;
			}

			//dpp_debug("Line \"%s\" successfully executed.", line);
			print(args[1]);
			return 1;
		}
		else
		{
			dpp_error("Unknown function in the package \"console\".");
			return 0;
		}
	}
	return 1;
}