#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tactless.h"

static int dump_encoding(const unsigned char *text, size_t size) {
  struct tactless_encoding e;
  if (!tactless_encoding_parse(text, size, &e)) {
    fputs("parse error\n", stderr);
    return 0;
  }
  tactless_encoding_dump(&e);
  tactless_encoding_free(&e);
  return 1;
}

static int dump(const char *type, const char *filename) {
  size_t size;
  unsigned char *text = tactless_readfile(filename, &size);
  if (!text) {
    return 0;
  }
  int ret = 1;
  if (strcmp(type, "encoding") == 0) {
    ret = dump_encoding(text, size);
  } else {
    fputs("invalid type\n", stderr);
    ret = 0;
  }
  free(text);
  return ret;
}

int main(int argc, char **argv) {
  if (argc == 4 && strcmp(argv[1], "dump") == 0) {
    return dump(argv[2], argv[3]) ? EXIT_SUCCESS : EXIT_FAILURE;
  }
  if (argc != 2) {
    fputs("usage: tactless product\n", stderr);
    return EXIT_FAILURE;
  }
  tactless *t = tactless_open(argv[1]);
  if (!t) {
    fputs("error opening tactless\n", stderr);
    return EXIT_FAILURE;
  }
  tactless_dump(t);
  tactless_close(t);
  return EXIT_SUCCESS;
}
