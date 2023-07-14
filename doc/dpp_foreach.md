# Foreach-loop and iterators

- In computer programming, an iterator is an object that enables a programmer to traverse a container, particularly lists - whereas a foreach loop (or for-each loop) is a control flow statement for traversing items in a collection. 

## Example

```pawn
iter::define,testiter,100;
var::define.int,foreachtestvar,0;

iter::add,testiter,1;
iter::add,testiter,10;
iter::remove,testiter,1;

foreach.int&var,foreachtestvar,testiter->using::console.println,"foreach test {foreachtestvar}";

iter::add,testiter,1;

foreach.int&var,foreachtestvar,testiter->using::console.println,"foreach test #2 {foreachtestvar}";

iter::delete,testiter;
```

Output:

```
foreach test 10
foreach test #2 1
foreach test #2 10
```

## `sizeof` instruction

- `sizeof` is a keyword you may have seen in a huge variety of programming languages. In D++, `sizeof` is by-default enabled instruction which returns the size of an iterator.


```pawn
using::console.cout,sizeof?testiter;
```

Output:

```
100
```