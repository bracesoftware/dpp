# Passing arguments to user forms

```pawn
public&form.form?text&num;
do;
	using::console.println,text@form;
	using::console.cout,num@form;
end;

using::user.form,"text",1;
```