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

#define DPP_VERSION_MAJOR 0
#define DPP_VERSION_MINOR 0
#define DPP_VERSION_PATCH 1
#define DPP_VERSION_RELEASE 1

#define dpp_execheader%0(%1) print("|====================| "%1" |====================|")
#define dpp_comment%0(%1) print("|==============================================|")
#define dpp_nullcomment%1(%1) print("                                               ")
#define dpp_print%0(%1) printf(">> D++ | INFO: "%1)
#if DPP_DEBUG == 1
#define dpp_debug%0(%1) printf(">> D++ | DEBUG: "%1)
#elseif DPP_DEBUG == 0
#define dpp_debug%0(%1)%2;
#endif
#define dpp_error%0(%1) printf(">> D++ | ERROR: "%1)
#define dpp_warning%0(%1) printf(">> D++ | WARNING: "%1)

stock dpp_parsecode(const code[], destln[][])
{
	new 
		i, 
		start,
		index,
		len;

	while(i <= strlen(code))
	{
		if(code[i] == ';' || i == strlen(code))
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

new content[16000];

stock dpp_execute()
{
	dpp_print("Interpreter version %i.%i.%i-R%i - by: DEntisT",DPP_VERSION_MAJOR,DPP_VERSION_MINOR,DPP_VERSION_PATCH,DPP_VERSION_RELEASE);
	dpp_print("Executing the entry script...");
	dpp_nullcomment();
	dpp_execheader("script.dpp");
	dpp_nullcomment();
	new File:file = fopen("script.dpp", io_read), rlen;
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
			dpp_parsecode(content, codelines);
			//dpp_debug("Executing:\n\n%s", content);
			for(new i; i < 1024; i++)
			{
				dpp_process(codelines[i]);
			}
		}
	}
	else if(!file)
	{
		dpp_error("Invalid file.");
	}
	dpp_nullcomment();
	dpp_comment();
	dpp_nullcomment();
	dpp_print("The interpreter reached the EOS point.");
	return 1;
}