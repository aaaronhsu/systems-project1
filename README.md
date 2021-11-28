# Shell Implementation


## Features
- Run commands one at a time
- Run commands separated by ` ;`
  - There must be a space before the semicolon
- Redirection using `>` and `<`
  - You cannot use them together in the same command (yet)
- Piping using `|`
  - You can only pipe two commands together
  - You cannot use them with `>` or `<` (yet)

---

## Random Notes
- Redirection
  - After creating the `args` array for a command input, scan for `>` and `<`
    - If `>`, take the argument before the `>` and store it in a file using `dup2(file_name, 1);`
    - Execute as normal
    - If `<`, do the same thing but take the argument after the `<` and use `dup2(file_name, 0);`