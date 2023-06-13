# DSH
Dashing you to wherever you need to be (in the cli).

## -> The Problem

- Have you ever felt like ls and cd-ing in the shell took too much time even though its mostly muscle memory?
You're working on one project and would like to jump on over to another one without having to trudge through using `cd ..`.

![slowly cd-ls](https://github.com/leeian1011/dsh/blob/fastlane/imgandgif/problemgif.gif)
>slow and steasy I guess.


## -> The solution

- Quick and easy cli tool that lets you hop around saved lanes (up to 5 only).

![superfastquickafdsh](https://github.com/leeian1011/dsh/blob/fastlane/imgandgif/solutiongif.gif)
>DSH-ING THROUGH

## Notes

This is my first project and also my CS50 Final Project!


## Installation

**Important Note: This was made for macBook on arm64 and I havent had the time to compile a separate version for windows**

- Install by using git clone and cloning it into a directory.

- Copy and paste the code below into your .zshrc or .bashrc file and replace "path/to/" with the path directory where you cloned the repo to.

```bash
export DASH_CACHE="path/to/dash/cache/lanes.txt"
export PATH="$PATH:path/to/dash"

dsh(){
    operate=$1
    position=$2
    nextposition=$3

    if [[ $operate < 5 ]]; then
        directory=$(dasher $operate)
        if [[ $? == 0 ]]; then
            cd $directory
        fi
    elif [[ $# -eq 0 ]]; then
        dasher
    else
        dasher $operate $position $nextposition
    fi
}

```

- hopefully I learn how to make my own install scripts soon :p

## All about DSH

1. Lanes & \[lane index]

- Lanes are just the path to directory saved on dsh, while \[lane index] is the position or number mapped to the lane.

2. dsh a

- Simple add function that adds the current working directory, the same path you'd get if you'd inputted pwd into the terminal, to dsh.

- It takes 0 arguments.

3. dsh rm

- Removes a \[lane index] and it's corresponding lane from dsh.

- Removes only 1 \[lane index] at a time.

4. dsh ls 

- Lists all currently saved lanes and their corresponding \[lane index] in ascending order.

5. dsh mv 

- Moves a \[lane index] to a new index.

- If the new index already has a lane attached to it, the command will still run and replace the lane's \[lane index] with the moved \[lane index].

6. dsh \[lane index]

- Changes the current working directory to whatever lane is stored in \[lane index].

> Pretty simple, borderline CRUD application honestly.

## Going through what I learnt and the problems I faced building This

- [Check this out](https://github.com/leeian1011/dsh/blob/fastlane/progression.md)
























