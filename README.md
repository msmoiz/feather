# Feather

Feather is a lightweight text editor written in less than 600 lines of code (counted with [cloc](https://github.com/AlDanial/cloc)).

Usage: `feather <filename>`

Keys:

```shell
CTRL-S: Save
ESC: Quit
```

Feather does not depend on any libraries (except [Catch](https://github.com/catchorg/Catch2) for testing) and employs virtual terminal sequences to handle input and render output. It currently supports Windows only. The project was written over the course of a few days and was a good exercise in console manipulation, test-driven development, and architectural design.
