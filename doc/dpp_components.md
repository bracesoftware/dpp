# Interpreter components
- To use certain *native forms*, you need to import standard built-in components into your code. For example - to use `cout`, you need to have a `console` interpreter component imported. Below, you can find the full list of available components.

## Components `console`
- Provides console-related functions.

Import the component using:
```pawn
```

### `cout`
- Character output.

```pawn
using::console.cout,"some words.";
```

## Package `system`
- Provides random, usually internal, functions.

### `rem`
- Comments.
```pawn
using::system.rem,"SOME TEXT";
```
