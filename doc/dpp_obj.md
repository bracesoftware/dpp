# Objects

- Objects in D++ are simple little tags that you can mark variables with.

> ***NOTE***: Objects have no use right now.

## Example

- Assigning a `TestObj` object to a variable.

```pawn
object,TestObj;
TestObj<-new.int,testvar=10;
```

## Example `#2`

- Objects inside classes.

```pawn
public&class.ObjectTest;
<;
	object,TestObj;
>;

ObjectTest:TestObj<-new.int,testvar=1;
```