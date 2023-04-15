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
	if(isnull(line))
	{
		return 1;
	}
	new codeblockline[1024];
	new args[10][dpp_argcharsize], funcgroup[2][20];
	dpp_parseline(line, args, ',');
	dpp_parseline(args[0], funcgroup, '.');

	//using::console.cout,"Hello World";

	//	funcgroup[0]	using::console
	//	funcgroup[1]	cout
	//	args[1]			"Hello World"

	if(!strcmp(funcgroup[0], "decl::func"))
	{
		dpp_createfunc(funcgroup[1]);
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

	if(dpp_interpreter == 0)
	{
		format(codeblockline, sizeof codeblockline, "%s;", line);
		dpp_debug("codeblockline:%s",codeblockline);
		dpp_debug("dpp_currentfuncid:%i",dpp_currentfuncid);
		strcat(dpp_funccodeblock[dpp_currentfuncid], codeblockline);
		return 1;
	}

	for(new i; i < 10; i++)
	{
		dpp_argarraycheck(args[i]);
	}

	if(!strcmp(funcgroup[0], "const::define"))
	{
		if(!strcmp(funcgroup[1], "int"))
		{
			/*new mul, str[dpp_argcharsize];
			strmid(str, args[1], 0, dpp_argcharsize);
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
				dpp_error("Argument error; [%i] \"%s\"", mul, args[1]);
				return 0;
			}*/

			if(!dpp_isnumeric(args[2]))
			{
				dpp_error("Argument error; value must be an integer.");
				return 0;
			}

			dpp_createintconst(args[1],strval(args[2]));
			return 1;
		}
		if(!strcmp(funcgroup[1], "bool"))
		{
			/*new mul, str[dpp_argcharsize];
			strmid(str, args[1], 0, dpp_argcharsize);
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
				dpp_error("Argument error; [%i] \"%s\"", mul, args[1]);
				return 0;
			}*/

			if(strcmp(args[2],"true") && strcmp(args[2],"false"))
			{
				dpp_error("Argument error; value must be either 'true' or 'false'.");
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
			/*new mul, str[dpp_argcharsize];
			strmid(str, args[1], 0, dpp_argcharsize);
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
				dpp_error("Argument error; [%i] \"%s\"", mul, args[1]);
				return 0;
			}*/

			new mul2, str2[dpp_argcharsize];
			strmid(str2, args[2], 0, dpp_argcharsize);
			for(new i; i < strlen(args[2]); i++)
			{
				if(args[2][i] == '\"') mul2++, strdel(args[2], i, i+1);
			}
			if(mul2 == 0)
			{
				dpp_error("You need to use '\"' to start a string.");
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
			/*new mul, str[dpp_argcharsize];
			strmid(str, args[1], 0, dpp_argcharsize);
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
				dpp_error("Argument error; [%i] \"%s\"", mul, args[1]);
				return 0;
			}*/

			dpp_deleteintconst(args[1]);
			return 1;
		}
		if(!strcmp(funcgroup[1], "bool"))
		{
			/*new mul, str[dpp_argcharsize];
			strmid(str, args[1], 0, dpp_argcharsize);
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
				dpp_error("Argument error; [%i] \"%s\"", mul, args[1]);
				return 0;
			}*/

			dpp_deleteboolconst(args[1]);
			return 1;
		}
		if(!strcmp(funcgroup[1], "str"))
		{
			/*new mul, str[dpp_argcharsize];
			strmid(str, args[1], 0, dpp_argcharsize);
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
				dpp_error("Argument error; [%i] \"%s\"", mul, args[1]);
				return 0;
			}*/

			dpp_deletestrconst(args[1]);
			return 1;
		}
		
		else
		{
			dpp_error("Unknown symbol type \"%s\".", funcgroup[1]);
			return 0;
		}
	}

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
		if(!strcmp(funcgroup[1], "samp"))
		{
			dpp_config[samp_pkg] = 1;
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
		if(fexist(filename)) return dpp_executefile(filename);
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
			new mul, str[dpp_argcharsize];
			strmid(str, args[1], 0, dpp_argcharsize);
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
				dpp_error("Argument error; [%i] \"%s\"", mul, args[1]);
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
			new mul, str[dpp_argcharsize];
			strmid(str, args[1], 0, dpp_argcharsize);
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
				dpp_error("Argument error; [%i] \"%s\"", mul, args[1]);
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
	if(!strcmp(funcgroup[0], "using::samp"))
	{
		if(dpp_config[samp_pkg] == 0)
		{
			dpp_error("Package \"samp\" is not imported.");
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
				dpp_error("You need to use '\"' to start a string.");
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
				dpp_error("Argument error; value must be an integer.");
				return 0;
			}

			SetMaxPlayers(strval(args[1]));
			return 1;
		}

		else
		{
			dpp_error("Unknown function in the package \"system\".");
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