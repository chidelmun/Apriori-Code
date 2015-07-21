/*----------------------------------------------------------------------
  File    : escape.h
  Contents: escape character handling

----------------------------------------------------------------------*/
#ifndef __ESCAPE__
#define __ESCAPE__
#include <stddef.h>

/*----------------------------------------------------------------------
  Constants
----------------------------------------------------------------------*/
extern const char* esc_map[256];

/*----------------------------------------------------------------------
  Functions
----------------------------------------------------------------------*/
extern const char* esc_encode (int c);
extern int         esc_decode (const char *s, char **end);

extern size_t      esc_enclen (const char *s);
extern size_t      esc_encstr (char *dst, const char *src);
extern size_t      esc_decstr (char *dst, const char *src);

/*----------------------------------------------------------------------
  Preprocessor Definitions
----------------------------------------------------------------------*/
#define esc_encode(c)   (esc_map[c])

#endif
