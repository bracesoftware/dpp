/*
*
* D++ Language
*
* (c) Copyright - 2022, DEntisT.
*
* Core functions.
*
*/

#define dpp_%0\32; dpp_
#if !defined isnull
	#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif
#define dppfunc::%0(%1) stock dpp_%0(%1)
#define @DETUTILSVARS_DEL__@%0\32; @DETUTILSVARS_DEL__@
#define delete @DETUTILSVARS_DEL__@
#define @DETUTILSVARS_SET__@%0\32; @DETUTILSVARS_SET__@
#define set @DETUTILSVARS_SET__@
#define @DETUTILSVARS_GET__@%0\32; @DETUTILSVARS_GET__@
#define get @DETUTILSVARS_GET__@
#define @DETUTILSVARS_DECLARE__@%0\32; @DETUTILSVARS_DECLARE__@
#define declare @DETUTILSVARS_DECLARE__@
// declare Integer("Variable");
#define @DETUTILSVARS_DECLARE__@Integer%1(%0) __GetIntegerValue(%0)
// declare Boolean("Variable");
#define @DETUTILSVARS_DECLARE__@Boolean%1(%0) __GetBooleanValue(%0)
// declare Float("Variable");
#define @DETUTILSVARS_DECLARE__@Float%1(%0) __GetFloatValue(%0)
// declare Integer("Variable");
#define @DETUTILSVARS_DECLARE__@String%1(%0) __GetStringValue(%0)
// get Integer("Variable");
#define @DETUTILSVARS_GET__@Integer%1(%0) __GetIntegerValue(%0)
// get Boolean("Variable");
#define @DETUTILSVARS_GET__@Boolean%1(%0) __GetBooleanValue(%0)
// get Float("Variable");
#define @DETUTILSVARS_GET__@Float%1(%0) __GetFloatValue(%0)
// get Integer("Variable");
#define @DETUTILSVARS_GET__@String%1(%0) __GetStringValue(%0)
// set Integer("Variable");
#define @DETUTILSVARS_SET__@Integer%1(%0) __SetIntegerValue(%0)
// set Boolean("Variable");
#define @DETUTILSVARS_SET__@Boolean%1(%0) __SetBooleanValue(%0)
// set Float("Variable");
#define @DETUTILSVARS_SET__@Float%1(%0) __SetFloatValue(%0)
// set Integer("Variable");
#define @DETUTILSVARS_SET__@String%1(%0) __SetStringValue(%0)
// delete Integer("Variable");
#define @DETUTILSVARS_DEL__@Integer%1(%0) __DeleteIntegerVariable(%0)
// delete Boolean("Variable");
#define @DETUTILSVARS_DEL__@Boolean%1(%0) __DeleteBooleanVariable(%0)
// delete Float("Variable");
#define @DETUTILSVARS_DEL__@Float%1(%0) __DeleteFloatVariable(%0)
// delete Integer("Variable");
#define @DETUTILSVARS_DEL__@String%1(%0) __DeleteStringVariable(%0)

#define dpp_comment print("---------------[D++ Script]---------------")

#define MAX_STRING_CELLS 256
// General definitions:

// CallLocalFunction("OnVariableCreate", "si", name, VARIABLE_TYPE_);
forward OnVariableCreate(varname[], vartype);
public OnVariableCreate(varname[], vartype)
{
	if(dpp_config[execdebug] == 1)
	{
		printf("[D++]: (info) - Variable '%s' created.", varname);
	}
	return 1;
}
// CallLocalFunction("OnVariableUpdate", "siii", name, VARIABLE_TYPE_, value, dimension);
forward OnVariableUpdate(varname[], vartype, value, dimension);
// CallLocalFunction("OnVariableDelete", "si", name, VARIABLE_TYPE_);
forward OnVariableDelete(varname[], vartype);

#define VARIABLE_TYPE_INTEGER 0
#define VARIABLE_TYPE_BOOLEAN 1
#define VARIABLE_TYPE_STRING 2
#define VARIABLE_TYPE_FLOAT 3
#define MAX_VAR_DIMENSIONS 256

// Integers:

#define MAX_INTEGER_VARS 1000

enum enum_IntVarData
{
	Valid,
	Multi,
	Const,
	IntName[32],
	ReturnVal,
	Dimensions[MAX_VAR_DIMENSIONS]
}

new g_IntCache[MAX_INTEGER_VARS][enum_IntVarData];

// Booleans:

#define MAX_BOOLEAN_VARS 1000

enum enum_BoolVarData
{
	Valid,
	Multi,
	Const,
	BoolName[32],
	bool:ReturnVal,
	Dimensions[MAX_VAR_DIMENSIONS]
}

new g_BoolCache[MAX_BOOLEAN_VARS][enum_BoolVarData];

// Strings:

#define MAX_STRINGS 1000
#define MAX_STRING_VARS MAX_STRINGS

enum enum_StringData
{
	Valid,
	Const,
	StringName[32],
	ReturnVal[MAX_STRING_CELLS]
}

new g_StringCache[MAX_STRINGS][enum_StringData];

// Floats:

#define MAX_FLOAT_VARS 1000

enum enum_FloatData
{
	Valid,
	Multi,
	Const,
	FloatName[32],
	Float:ReturnVal,
	Float:Dimensions[MAX_VAR_DIMENSIONS]
}

new g_FloatCache[MAX_FLOAT_VARS][enum_FloatData];

stock CallVariableHandler(const name[])
{
	new funcname[32];
	format(funcname, sizeof funcname, "@DETVAR_%s", name);
	return CallLocalFunction(funcname, "");
}

// DELETE FUNCS

// Delete functions are REALLY important.
// Though, I HIGHLY recommend to delete every variable which is not needed because
// if you don't, you'll eventually run out of space required for variables to create 
// and create functions will fail.

stock __DeleteIntegerVariable(const name[])
{
	for(new i; i < MAX_INTEGER_VARS; i++)
	{
		if(!strcmp(g_IntCache[i][IntName], name, false))
		{
			strmid(g_IntCache[i][IntName], " ", 0, 1);
			g_IntCache[i][Valid] = 0;
			for(new x; x < MAX_VAR_DIMENSIONS; x++)
			{
				g_IntCache[i][Dimensions][x] = 0;
			}
			g_IntCache[i][ReturnVal] = 0;
			CallLocalFunction("OnVariableDelete", "si", name, VARIABLE_TYPE_INTEGER);
			return 1;
		}
	}
	return 0;
}

stock __DeleteBooleanVariable(const name[])
{
	for(new i; i < MAX_BOOLEAN_VARS; i++)
	{
		if(!strcmp(g_BoolCache[i][BoolName], name, false))
		{
			strmid(g_BoolCache[i][BoolName], " ", 0, 1);
			g_BoolCache[i][Valid] = 0;
			for(new x; x < MAX_VAR_DIMENSIONS; x++)
			{
				g_BoolCache[i][Dimensions][x] = false;
			}
			g_BoolCache[i][ReturnVal] = false;
			CallLocalFunction("OnVariableDelete", "si", name, VARIABLE_TYPE_BOOLEAN);
			return 1;
		}
	}
	return 0;
}

stock __DeleteFloatVariable(const name[])
{
	for(new i; i < MAX_FLOAT_VARS; i++)
	{
		if(!strcmp(g_FloatCache[i][FloatName], name, false))
		{
			strmid(g_FloatCache[i][FloatName], " ", 0, 1);
			g_FloatCache[i][Valid] = 0;
			for(new x; x < MAX_VAR_DIMENSIONS; x++)
			{
				g_FloatCache[i][Dimensions][x] = Float:0;
			}
			g_FloatCache[i][ReturnVal] = Float:0;
			CallLocalFunction("OnVariableDelete", "si", name, VARIABLE_TYPE_FLOAT);
			return 1;
		}
	}
	return 0;
}

stock __DeleteStringVariable(const name[])
{
	for(new i; i < MAX_STRING_VARS; i++)
	{
		if(!strcmp(g_StringCache[i][StringName], name, false))
		{
			strmid(g_StringCache[i][ReturnVal], " ", 0, 1);
			strmid(g_StringCache[i][StringName], " ", 0, 1);
			g_StringCache[i][Valid] = 0;
			CallLocalFunction("OnVariableDelete", "si", name, VARIABLE_TYPE_STRING);
			return 1;
		}
	}
	return 0;
}

// DECLARATION FUNCS

dppfunc::integer(const name[], multi = 0, constant = 0, constvalue = 0)
{
	for(new i; i < MAX_INTEGER_VARS; i++)
	{
		if(g_IntCache[i][Valid] == 0)
		{
			strmid(g_IntCache[i][IntName], name, 0, 32);
			g_IntCache[i][Multi] = multi;
			if(constant == 1 && multi == 1)
			{
				printf("[samp-detutils]: (var error) - You can't create constant variables with more dimensions.");
				return 0;
			}
			if(multi == 1)
			{
				for(new x; x < MAX_VAR_DIMENSIONS; x++)
				{
					g_IntCache[i][Dimensions][x] = 0;// Initialize the "dimension" sizes.
				}
			}
			else if(multi == 0)
			{
				g_IntCache[i][ReturnVal] = 0; // Initialize the single return size.
			}
			if(constant == 1)
			{
				g_IntCache[i][Const] = 1;
				g_IntCache[i][ReturnVal] = constvalue;
			}
			CallLocalFunction("OnVariableCreate", "si", name, VARIABLE_TYPE_INTEGER);
			g_IntCache[i][Valid] = 1;
			return 1;
		}   
	}
	return 0;
}

dppfunc::bool(const name[], multi, constant, bool:constvalue = false)
{
	for(new i; i < MAX_BOOLEAN_VARS; i++)
	{
		if(g_BoolCache[i][Valid] == 0)
		{
			strmid(g_BoolCache[i][BoolName], name, 0, 32);
			g_BoolCache[i][Multi] = multi;
			if(constant == 1 && multi == 1)
			{
				printf("[samp-detutils]: (var error) - You can't create constant variables with more dimensions.");
				return 0;
			}
			if(multi == 1)
			{
				for(new x; x < MAX_VAR_DIMENSIONS; x++)
				{
					g_BoolCache[i][Dimensions][x] = 0;// Initialize the "dimension" sizes.
				}
			}
			else if(multi == 0)
			{
				g_BoolCache[i][ReturnVal] = false; // Initialize the single return size.
			}
			if(constant == 1)
			{
				if(constvalue != false && constvalue != true)
				{
					printf("[samp-detutils]: (var error) - Booleans can only have 0 and 1 as values.");
					return 0;
				}
				g_BoolCache[i][Const] = 1;
				g_BoolCache[i][ReturnVal] = constvalue;
			}
			CallLocalFunction("OnVariableCreate", "si", name, VARIABLE_TYPE_BOOLEAN);
			g_BoolCache[i][Valid] = 1;
			return 1;
		}   
	}
	return 0;
}

dppfunc::float(const name[], multi, constant, Float:constvalue = 0.0000)
{
	for(new i; i < MAX_FLOAT_VARS; i++)
	{
		if(g_FloatCache[i][Valid] == 0)
		{
			strmid(g_FloatCache[i][FloatName], name, 0, 32);
			g_FloatCache[i][Multi] = multi;
			if(constant == 1 && multi == 1)
			{
				printf("[samp-detutils]: (var error) - You can't create constant variables with more dimensions.");
				return 0;
			}
			if(multi == 1)
			{
				for(new x; x < MAX_VAR_DIMENSIONS; x++)
				{
					g_FloatCache[i][Dimensions][x] = 0;// Initialize the "dimension" sizes.
				}
			}
			else if(multi == 0)
			{
				g_FloatCache[i][ReturnVal] = 0; // Initialize the single return size.
			}
			if(constant == 1)
			{
				g_FloatCache[i][Const] = 1;
				g_FloatCache[i][ReturnVal] = constvalue;
			}
			CallLocalFunction("OnVariableCreate", "si", name, VARIABLE_TYPE_FLOAT);
			g_FloatCache[i][Valid] = 1;
			return 1;
		}   
	}
	return 0;
}

dppfunc::string(const name[], constant, const constvalue[])
{
	for(new i; i < MAX_STRINGS; i++)
	{
		if(g_StringCache[i][Valid] == 0)
		{
			new len = strlen(constvalue);
			strmid(g_StringCache[i][StringName], name, 0, 32);
			if(constant == 1)
			{
				strmid(g_StringCache[i][ReturnVal], constvalue, 0, len);
				g_StringCache[i][Const] = 1;
			}
			else if(constant == 0)
			{
				strmid(g_StringCache[i][ReturnVal], constvalue, 0, len);
			}
			CallLocalFunction("OnVariableCreate", "si", name, VARIABLE_TYPE_STRING);
			g_StringCache[i][Valid] = 1;
			return 1;
		}   
	}
	return 0;
}

// GET... FUNCS

stock __GetIntegerValue(const name[], dimension = -1)
{
	for(new i; i < MAX_INTEGER_VARS; i++)
	{
		if(!strcmp(g_IntCache[i][IntName], name, false))
		{
			if(g_IntCache[i][Multi] == 1)
			{
				if(dimension == -1)
				{
					printf("[samp-detutils]: (var error) - Invalid dimension.");
					return 0;
				}
				return g_IntCache[i][Dimensions][dimension];
			}
			else if(g_IntCache[i][Multi] == 0)
			{
				return g_IntCache[i][ReturnVal];
			}
		}
	}
	return 0;
}

stock __GetBooleanValue(const name[], dimension = -1)
{
	for(new i; i < MAX_BOOLEAN_VARS; i++)
	{
		if(!strcmp(g_BoolCache[i][BoolName], name, false))
		{
			if(g_BoolCache[i][Multi] == 1)
			{
				if(dimension == -1)
				{
					printf("[samp-detutils]: (var error) - Invalid dimension.");
					return 0;
				}
				return g_BoolCache[i][Dimensions][dimension];
			}
			else if(g_BoolCache[i][Multi] == 0)
			{
				return g_BoolCache[i][ReturnVal];
			}
		}
	}
	return 0;
}

stock Float:__GetFloatValue(const name[], dimension = -1)
{
	for(new i; i < MAX_FLOAT_VARS; i++)
	{
		if(!strcmp(g_FloatCache[i][FloatName], name, false))
		{
			if(g_FloatCache[i][Multi] == 1)
			{
				if(dimension == -1)
				{
					printf("[samp-detutils]: (var error) - Invalid dimension.");
					return Float:0;
				}
				return g_FloatCache[i][Dimensions][dimension];
			}
			else if(g_FloatCache[i][Multi] == 0)
			{
				return g_FloatCache[i][ReturnVal];
			}
		}
	}
	return Float:0;
}

stock __GetStringValue(const name[])
{
	new ret[1024];
	format(ret, 4, "NULL");
			
	for(new i; i < MAX_STRING_VARS; i++)
	{
		if(!strcmp(g_StringCache[i][StringName], name, false))
		{
			format(ret, 1024, "%s", g_StringCache[i][ReturnVal]);
			return ret;
		}
	}
	return ret;
}

// SET THE VALUE.

stock __SetIntegerValue(const name[], value, dimension = -1)
{
	for(new i; i < MAX_INTEGER_VARS; i++)
	{
		if(!strcmp(g_IntCache[i][IntName], name, false))
		{
			if(g_IntCache[i][Const] == 1)
			{
				printf("[samp-detutils]: (var error) - Cannot update the constant value of : %s", name);
				return 0;
			}
			if(g_IntCache[i][Multi] == 1)
			{
				if(dimension == -1)
				{
					printf("[samp-detutils]: (var error) - Invalid dimension.");
					return 0;
				}
				CallLocalFunction("OnVariableUpdate", "siii", name, VARIABLE_TYPE_INTEGER, value, dimension);
				g_IntCache[i][Dimensions][dimension] = value;
				return 1;
			}
			else if(g_IntCache[i][Multi] == 0)
			{
				CallLocalFunction("OnVariableUpdate", "siii", name, VARIABLE_TYPE_INTEGER, value, dimension);
				g_IntCache[i][ReturnVal] = value;
				return 1;
			}
		}
	}
	return 0;
}

stock __SetBooleanValue(const name[], bool:value, dimension = -1)
{
	for(new i; i < MAX_BOOLEAN_VARS; i++)
	{
		if(!strcmp(g_BoolCache[i][BoolName], name, false))
		{
			if(g_BoolCache[i][Const] == 1)
			{
				printf("[samp-detutils]: (var error) - Cannot update the constant value of : %s", name);
				return 0;
			}
			if(value != false && value != true)
			{
				printf("[samp-detutils]: (var error) - Boolean variables can only hold the values of 0 and 1.");
				return 0;
			}
			if(g_BoolCache[i][Multi] == 1)
			{
				if(dimension == -1)
				{
					printf("[samp-detutils]: (var error) - Invalid dimension.");
					return 0;
				}
				CallLocalFunction("OnVariableUpdate", "siii", name, VARIABLE_TYPE_BOOLEAN, value, dimension);
				g_BoolCache[i][Dimensions][dimension] = value;
				return true;
			}
			else if(g_BoolCache[i][Multi] == 0)
			{
				CallLocalFunction("OnVariableUpdate", "siii", name, VARIABLE_TYPE_BOOLEAN, value, dimension);
				g_BoolCache[i][ReturnVal] = value;
				return true;
			}
		}
	}
	return 0;
}

stock __SetFloatValue(const name[], Float:value, dimension = -1)
{
	for(new i; i < MAX_FLOAT_VARS; i++)
	{
		if(!strcmp(g_FloatCache[i][FloatName], name, false))
		{
			if(g_FloatCache[i][Const] == 1)
			{
				printf("[samp-detutils]: (var error) - Cannot update the constant value of : %s", name);
				return 0;
			}
			if(g_FloatCache[i][Multi] == 1)
			{
				if(dimension == -1)
				{
					printf("[samp-detutils]: (var error) - Invalid dimension.");
					return 0;
				}
				CallLocalFunction("OnVariableUpdate", "siii", name, VARIABLE_TYPE_FLOAT, value, dimension);
				g_FloatCache[i][Dimensions][dimension] = value;
				return 1;
			}
			else if(g_FloatCache[i][Multi] == 0)
			{
				CallLocalFunction("OnVariableUpdate", "siii", name, VARIABLE_TYPE_FLOAT, value, dimension);
				g_FloatCache[i][ReturnVal] = value;
				return 1;
			}
		}
	}
	return 0;
}

stock __SetStringValue(const name[], const value[])
{           
	for(new i; i < MAX_STRING_VARS; i++)
	{
		if(!strcmp(g_StringCache[i][StringName], name, false))
		{
			if(g_StringCache[i][Const] == 1)
			{
				printf("[samp-detutils]: (var error) - Cannot update the constant value of : %s", name);
				return 0;
			}
			new len = strlen(value);
			strmid(g_StringCache[i][ReturnVal], value, 0, len);
			CallLocalFunction("OnVariableUpdate", "siii", name, VARIABLE_TYPE_STRING, 0, -1);
			return 1;
		}
	}
	return 0;
}

#if defined detutils_complete_error_boom
stock CreateVariable( // this is deprecated function
	const name[], 
	type, 
	constant = 0, 
	{Float,_,bool}:constvalue = {Float,_,bool}:0, 
	const conststr[] = "_", 
	multi = 0
)
{
	switch(type)
	{
		case VARIABLE_TYPE_INTEGER:
		{
			// Integers.
			for(new i; i < MAX_INTEGER_VARS; i++)
			{
				if(g_IntCache[i][Valid] == 0)
				{
					strmid(g_IntCache[i][IntName], name, 0, 32);
					g_IntCache[i][Multi] = multi;
					if(constant == 1 && multi == 1)
					{
						printf("[samp-detutils]: (var error) - You can't create constant variables with more dimensions.");
						return 0;
					}
					if(multi == 1)
					{
						for(new x; x < MAX_VAR_DIMENSIONS; x++)
						{
							g_IntCache[i][Dimensions][x] = 0;// Initialize the "dimension" sizes.
						}
					}
					else if(multi == 0)
					{
						g_IntCache[i][ReturnVal] = 0; // Initialize the single return size.
					}
					if(constant == 1)
					{
						g_IntCache[i][Const] = 1;
						g_IntCache[i][ReturnVal] = constvalue;
					}
					g_IntCache[i][Valid] = 1;
					return 1;
				}   
			}
		}
		case VARIABLE_TYPE_BOOLEAN:
		{
			// Booleans.
			for(new i; i < MAX_BOOLEAN_VARS; i++)
			{
				if(g_BoolCache[i][Valid] == 0)
				{
					strmid(g_BoolCache[i][BoolName], name, 0, 32);
					g_BoolCache[i][Multi] = multi;
					if(constant == 1 && multi == 1)
					{
						printf("[samp-detutils]: (var error) - You can't create constant variables with more dimensions.");
						return 0;
					}
					if(multi == 1)
					{
						for(new x; x < MAX_VAR_DIMENSIONS; x++)
						{
							g_BoolCache[i][Dimensions][x] = 0;// Initialize the "dimension" sizes.
						}
					}
					else if(multi == 0)
					{
						g_BoolCache[i][ReturnVal] = 0; // Initialize the single return size.
					}
					if(constant == 1)
					{
						if(constvalue != 0 && constvalue != 1)
						{
							printf("[samp-detutils]: (var error) - Booleans can only have 0 and 1 as values.");
							return 0;
						}
						g_BoolCache[i][Const] = 1;
						g_BoolCache[i][ReturnVal] = constvalue;
					}
					g_BoolCache[i][Valid] = 1;
					return 1;
				}   
			}
		}
		case VARIABLE_TYPE_STRING:
		{
			// Strings.
			for(new i; i < MAX_STRINGS; i++)
			{
				if(g_StringCache[i][Valid] == 0)
				{
					strmid(g_IntCache[i][FloatName], name, 0, 32);
					g_StringCache[i][Multi] = multi;
					if(constant == 1 && multi == 1)
					{
						printf("[samp-detutils]: (var error) - You can't create constant variables with more dimensions.");
						return 0;
					}
					if(multi == 1)
					{
						// There can't be more than a 1 return size for strings :( Pawn limits
						printf("[samp-detutils]: (string error) - Strings cannot be multidimensional variables.");
						return 0;
					}
					else if(multi == 0)
					{
						g_StringCache[i][ReturnVal] = 0; // Initialize the single return size.
					}
					g_StringCache[i][Valid] = 1;
					return 1;
				}   
			}

		}
		case VARIABLE_TYPE_FLOAT:
		{
			// Floats / real numbers.
			for(new i; i < MAX_FLOAT_VARS; i++)
			{
				if(g_FloatCache[i][Valid] == 0)
				{
					strmid(g_FloatCache[i][FloatName], name, 0, 32);
					g_FloatCache[i][Multi] = multi;
					if(constant == 1 && multi == 1)
					{
						printf("[samp-detutils]: (var error) - You can't create constant variables with more dimensions.");
						return 0;
					}
					if(multi == 1)
					{
						for(new x; x < MAX_VAR_DIMENSIONS; x++)
						{
							g_FloatCache[i][Dimensions][x] = 0;// Initialize the "dimension" sizes.
						}
					}
					else if(multi == 0)
					{
						g_FloatCache[i][ReturnVal] = 0; // Initialize the single return size.
					}
					if(constant == 1)
					{
						g_FloatCache[i][Const] = 1;
						g_FloatCache[i][ReturnVal] = constvalue;
					}
					g_FloatCache[i][Valid] = 1;
					return 1;
				}   
			}
		}
	}
	return 0;
}

#endif

stock __GetIntegerVarId(const name[])
{
	for(new i = 1; 
		i < MAX_INTEGER_VARS; 
		i++)
	{
		if(!strcmp(g_IntCache[i][IntName], name))
		{
			return i;
		}
	}
	return 0;
}

stock __GetBoolVarId(const name[])
{
	for(new i = 1; 
		i < MAX_BOOLEAN_VARS; 
		i++)
	{
		if(!strcmp(g_BoolCache[i][BoolName], name))
		{
			return i;
		}
	}
	return 0;
}

stock __GetFloatVarId(const name[])
{
	for(new i = 1; 
		i < MAX_FLOAT_VARS; 
		i++)
	{
		if(!strcmp(g_FloatCache[i][FloatName], name))
		{
			return i;
		}
	}
	return 0;
}

stock __GetStringVarId(const name[])
{
	for(new i = 1; 
		i < MAX_STRING_VARS; 
		i++)
	{
		if(!strcmp(g_StringCache[i][StringName], name))
		{
			return i;
		}
	}
	return 0;
}

static dpp_split(const strsrc[], strdest[][], delimiter)
{
	new i, li;
	new aNum;
	new len;
	while(i <= strlen(strsrc))
	{
		if(strsrc[i]==delimiter || i==strlen(strsrc))
		{
			len = strmid(strdest[aNum], strsrc, li, i, 128);
			strdest[aNum][len] = 0;
			li = i+1;
			aNum++;
		}
		i++;
	}
	return 1;
}

stock dpp_loadconfig(id)
{
	new d_ArrayCoordinates[19][32],file_name[100];
	format(file_name, sizeof file_name,
		dpp_configfile, id);
	new strFromFile2[128];
	if(!fexist(file_name)) return 0;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		fread(file, strFromFile2);
		d_me_SplitString(strFromFile2, d_ArrayCoordinates, ',');
		strmid(dpp_config[file], d_ArrayCoordinates[0], 0, strlen(d_ArrayCoordinates[0]));
		
		fclose(file);
	}
	return 1;
}

stock dpp_saveconfig(loopid)
{
	new string[228], file_name[100];
	format(file_name, sizeof file_name,
		dpp_configfile, loopid);
	new id = loopid;
	format(string, sizeof(string), 
		"%f,%f,%f,%f,%f,%f,%i");
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

dppfunc::init()
{
	print("                                        ");
	print("WELCOME TO D++ LANGUAGE INTERPRETER!");
	print("D++ | "dpp_version" : System is starting...");
	print("D++ | INFO: Loaded.");
	print("                                        ");
}
/*
dppfunc::error(const str[])
{
	new output[256];
	format(output, sizeof output, "D++ | Error: %s",str);
	printf(output);    
	return 1;
}

dppfunc::debug(const str[])
{
	new output[256];
	format(output, sizeof output, "D++ | Debug: %s",str);
	printf(output);    
	return 1;
}

dppfunc::print(const str[])
{
	new output[256];
	format(output, sizeof output, "[D++]: (info) - %s",str);
	printf(output);    
	return 1;
}
*/

#define max_functions 100

enum FunctionInfo
{
	name[32],
	data[1024]
}

new g_FunctionCache[max_functions][FunctionInfo];

#define dpp_error(%1) printf("D++ | ERROR: "%1)
#define dpp_debug(%1) printf("D++ | DEBUG: "%1)
#define dpp_print(%1) printf("D++ | INFO: "%1)

new funcindex;

dppfunc::process(const line[])
{
	if(isnull(line))
		return 0;
	if(dpp_config[execdebug] == 1) printf("[D++]: (info) - Processing: '%s'", line);
	new args[10][100], funcgroup[2][20];
	dpp_split(line, args, ',');
	dpp_split(args[0], funcgroup, '.');
	for(new i; i < strlen(funcgroup[0]); i++)
	{
		if(funcgroup[0][i] == ' ') strdel(funcgroup[0], i, i+1);
	}
	for(new i; i < strlen(funcgroup[0]); i++)
	{
		if(funcgroup[0][i] == '\10') strdel(funcgroup[0], i, i+1);
	}

	// Functions etc
	if(dpp_config[execdebug] == 1) printf("[D++]: (info) - funcgrp: '%s %s'", funcgroup[0],funcgroup[1]);
	if(!strcmp(funcgroup[0], "option::debug"))
	{
		dpp_config[execdebug] = strval(args[1]);
		return 1;
	}
	if(!strcmp(funcgroup[0], "option::importbacktrace"))
	{
		dpp_config[import_backtrace] = strval(args[1]);
		return 1;
	}
	if(!strcmp(funcgroup[0], "import::file"))
	{
		for(new i; i < strlen(args[1]); i++)
		{
			if(args[1][i] == '\"') strdel(args[1], i, i+1);
		}
		new dpp_include[32];
		format(dpp_include, 32, "%s.dpp", args[1]);
		if(!fexist(dpp_include))
		{
			dpp_error("Cannot read from file: '%s'",funcgroup[1]);
			return 0;
		}
		dpp_subexecute(dpp_include);
		return 1;
	}
	if(!strcmp(funcgroup[0], "using::console"))
	{
		if(dpp_config[console_pkg] == 0)
		{
			dpp_error("Package 'console' is not imported.");
			return 1;
		}
		// If the function used it "print"
		if(!strcmp(funcgroup[1], "print"))
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
			print(args[1]);
			return 1;
		}
		else
		{
			dpp_error("Unknown function.");
			return 0;
		}
	}
	if(!strcmp(funcgroup[0], "using::user"))
	{
		if(dpp_config[user_pkg] == 0)
		{
			dpp_error("Package 'user' is not imported.");
			return 1;
		}
		for(new d; d < max_functions; d++)
		{
			if(!strcmp(g_FunctionCache[d][name], 
				funcgroup[1], false))
			{
				dpp_subprocess(g_FunctionCache[d][data]);
				return 1;
			}
		}
		dpp_error("Unknown user function.");
		return 0;
	}
	if(!strcmp(funcgroup[0], "import::package"))
	{
		// If the function used it "print"
		if(!strcmp(funcgroup[1], "console"))
		{
			dpp_config[console_pkg] = 1;
			return 1;
		}
		if(!strcmp(funcgroup[1], "user"))
		{
			dpp_config[user_pkg] = 1;
			return 1;
		}
		else
		{
			dpp_error("Unknown package.");
			return 0;
		}
	}
	if(!strcmp(funcgroup[0], "decl::var"))
	{
		// If the var is integer
		if(!strcmp(funcgroup[1], "int"))
		{
			dpp_print("Var : %s created.", args[1]);
			declare Integer(args[1]);
			return 1;
		}
		else
		{
			dpp_error("Invalid declaration.");
			return 0;
		}
	}
	if(!strcmp(funcgroup[0], "decl::func"))
	{
		static address[2][1024];
		dpp_split(line, address, '?');
		// If the var is integer
		if(!strcmp(funcgroup[1], "int"))
		{
			strmid(
				g_FunctionCache[funcindex][name],
				args[1],
				0, strlen(args[1])
				)
			;
			strmid(
				g_FunctionCache[funcindex][data],
				address[1],
				0, strlen(address[1])
				)
			;
			funcindex++;
			return 1;
		}
		else
		{
			dpp_error("Invalid declaration.");
			return 0;
		}
	}
	if(!strcmp(funcgroup[0], "var::set"))
	{
		// If the var is integer
		if(!strcmp(funcgroup[1], "int"))
		{
			set Integer(args[1],strval(args[2]));
			return 1;
		}
		else
		{
			dpp_error("Invalid declaration.");
			return 0;
		}
	}
	else
	{
		dpp_error("Unknown directive.");
	}
	return 0;
}

dppfunc::subprocess(const line[])
{
	return dpp_process(line);
}

#define MAX_CODE_LINES 100
#define MAX_LN_CHARS 300

dppfunc::isstringchar(const str[], index)
{
	new count, count1 = -1, count2 = -1;
	for(new i; i < strlen(str); i++)
	{
		count++;
		if(str[i] == '\"')
		{
			count1 = count; 
			break;
		}
	}
	for(new i; i < strlen(str); i++)
	{
		count++;
		if(str[i] == '\"')
		{
			count2 = count; 
			break;
		}
	}
	if(count1 < index < count2)
	{
		return true;
	}
	return false;
}

dppfunc::execute(const dirbose[])
{
	printf("D++ | INFO: Executing the script: '%s'", dirbose);
	printf("           ");
	dpp_comment;
	printf("           ");
	
	new content[16000], address[MAX_CODE_LINES][MAX_LN_CHARS];
	new File:file = fopen(dirbose, io_read);
	if(file)
	{
		fread(file, content);
		dpp_split(content, address, ';');
		for(new i; i < MAX_CODE_LINES; i++)
		{
			dpp_process(address[i]);
		}
		fclose(file);
	}

	printf("           ");
	dpp_comment;
	printf("D++ | INFO: The interpreter has reached the EOS point.");
	return 1;
}

dppfunc::subexecute(const dirbose[])
{
	if(dpp_config[import_backtrace] == 1)
	{
		printf("D++ | INFO: Executing the script: '%s'", dirbose);
		printf("           ");
		dpp_comment;
		printf("           ");
	}
	new content[16000], address[MAX_CODE_LINES][MAX_LN_CHARS];
	new File:file = fopen(dirbose, io_read);
	if(file)
	{
		fread(file, content);
		dpp_split(content, address, ';');
		for(new i; i < MAX_CODE_LINES; i++)
		{
			dpp_process(address[i]);
		}
		fclose(file);
	}
	if(dpp_config[import_backtrace] == 1)
	{
		printf("           ");
		dpp_comment;
		printf("D++ | INFO: The interpreter has reached the EOS point.");
	}
	return 1;
}