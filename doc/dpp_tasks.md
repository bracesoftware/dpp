# Tasks

- Tasks in D++ are specific chunks of code that are being called every certain period of time.


```pawn
public&task.testtask#1000;
task.do;
	using::console.println,"Task works!";
task.end;
```

Code above will print `Task works!` every 1 second. It is also really important to note that tasks are VERY different from forms and cannot return any values. 

Tasks also can be only stopped using `exit;` which terminates everything else as well.