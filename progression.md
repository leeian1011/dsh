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

3. Add commands, Minor issues here, quickly realized that the previous way of handling of "adding a lane" was to pipe the output of pwd and immediately use `append()`.
This meant that the position of the lane would be assigned when appending, this makes it impossible to assign a missing index.

> An example of the issue

```C
int append(list *dasher, char *directory){
    list *newLane = malloc(sizeof(list));
    ...
    list *iterator = dasher;
    ...
    newLane->position = iterator->position + 1;

    ...
}
```
The code above means that the appended newLane would always have a position of > 1. If there were existing lanes, 4, 2 , 0, 1. It would append lane 5 rather than lane 3.

- Ended up refactoring append to accept the address of a list to be appended, `append(list **dasher, list **newLane)` and assign newLane in the `add_command(list **dasher)`.

- Set restriction where iF `MAX_LANES` number of lanes have been set it would not add a new lane.

4. TINY BRAIN MOMENT

**SO** my peanut sized brain just spent half an hour trying to figure out how to get dsh to execute and change the directory of the current parent shell. I went down a
minor rabbit hole and learned a whole bunch about how the shell actually works.

- Its a program that lets use interface with the kernel of the OS.

This is where I learned about a tiny little thing that somehow never came to me. SUBPROCESSES OR CHILD SHELL.
Everytime I run dsh from the command line or if I had dsh included in the environment PATH variable, the parent shell creates a subprocess, which contains it's own environment.
This meant that everytime I call dsh, I cant force change the current directory in the parent shell. The same applies to shell scripts.

> A temporary workaround to this was just literally typing `cd $(dsh x)`, where x is the lane position, and also modifying dsh to simply print to stdout, the directory saved.

This isnt a very elegant fix, there are many issues with it, whereby, if position x does not exist, cd would change the directory to the home directory.

- Learned about shell function, that lets commands be ran in the current instance of the shell but can only be declared in the rc file.

- Learned quite a lot about how shells work and a lot more about pipe and file descriptors, like how printing to the subshell's stdout prints to the parent shell's stdout because
the subshell has the exact same file descriptor. And also why the parent shell has to call fork/clone in order to use exec* to oopen external programs.
If it doesn't it defeats the purpose because the exec system call essentially overwrites the parent shell "program" with the just called exec'd program.

- Currently using a simply shell function to get intended behaviour with the program!, will continue to learn more and try figuring out how to make installations.


