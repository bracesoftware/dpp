# Form structure types

- In D++, there are 2 form structure types, and those are local and external forms.

## Local forms

- Those are basic chunks or blocks of code that are called from D++ internally.

Example:

```pawn
auto&form.OnGameModeInit;
do;
	using::console.println,"Script loaded";
end;
```

## External forms

- External forms are forms that are called when a certain event happens in third-party API; for example, SA-MP commands are external structures or forms that are called when a player uses a command. In short, externally structured forms are and are not forms at the same time. Because external form types are so special, they're only available after including a certain third-party API system or an interpreter component.

### Component `samp`

#### External struct name: `samp_command`

Example:

```pawn
extern&struct*samp_command.testcmd?playerid&params;
do;
	using::samp.SendClientMessage,playerid@testcmd,0,"Your command works!";
	return.int,1;
end;
```