# Mininshell

The objective of this project is to create a simple version of shell, similar to bash. This project is done with [Ojing Ha](https://github.com/hanzong111). This program is capable to handle command in both Absolute `(/bin/ls)` and relative path `(ls)`. The program also support redirections `(>, <, >>, <<)` and pipe `(|)`

# How To use
Use `make` to create executable and run `./minishell`. Make sure you have the readline library installed

# Credit

I was responsible for creating lexer and parser, handling of signal and parts of built in function.
Hanz was responsible in creating the executer, handle redirection and pipe and the parts of built in functions.

