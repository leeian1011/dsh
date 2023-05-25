Issue with assigning dasher (the node) to new instance of another node after initializing the new instance.

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

