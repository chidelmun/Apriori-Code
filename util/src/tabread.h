/*----------------------------------------------------------------------
  File    : tabread.h
  Contents: table reader management

----------------------------------------------------------------------*/
#ifndef __TABREAD__
#define __TABREAD__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------
  Preprocessor Definitions
----------------------------------------------------------------------*/
#define CCHAR   const char      /* abbreviation */

/* --- character flags --- */
#define TRD_RECSEP    0x01      /* flag for record separator */
#define TRD_FLDSEP    0x02      /* flag for field separator */
#define TRD_BLANK     0x04      /* flag for blank character */
#define TRD_NULL      0x08      /* flag for null value characters */
#define TRD_COMMENT   0x10      /* flag for comment character */
#define TRD_OTHER     0x20      /* flag for other character type */
#define TRD_ADD     0x8000      /* flag for adding characters */

/* --- delimiter types --- */
#define TRD_ERR         -2      /* error indicator */
#define TRD_EOF         -1      /* end of file delimiter */
#define TRD_FLD          0      /* field  delimiter */
#define TRD_REC          1      /* record delimiter */

/* --- buffer size --- */
#define TRD_BUFSIZE  65536      /* size of internal read buffer */
#define TRD_MAXLEN    1024      /* maximum length of a field */

#define TRD_FPOS(r)  trd_name(r), trd_rec(r), trd_pos(r)
#define TRD_INFO(r)  trd_name(r), trd_rec(r), trd_pos(r), trd_field(r)

/*----------------------------------------------------------------------
  Type Definitions
----------------------------------------------------------------------*/
typedef struct {                /* --- table reader --- */
  FILE   *file;                 /* file to read from */
  CCHAR  *name;                 /* name of the input file */
  int    last;                  /* last character read */
  int    delim;                 /* last delimiter read */
  size_t len;                   /* number of characters read */
  size_t rec;                   /* number of current record */
  size_t pos;                   /* number of current field */
  char   *next;                 /* next character to read */
  char   *end;                  /* current end of the buffer */
  int    flags[256];            /* character flags */
  char   field[TRD_MAXLEN+4];   /* current field */
  char   buf  [TRD_BUFSIZE];    /* read buffer */
} TABREAD;                      /* (table reader) */

/*----------------------------------------------------------------------
  Functions
----------------------------------------------------------------------*/
extern TABREAD* trd_create (void);
extern int      trd_delete (TABREAD *trd, int close);
extern int      trd_open   (TABREAD *trd, FILE *file, CCHAR *name);
extern int      trd_close  (TABREAD *trd);
extern FILE*    trd_file   (TABREAD *trd);
extern CCHAR*   trd_name   (TABREAD *trd);

extern void     trd_chars  (TABREAD *trd, int type, const char *chars);
extern void     trd_allchs (TABREAD *trd,        const char *recseps,
                            const char *fldseps, const char *blanks,
                            const char *nullchs, const char *comment);
extern void     trd_copy   (TABREAD *dst, const TABREAD *src);
extern int      trd_istype (const TABREAD *trd, int c, int type);
extern int      trd_type   (const TABREAD *trd, int c);

extern int      trd_getc   (TABREAD *trd);
extern int      trd_ungetc (TABREAD *trd, int c);

extern int      trd_read   (TABREAD *trd);
extern char*    trd_field  (TABREAD *trd);
extern size_t   trd_len    (TABREAD *trd);
extern int      trd_last   (TABREAD *trd);
extern int      trd_delim  (TABREAD *trd);
extern size_t   trd_rec    (TABREAD *trd);
extern size_t   trd_pos    (TABREAD *trd);

/*----------------------------------------------------------------------
  Preprocessor Definitions
----------------------------------------------------------------------*/
#define trd_file(r)        ((r)->file)
#define trd_name(r)        ((r)->name)

#define trd_copy(d,s)      memcpy((d)->flags, (s)->flags, \
                                       sizeof((s)->flags))
#define trd_istype(r,c,t)  ((r)->flags[(unsigned char)(c)] & (t))
#define trd_type(r,c)      ((r)->flags[(unsigned char)(c)])

#define trd_field(r)       ((r)->field)
#define trd_len(r)         ((r)->len)
#define trd_last(r)        ((r)->last)
#define trd_delim(r)       ((r)->delim)
#define trd_rec(r)         ((r)->rec -(((r)->delim == TRD_REC) ? 1 : 0))
#define trd_pos(r)         ((r)->pos)

#endif  /* #ifdef __TABREAD__ */
