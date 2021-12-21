# Compiler for Java-like language Decaf
## Overview
  - Converts decaf source code into JVM assembly instructions
  - Four stages of compiling
    1. Lexing: Chop source code into identifiable pieces
    2. Parsing: Parse pieces into tree for semantic analysis
    3. Semantics: Ensure code is semantically correct
    4. Code Generation: Create JVM assembly so it can run in the JVM
  - Full implementation of Decaf language
## Requirements for compiling
  - g++ compiler
  - Flex: for lexing
  - Bison: for parsing
### Decaf Specification in decafOverview.pdf
