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

#define dpp_interpreter 1

/*
import::package,console;
import::file,"file.dpp"
using::console.print,"Hello World";
*/

stock dpp_process(const line[])
{
	new args[10][100], funcgroup[2][20];
	dpp_parseline(line, args, ',');
	dpp_parseline(args[0], funcgroup, '.');

	if(!strcmp(funcgroup[0], "import::package"))
	{
		if(!strcmp(funcgroup[1], "console"))
		{
			dpp_config[console_pkg] = 1;
			dpp_debug("Package \"console\" successfully imported.");
			return 1;
		}
		else
		{
			dpp_error("Unknown package \"%s\".", funcgroup[1]);
			return 0;
		}
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
			dpp_debug("Line \"%s\" successfully executed.", line);
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