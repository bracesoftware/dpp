# Classes
- Class in D++ is a block of code which can contain elements such as constants, variables and forms.

There are standard classes and hook classes.

## Standard class

- A normal class with a normal purpose.

```pawn
public&class.customer;
do;
end;
```

Within the class code block, we can create a variable.

```pawn
public&class.customer;
do;
	var::define.str,name,"Alex";
end;
```

To use this variable, we need to include the class name within the variable name; like this:

```pawn
console.println,customer:name;
```

---------------------------------------------------------------------------------------------------------

## Hook classes
- You can also hook a class. For example, this is our code right now:

```pawn
public&class.customer;
do;
	var::define.str,name,"Alex";
end;

console.println,customer:name;

```

We can hook the `customer` class:

```pawn
public&class.customer;
do;
	var::define.str,name,"Alex";
end;

console.println,customer:name;

hook&class.customer;
do;
	var::define.int,age,12;
end;

console.cout,customer:age;
```