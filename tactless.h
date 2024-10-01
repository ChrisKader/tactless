#ifndef TACTLESS_H_
#define TACTLESS_H_

struct tactless;
typedef struct tactless tactless;

tactless *tactless_open(const char *product);
void tactless_close(tactless *t);
void tactless_dump(const tactless *t);

#endif
