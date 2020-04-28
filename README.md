# libdlm

libdlm: a tiny library for reading and writing delimited files. The idea of this library comes from `DelimitedFiles.jl` in `Julia` language. This library is not fast, but it's small and easy to use. Me personally use it in some scientific calculation packages, which do not require high IO performance, as part of the input file parser.

## Installation

### Compilation

Simply type `make lib` in the `src` folder, and the binary files will be located in the `lib` folder.

### Test

Type `make test` in the `src` folder, then the program will read a delimited file called `txt` under `test` folder, then writes outputs to a file called `out` in the same folder.

## Usage

### Structure

The header file `delimitedfiles.h` defines the struct used to record information of the delimited file, namely `DLM`. There are three members in it:

- `int linenum`: line number of the delimited file.

- `int wordnum`: total word number of the delimited file.

- `char ***list`: storing the address of the buffer containing the text. `list[i][j]` contains the word in (i+1) row and (j+1) column of the delimited file.

### Functions

You could call four functions from the library:

```C
void init_dlm(struct DLM *dlm);
void free_dlm(struct DLM *dlm);
void readdlm(FILE *fp, struct DLM *dlm, char delim, int quotes, int comments, char comment_char);
int writedlm(FILE *fp, struct DLM *dlm, char delim);
```

1. `init_dlm`:

   Before reading from or writing to the delimited file, you should first initialize a `DLM` struct by:

   ```C
   struct DLM dlm;
   init_dlm(&dlm);
   ```

2. `free_dlm`:

   After the struct finished its job, you can free the memory by:

   ```C
   free_dlm(&dlm);
   ```

3. `readdlm`:

   parameters:

   - `FILE *fp`: the input file stream.

   - `struct DLM *dlm`: address of a `DLM` struct.

   - `char delim`: the delimiter.

   - `int quotes`: if this parameter equals to 0, all characters between two quotes will be treated as one string.

   - `int comments`: if this parameter equals to 0, lines beginning with `comment_char` and text following `comment_char` in any line are ignored.

   - `char comment_char`: the character indicates that characters after that are comments.

4. `writedlm`:

   parameters:

   - `FILE *fp`: the output file stream.
   
   - `struct DLM *dlm`: address of a `DLM` struct.
   
   - `char delim`: will write output file with this delimiter.
   
   return value: number of words that has been written.

-----

The header file contains three macros called `MAXLINES`, `MAXWORDS` and `MAXLETTERS`, which control the maximum file size. You may want to change them depending on your tasks. According to different OS, you should also adjust the `EOL` macro, since files under Linux, macOS and windows use different EOL. For more detailed usages, you may want to look into the `main.c` file under `test` folder.
