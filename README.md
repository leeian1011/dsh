# DSH

A simple command line tool that lets me "dash" to project directories. 

## The Problem & the Solution

![slowly cd-ls](https://github.com/leeian1011/dsh/blob/fastlane/imgandgif/problemgif.gif)
> Look at this can you even watch till the end ??

![superfastquickafdsh](https://github.com/leeian1011/dsh/blob/fastlane/imgandgif/solutiongif.gif)
> Now look at this DSHHHHHHHHH

## Notes

Currently still a W.I.P and my peanut sized brain couldnt figure out that cd was a shell-specific built-in function.
To run the program you'll need to export the directory path to the PATH environment variable and also include the shell function below

```bash
dsh(){
    operate=$1
    position=$2
    if [[ $operate < 5 ]]; then
        directory=$(dasher $operate)
        if [[ $? == 0 ]]; then
            cd $directory
        fi
    else
        dasher $operate $position
    fi
}
```
Hopefully I'll learn how to make install scripts soon :D
