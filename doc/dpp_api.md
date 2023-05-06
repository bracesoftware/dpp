# Third-party API
- An application programming interface; or API in short; is a way for two or more computer programs to communicate with each other. It is a type of software interface, offering a service to other pieces of software. In D++, you can import a built-in API such as `discord`, `mysql` and such.

---------------------------------------------------------------------------------------------------------

## API: `discord`
- Provides tools for Discord bot development.

Import the API using:
```pawn
import::api.discord;
```

### Form: `discord_bot_send_message`
- Equivalent to `DCC_SendChannelMessage` in Pawn.
```pawn
using::discord.discord_bot_send_message,01234567890,"Message";
```

---------------------------------------------------------------------------------------------------------

### Automated user form: `discord_init`

- Called when the Discord bot loads.

```pawn
auto&form.discord_init;
do;
	using::discord.discord_bot_send_message,01234567890,"Message";
	return.int,1;
end;
```


---------------------------------------------------------------------------------------------------------