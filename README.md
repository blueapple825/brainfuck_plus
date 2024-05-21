# brainfuck plus

brainfuck with miscellaneous features added

## build

windows & linux

```
make
```

## run

linux

```
./bfp <file path>
```

windows
```
bfp.exe <file path>
```

## command

`>` - Increase pointer

`<` - Decrease pointer

`^` - Push the pointer value onto the stack

`~` - Pop the pointer value from the stack

`+` - Increase the value pointed by the pointer

`-` - Decrease the value pointed by the pointer

`.` - Output the value pointed by the pointer

`,` - Receive input at the location pointed by the pointer

`[` - Start of loop, end loop if the value pointed by the pointer is 0

`]` - End of loop, move to the start of the loop

`*` - Change the pointer to the value currently pointed by the pointer

`{name}[code]` - Define subroutine

`!{name}` - Call subroutine

`name` - Characters with ASCII codes ranging from 33 to 64 when converted (up to 32 characters)
