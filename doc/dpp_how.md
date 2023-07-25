# How does D++ work?

## Introduction

- D++ is a small interpreted language written in Pawn. It is designed with the role of enabling modification of the gamemode code on the server during run-time. It contains various features and things that aren't even introduced into Pawn itself. D++ has a very complex syntax which makes it very hard to learn but also fragile to small mistakes.

### Writing code

- Similar to other types to frameworks, D++ has its own entry file path, and it is `scriptfiles/index.dpp`. In order to start coding in D++, you need to create your very first `index.dpp` and begin your journey!

#### `Hello World!`

- Writing a small "hello world" program is the initial step of anyone trying to learn a new language, so that's how we'll start this one as well. Open your `index.dpp` and write in the following code.

`index.dpp`:
```cpp
using.console;
```

- This line will enable the use of an integrated component called "console". Console component provides forms and functions you can use for character output. If we did not enable the component, we'd run into an error.

- Now, to print our destined message, we'll use the `println` form (function).

`index.dpp`:
```cpp
using.console;

console.println("Hello World!");
```

- What we did here is basically call the `console` component and provided a function name next to the component call. That function is `println` which literally stands for "print line". Group of words separated by a semicolon (`;`) is called a **statement**. Adding a comma, we started an **argument part** of the statement. Argument part of a statement consists of some kind of resources we have use of when it comes to executing code.

- As you can see, our first argument is `"Hello World"` - which is a string, and since we provided this argument to the `console.println` function, contents of that argument will be displayed in the console.

### Running code 

- Now that we got our very first D++ program, we can run our server. You firstly need to configure your server by setting the D++ build as your server gamemode, you can learn how to do it [here](https://google.com). 

- Now after running your server you will see the following output in the console.

```
Hello World!
```

- And that's it, you've made your own D++ program. To learn more about D++ possibilities and other functions, head over to the home page and explore the language section, but if you want to stay and learn more on how D++ works itself, grab your popcorn! 

## D++ compiler

- D++ is, as you saw, an interpreted language, which means that the D++ interpreter is reading the `index.dpp` source code and executes things accordingly.

- But, there is more than that, D++ build contains the integrated compiler function which is useful when dealing with modules, but if you've got a monolitic script, you don't really need to worry about this section.

- The thing that the D++ compiler actually does is that it reads the code from the entry-file and the imported modules and then copies it all into a single `index.dppc` file - which literally translates to "D++ index compiled".

- Of course there is much more underlying code behind this, but it is basically it.

## D++ interpreter

- Unlike compiler's simplicity, interpreter itself is the core part. The interpreter is responsible for opening the compiled file, reading its contents and executing functions. Reading functions is enabled because of the so-called parsing system. The parsing system makes it possible to read a certain line and break it down into groups of keywords and arguments, according to which further processing of information is carried out. Below, there is a simple example which is explaining this.

- Let this be our code:

`index.dpp`:
```cpp
using.console;

console.println("Hello World!");
```

- Interpreter is firstly going to read the first line. Afterwards, the semicolon will be removed and the internal process-function will be called:

```cpp
main() dpp_process("using.console");
```

- Of course this is a simplified depiction. The thing that `dpp_process` does is that it calls `dpp_parseline` which breaks down the line into so-called groups, so internally it will look like this after the break-down.

```
funcgroup[0] = "using"
funcgroup[1] = "console"
```

- Now `dpp_process` will pass the groups with their contents on until the function ends. Basically, the processor is full of if-checks which execute the remaining code accordingly.

- So this is how it looks simplified:

```cpp
dpp_process(line)
{
	dpp_parseline(line,funcgroup,'.');

	if(funcgroup[0] == "using")
	{
		if(funcgroup[1] == "console")
		{
			dpp_enablesamp();
			return 1;
		}
	}
}
```

- But when it comes to function calls, then it is way more complicated, there are now also arg-groups.

```cpp
dpp_process(line)
{
	dpp_parseline(line,funcgroup,'.');
	dpp_parseline(funcgroup,args,',');

	if(funcgroup[0] == "console")
	{
		if(funcgroup[1] == "println")
		{
			if(dpp_isstring(arg[1]))
			{
				dpp_processconsole(funcgroup,args);
			}
			return 1;
		}
	}
}
```

- But if you want to experience it the full-HD (this function has around 2 thousand lines without all the integrated components), then feel free to check out the `dpp_modules/dpp_interpreter` file.

- If you have any more questions, feel free to contact me on Discord on [SAMPIKS server](https://discord.gg/2KyPR4BQ5a). 