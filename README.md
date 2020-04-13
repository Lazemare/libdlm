# libdlm

libdlm: a tiny library for reading and writing delimited files. The idea of this library comes from `DelimitedFiles.jl` in `Julia` language. This library is not fast, but it's small and easy to use. Me personally use it in some scientific calculation packages, which do not require high IO performance, as part of the input file parser.

## Installation

### Compilation

Simply type `make lib` in the main folder, and the binary files will be located in the `lib` folder.

### Test

Type `make test` in the main folder, then the program will read a delimited file called `txt` under `test` folder, and print results on your screen.

## Usage

You could call two functions from the library:

```C
int readdlm(FILE *fp, char list[MAXLINES][MAXWORDS][MAXLETTERS], char delim, int quotes, int comments, char comment_char);
int writedlm(FILE *fp, char list[MAXLINES][MAXWORDS][MAXLETTERS], char delim);
```
1. `readdlm`
   parameters:
   - `FILE *fp`: the input file stream.

   - `char list[MAXLINES][MAXWORDS][MAXLETTERS]`: where storing the address of the buffer containing the text. `list[i][j]` contains the word in (i+1) row and (j+1) column of `fp`.

   - `char delim`: the delimiter.

   - `int quotes`: if this parameter equals to 0, all characters between two quotes will be treated as one string.

   - `int comments`: if this parameter equals to 0, lines beginning with `comment_char` and text following `comment_char` in any line are ignored.

   - `char comment_char`: the character indicates that characters after that are comments.

   return value: number of total words in the input file.
2. `writedlm`
   - `FILE *fp`: the output file stream.
   - `char list[MAXLINES][MAXWORDS][MAXLETTERS]`: same as this parameter in `readdlm`.
   - `char delim`: will write output file with this delimiter.
   return value: number of total words has been written.

I defined three macros called `MAXLINES`, `MAXWORDS` and `MAXLETTERS` in the header file, which control the maximum file size. You may want to change them depending on your tasks. According to different OS, you should also adjust the `EOL` macro, since files under Linux, macOS and windows use different EOL. For detailed usages, you may want to look into the `main.c` file under `test` folder.
