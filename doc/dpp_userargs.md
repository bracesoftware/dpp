# Passing arguments to user forms

```pawn
public&form.form?text&num;
do;
	console.println,text@form;
	console.cout,num@form;
end;

user.form,"text",1;
```