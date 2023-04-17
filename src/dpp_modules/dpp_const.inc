/*
*
* D++ Scripting Language
*     Made for a SA:MP server
*
* Support for constants
*
* 
* - by: DEntisT, (c) 2022
*
*/

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

//const::define.int,"VAR1",1;
//const::define.bool,"VAR1",true;
//const::define.str,"VAR1","OKAY";

//const::undef.int,"VAR1";
//const::undef.bool,"VAR1";
//const::undef.str,"VAR1";

new dpp_constdata[dpp_maxconst][__dpp_const_val];

/////////////////////////////////////////////////////
stock dpp_argarraycheck(arg[])
{
	new newvalue[dpp_argcharsize];
	for(new i; i < dpp_maxconst; i++)
	{
		if(!strcmp(dpp_constdata[i][const_name], arg))
		{
			if(dpp_constdata[i][const_valid] == 1)
			{
				if(dpp_constdata[i][const_type] == dpp_const_type_int)
				{
					format(newvalue, dpp_argcharsize, "%i", 
						dpp_constdata[i][integervalue]);
				}
				if(dpp_constdata[i][const_type] == dpp_const_type_bool)
				{
					if(dpp_constdata[i][boolvalue] == 1)
					{
						strmid(arg, "true", 0, dpp_argcharsize, dpp_argcharsize);
					}
					if(dpp_constdata[i][boolvalue] == 0)
					{
						strmid(arg, "false", 0, dpp_argcharsize, dpp_argcharsize);
					}
				}
				if(dpp_constdata[i][const_type] == dpp_const_type_str)
				{
					format(newvalue, dpp_argcharsize, "\"%s\"", 
						dpp_constdata[i][stringvalue]);
				}
				dpp_debug("argarraycheck debug\n\tarr : '%s'\n\targ : '%s'\n\tnewvalue : '%s'", dpp_constdata[i][const_name], arg, newvalue);
				if(dpp_constdata[i][const_type] != dpp_const_type_bool)
				{
					strmid(arg, newvalue, 0, dpp_argcharsize, dpp_argcharsize);
				}
				dpp_debug("argarraycheck debug 2\n\tarr : '%s'\n\targ : '%s'\n\tnewvalue : '%s'", dpp_constdata[i][const_name], arg, newvalue);
				return 1;
			}
		}
	}
	return 1;
}

///////////////////////////CREATE/////////////////////////////

stock dpp_createintconst(const name[], value)
{
	for(new i; i < dpp_maxconst; i++)
	{
		if(dpp_constdata[i][const_valid] == 0)
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
				dpp_error("Invalid symbol name.",);
				return 1;
			}

			dpp_debug("Constant \"%s\" assigned a value : %i",name,value);
			strmid(dpp_constdata[i][const_name], name, 0, 64);
			dpp_constdata[i][integervalue] = value;
			dpp_constdata[i][const_type] = dpp_const_type_int;
			dpp_constdata[i][const_valid] = 1;
			return 1;
		}
	}
	return 1;
}

stock dpp_createboolconst(const name[], value)
{
	for(new i; i < dpp_maxconst; i++)
	{
		if(dpp_constdata[i][const_valid] == 0)
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
				dpp_error("Invalid symbol name.",);
				return 1;
			}

			dpp_debug("Constant \"%s\" assigned a value : %s",name,value ? "true" : "false");
			strmid(dpp_constdata[i][const_name], name, 0, 64);
			dpp_constdata[i][boolvalue] = value;
			dpp_constdata[i][const_type] = dpp_const_type_bool;
			dpp_constdata[i][const_valid] = 1;
			return 1;
		}
	}
	return 1;
}

stock dpp_createstrconst(const name[], const value[])
{
	for(new i; i < dpp_maxconst; i++)
	{
		if(dpp_constdata[i][const_valid] == 0)
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
				dpp_error("Invalid symbol name.",);
				return 1;
			}

			dpp_debug("Constant \"%s\" assigned a value : \"%s\"",name,value);
			strmid(dpp_constdata[i][const_name], name, 0, 64);
			strmid(dpp_constdata[i][stringvalue], value, 0, 256);
			dpp_constdata[i][const_type] = dpp_const_type_str;
			dpp_constdata[i][const_valid] = 1;
			return 1;
		}
	}
	return 1;
}

///////////////////////////DELETE///////////////////////


stock dpp_deleteintconst(const name[])
{
	for(new i; i < dpp_maxconst; i++)
	{
		if(!strcmp(dpp_constdata[i][const_name], name))
		{
			if(dpp_constdata[i][const_valid] == 1)
			{
				if(dpp_constdata[i][const_type] != dpp_const_type_int)
				{
					dpp_error("Constant \"%s\" is not an integer.", name);
					return 1;
				}

				strmid(dpp_constdata[i][const_name], "unknown", 0, 64);
				dpp_constdata[i][const_valid] = 0;
				dpp_constdata[i][integervalue] = 0;
				return 1;
			}
		}
		dpp_error("Constant \"%s\" not found.", name);
	}
	return 1;
}

stock dpp_deleteboolconst(const name[])
{
	for(new i; i < dpp_maxconst; i++)
	{
		if(!strcmp(dpp_constdata[i][const_name], name))
		{
			if(dpp_constdata[i][const_valid] == 1)
			{
				if(dpp_constdata[i][const_type] != dpp_const_type_bool)
				{
					dpp_error("Constant \"%s\" is not a boolean.", name);
					return 1;
				}

				strmid(dpp_constdata[i][const_name], "unknown", 0, 64);
				dpp_constdata[i][const_valid] = 0;
				dpp_constdata[i][boolvalue] = 0;
				return 1;
			}
		}
		dpp_error("Constant \"%s\" not found.", name);
	}
	return 1;
}

stock dpp_deletestrconst(const name[])
{
	for(new i; i < dpp_maxconst; i++)
	{
		if(!strcmp(dpp_constdata[i][const_name], name))
		{
			if(dpp_constdata[i][const_valid] == 1)
			{
				if(dpp_constdata[i][const_type] != dpp_const_type_str)
				{
					dpp_error("Constant \"%s\" is not a string.", name);
					return 1;
				}

				strmid(dpp_constdata[i][const_name], "unknown", 0, 64);
				dpp_constdata[i][const_valid] = 0;
				strmid(dpp_constdata[i][stringvalue], "empty", 0, 256);
				return 1;
			}
		}
		dpp_error("Constant \"%s\" not found.", name);
	}
	return 1;
}