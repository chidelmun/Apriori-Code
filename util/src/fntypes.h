/*----------------------------------------------------------------------
  File    : fntypes.h
  Contents: definition of some common function types

----------------------------------------------------------------------*/
#ifndef __FNTYPES__
#define __FNTYPES__

typedef void   OBJFN  (void *obj);
typedef size_t SIZEFN (const void *obj);
typedef int    CMPFN  (const void *p1, const void *p2, void *data);
typedef double RANDFN (void);

#endif
