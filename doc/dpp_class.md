# Classes
- Class in D++ is a block of code which can contain elements such as constants, variables and forms.

There are standard classes and hook classes.

## Standard class

- A normal class with a normal purpose.

```pawn
public&class.customer;
class.end;
```

Within the class code block, we can create a variable.

```pawn
public&class.customer;
	var::define.str,name,"Alex";
class.end;
```

To use this variable, we need to include the class name within the variable name; like this:

```pawn
using::console.println,customer:name;
```

---------------------------------------------------------------------------------------------------------

## Hook classes
- You can also hook a class. For example, this is our code right now:

```pawn
public&class.customer;
	var::define.str,name,"Alex";
class.end;

using::console.println,customer:name;

```

We can hook the `customer` class:

```pawn
public&class.customer;
	var::define.str,name,"Alex";
class.end;

using::console.println,customer:name;

hook&class.customer;
	var::define.int,age,12;
class.end

using::console.cout,customer:age;
```