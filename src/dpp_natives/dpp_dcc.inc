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


// Used by d++ itself
#define DCC_INVALID_CHANNEL DCC_Channel:0
native DCC_Channel:DCC_FindChannelById(const channel_id[]);

// Implemented in d++
native DCC_SendChannelMessage(DCC_Channel:channel, const message[], const callback[] = "", const format[] = "", {Float, _}:...);