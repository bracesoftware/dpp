# Interpreter options
You can modify some interpreter options using `pragma::option`. You may use `default` instead of `true` and `false` in order to reset the value to its default one.

## `debug`
- Default value: `false`

You can toggle D++ debugging on or off.

```pawn
pragma::option.debug,false;
pragma::option.debug,true;
```

## `warnings`
- Default value: `true`

You can toggle D++ warning system on or off.

```pawn
pragma::option.warnings,false;
pragma::option.warnings,true;
```

## `hooking`
- Default value: `true`

You can toggle D++ hooking system on or off.

```pawn
pragma::option.hooking,false;
pragma::option.hooking,true;
```
