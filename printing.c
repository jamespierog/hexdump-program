#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void usage(char *prog) {
  fprintf(stderr, "Usage: %s INPUT_FILENAME OUTPUT_FILENAME\n", prog);
}

int main(int argc, char **argv) {

  // Preliminary checks for command line arguments
  if (argc < 2) {
    fprintf(stderr, "%s: missing input filename\n", argv[0]);
    usage(argv[0]);
    return 1;
  }

  if (argc > 3) {
    fprintf(stderr, "%s: too many arguments\n", argv[0]);
    usage(argv[0]);
    return 1;
  }

  FILE * fp_input;
  FILE * fp_output;
  int c;
  int bitcount = 0;
  char str[17] = "";
  int i = 0;

  // Read files for input and output
  fp_input = fopen(argv[1], "r");
  fp_output = fopen(argv[2], "w+");

  fprintf(fp_output, "%08x  ", bitcount);

  c = getc(fp_input);

  while (c != EOF) {
    // Checks whether to make a new line b/c 16 bits have been read
    if ((bitcount != 0) && (bitcount % 16 == 0)) {
      putc('\n', fp_output);
      fprintf(fp_output, "%08x  ", bitcount);
      i = 0;
    }

    // Increment the bitcount up b/c new bit is read this round
    bitcount = bitcount + 1;

    // Print the hex representation of a bit && add a space
    fprintf(fp_output, "%02x ", c);

    // Check if char is printable and add it to char array to print later
    if (isprint(c) == 1) {
      *(str+i) = c;
    } else {
      *(str+i) = '.';
    }

    // Print the string if it is bitcount == 16
    if ((bitcount != 0) && (bitcount % 16 == 0)) {
      // Print out the regular ASCII string representation with char array
      fprintf(fp_output, " |%s|", str);
    }

    c = getc(fp_input);
    i = i + 1;
  }

  // Print out the ASCII string representation
  if (i % 16 == 0) {
    fprintf(fp_output, " |%s|", str);
  } else {
    int k;
    for(k = i; k < 17; k = k + 1) {
    *(str+k) = '\0';
    }

    for (k=i; k < 16; k = k+1) {
      fprintf(fp_output, "   ");
    }
    fprintf(fp_output, " |%s|", str);
  }

  fclose(fp_input);
  fclose(fp_output);

  return 0;
}
