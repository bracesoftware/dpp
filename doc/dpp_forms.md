# Forms
- Functions in programming are blocks of precisely defined and chronologically ordered instructions that are executed when the function is called. In D++, those are renamed to forms.

- Forms may be native forms, user forms and hook forms.

---------------------------------------------------------------------------------------------------------

## Native forms

- Native forms are those whose are defined in an interpreter component and are useable only if the component is imported. You may call native forms using the `using` keyword.

```pawn
import::component.console;
using::console.println,"Hello World";
```

So you are using the `using` procedure on a `console` component to use the `println` form - brilliant!


### Registering native forms from certain APIs

- To use a certain native form which is built into an API component, you'd need to register it; so for example if you wanted to use the `discord_bot_send_message` which is built into the `discord` API system, you need to register it like this:

```pawn
native&form.discord_bot_send_message;
```

---------------------------------------------------------------------------------------------------------

## User forms

- User forms are forms whose are defined by the person who wrote the code. You may declare an user form using:

```pawn
public&form.formname;
do;
	using::console.println,"my first user form";
end;
```

So now you've made an user form. Code between the `do` and `end` keywords is called a form code block. It may contain a native form call, or another user form declaration.

You also may return values.

```pawn
public&form.formname;
do;
	using::console.println,"my first user form";
	return.str,"this was returned";
end;
```

Then you can use this user form as an argument in a native form.

```pawn
public&form.formname;
do;
	using::console.println,"my first user form";
	return.str,"this was returned";
end;

using::console.println,formname;
```

To call an user form, use:

```pawn
using::user.formname;
```

---------------------------------------------------------------------------------------------------------

## Using vars and constants as arguments

- You may also use variables and constants as arguments in native functions.

```pawn
const::define.str,CONST_NAME,"constant worked";

using::console.println,CONST_NAME;
```

---------------------------------------------------------------------------------------------------------

## Hook forms
- You can hook already existing forms using **hook forms**.

```pawn
public&form.functobehooked;
do;
	using::console.println,"HOOKED";
	return.int,1;
end;

hook&form.functobehooked;
do;
	using::console.println,"HOOKED 1";
	return.int,1;
end;

hook&form.functobehooked;
do;
	using::console.println,"HOOKED 2";
	return.int,1;
end;

using::user.functobehooked;
```