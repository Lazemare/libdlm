# libdlm

Libdlm is a tiny library for reading and writing delimited files. The idea of this library comes from `DelimitedFiles.jl` in [`Julia`](https://julialang.org/ "Julia") language. Libdlm is not fast, but it's small and easy to use. Me personally use it in some scientific calculation packages, which do not require high IO performance, as part of the input file parser.

## Installation

### Compilation

Simply type `make lib` in the `src` folder, and the binary files will be located in the `lib` folder.

### Test

Type `make test` in the `src` folder, then the program will read a delimited file called `txt` under `test` folder, then writes outputs to a file called `out` in the same folder.

## Usage

### Type

The header file `delimitedfiles.h` defines the struct used to record information of the delimited file, namely `DLM`. There are three members in it:

- `int linenum`: line number of the delimited file.

- `int *wordnum`: word number of each line in the delimited file.

- `char ***list`: storing the address of the memories that contain the text. `list[i][j]` contains the word in `i+1` row and `j+1` column of the delimited file.

You could use `dlm_t var_name` to initialize a `DLM` struct called `var_name`.

### Functions

You could call three functions from the library:

```C
void readdlm(FILE *fp, struct DLM *dlm, char delim, int quotes, int comments, char comment_char);
int writedlm(FILE *fp, struct DLM *dlm, char delim);
void free_dlm(struct DLM *dlm);
```

1. `readdlm`:

   Read input file stream into a `DLM` struct.

   parameters:

   - `FILE *fp`: the input file stream.

   - `dlm_t *dlm`: address of a `DLM` struct.

   - `char delim`: the delimiter.

   - `int quotes`: if true, all characters between two quotes will be treated as one string.

   - `int comments`: if true, lines beginning with `comment_char` and text after `comment_char` in any line will be ignored.

   - `char comment_char`: the character indicates that characters after that are comments.

2. `writedlm`:

   Write texts in a `DLM` struct to output stream.

   parameters:

   - `FILE *fp`: the output file stream.

   - `dlm_t *dlm`: address of a `DLM` struct.

   - `char delim`: delimiter used to write the output file.

   return value: number of words that has been written.


3. `free_dlm`:

   Free allocated memories in a `DLM` struct.

   parameters:

   - `dlm_t *dlm`: address of a `DLM` struct.

# MISCS

The header file `readdlm.h` contains a macro called `BUFFSIZE`, which is the maximum line length. You may want to change it depending on your tasks. For detailed usages, you may want to look into the `main.c` file under `test` folder.
