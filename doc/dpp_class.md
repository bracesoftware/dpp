# Classes
- Class in D++ is a block of code which can contain elements such as constants, variables and forms.

There are standard classes and hook classes.

## Standard class

- A normal class with a normal purpose.

```pawn
public&class.customer;
<;
>;
```

Within the class code block, we can create a variable.

```pawn
public&class.customer;
<;
	new.str,name="Alex";
>;
```

To use this variable, we need to include the class name within the variable name; like this:

```pawn
console.println(customer:name);
```

---------------------------------------------------------------------------------------------------------

## Hook classes
- You can also hook a class. For example, this is our code right now:

```pawn
public&class.customer;
<;
	new.str,name="Alex";
>;

console.println(customer:name);

```

We can hook the `customer` class:

```pawn
public&class.customer;
<;
	new.str,name="Alex";
>;

console.println(customer:name);

hook&class.customer;
<;
	new.int,age=12;
>;

console.cout(customer:age);
```