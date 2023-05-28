1. Issue with assigning dasher (the node) to new instance of another node after initializing the new instance.

- found out that functions in C always makes a copy of the variables passed in as arguments. I thought this "pass by value" only applied to non pointer variables.
- to ensure that we are modifying the original variables we will have to pass in the memory address of the variable (be it pointer or non pointer variable).

- in this case what the issue was just happens to be that a copy of the pointer variable, `list *dasher` was being used and modified in the `append()` function.
to solve this we just have to make sure that the `append()` function accepts a pointer to the pointer variable or, `append(list **dasher)`.

> a rough idea of the err in my code before i found the solution

```C
int append(list *dasher){
    list *newLane = malloc(sizeof(list));
    ...

    newLane->position = 0;
    ...
    
    dasher = newLane;       //dasher here is a copy of the passed in argument rather than the original dasher.
    return 0;
}
```
2. Option handlings, to be honest I took some inspiration from tmux's open source code. I find out that theres this little helpful POSIX library called getopt.h,
I had used it in CS50 but it didnt really cross my mind. I tried reading the [openBSD](https://github.com/openbsd/src/blob/master/lib/libc/stdlib/getopt_long.c)
and the [GNU](https://github.com/gcc-mirror/gcc/blob/master/libiberty/getopt.c) versions of `getopt()` and I just cannot wrap my pea-sized brain around the code I was reading..
Ultimately decided to make my own option handling just to see how hard it would be to parse argvs, using `getopt()` could've saved me time but I can barely understand the inner
workings on it, and I just really really wanted to make everything from scratch to learn!

> ignore the fact that i use the <string.h> library everywhere despite claiming I want to make everything from scratch

The function or library(? I'm not sure what to call it), isnt as functional as `getopt()` but my program is pretty small and has like barely any commands
the intended behaviour is displayed and thats all well! (Until it isn't)

- tried reading open source code could barely understand but this just motivates me more, one day I'd be able to actually read Open Source code and really understand!

- very important I learned that `*argv[x]` (or any double pointer really) does not "derefence first, index into second", but rather it "dereferences twice", so instead of
"dereference the pointer and look at the next memory address the pointer points to" it does "get the \[x\]-th pointer and dereference it". The intended behaviour was to
dereference the pointer to a pointer, and index into the pointer's memory array.

> (*argv)\[1], "(*argv)" occurs first before indexing, "\[1]" occurs.

- What ended up happening was just dereferencing into the \[x\]-th pointer, and dereferencing that pointer to it's first memory location.

> *argv[1], "argv[1]" occurs first, effectively dereferencing the pointer to a pointer, then "*argv" occurs, further dereferencing into the first memory location.

- This second behaviour results in reading a `char` datatype representing the first memory location of the char *array, which is not what we want!

- This basically happens because indexing into an pointer using array takes precedence over dereferencing a pointer.
"
