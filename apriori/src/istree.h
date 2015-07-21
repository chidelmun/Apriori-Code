/*----------------------------------------------------------------------
  File    : istree.h
  Contents: item set tree management for apriori algorithm

----------------------------------------------------------------------*/
#ifndef __ISTREE__
#define __ISTREE__
#include <stddef.h>
#include <limits.h>
#include "ruleval.h"
#include "report.h"

/*----------------------------------------------------------------------
  Preprocessor Definitions
----------------------------------------------------------------------*/
/* --- operation modes --- */
#define IST_PERFECT 0x0100      /* prune with perfect extensions */
#define IST_PARTIAL 0x0200      /* do only partial subset checks */
#define IST_REVERSE 0x0400      /* reverse item order */

/* --- additional evaluation measures --- */
/* evaluation measure definitions in ruleval.h */
#define IST_INVBXS  INT_MIN     /* invalidate eval. below exp. supp. */

/* --- evaluation measure aggregation modes --- */
#define IST_NONE    0           /* no aggregation (use first value) */
#define IST_FIRST   0           /* no aggregation (use first value) */
#define IST_MIN     1           /* minimum of measure values */
#define IST_MAX     2           /* maximum of measure values */
#define IST_AVG     3           /* average of measure values */

/* --- item set filter modes --- */
#define IST_CLEAR   ISR_ALL     /* all     frequent item sets */
#define IST_CLOSED  ISR_CLOSED  /* closed  frequent item sets */
#define IST_MAXIMAL ISR_MAXIMAL /* maximal frequent item sets */
#define IST_GENERA  ISR_GENERA  /* generators */
#define IST_SAFE    ISR_SORT    /* safe filtering (assume holes) */

/*----------------------------------------------------------------------
  Type Definitions
----------------------------------------------------------------------*/
typedef struct istnode {        /* --- item set tree node --- */
  struct istnode *succ;         /* successor node (on same level) */
  struct istnode *parent;       /* parent    node (one level up) */
  ITEM           item;          /* item used in parent node */
  ITEM           offset;        /* offset of counter array */
  ITEM           size;          /* size   of counter array */
  ITEM           chcnt;         /* number of child nodes */
  SUPP           cnts[1];       /* counter array (weights) */
} ISTNODE;                      /* (item set tree node) */

typedef struct {                /* --- item set tree --- */
  ITEMBASE *base;               /* underlying item base */
  int      mode;                /* search mode (e.g. support def.) */
  SUPP     wgt;                 /* total weight of transactions */
  ITEM     height;              /* tree height (number of levels) */
  ISTNODE  **lvls;              /* first node of each level */
  int      valid;               /* whether levels are valid */
  SUPP     smin;                /* minimum support of an item set */
  SUPP     body;                /* minimum support of a rule body */
  double   conf;                /* minimum confidence of a rule */
  int      eval;                /* additional evaluation measure */
  int      agg;                 /* aggregation mode of measure values */
  int      invbxs;              /* invalidate eval. below expectation */
  double   dir;                 /* direction of evaluation measure */
  double   thresh;              /* evaluation measure threshold */
  ISTNODE  *curr;               /* current node for traversal */
  ITEM     depth;               /* depth of current node */
  ITEM     size;                /* current size of an item set */
  ITEM     zmin;                /* minimal size of an item set */
  ITEM     zmax;                /* maximal size of an item set */
  int      order;               /* item set output order (by size) */
  ISTNODE  *node;               /* item set node for extraction */
  ITEM     index;               /* index in item set node */
  ISTNODE  *head;               /* head item node for extraction */
  ITEM     prune;               /* start level for evaluation pruning */
  ITEM     item;                /* head item of previous rule */
  ITEM     *buf;                /* buffer for paths (support check) */
  ITEM     *path;               /* current path / (partial) item set */
  int      hdonly;              /* head only item in current set */
  ITEM     *map;                /* to create identifier maps */
#ifdef BENCH                    /* if benchmark version */
  size_t   ndcnt;               /* number of item set tree nodes */
  size_t   ndprn;               /* number of pruned tree nodes */
  size_t   mapsz;               /* number of elements in id. maps */
  size_t   sccnt;               /* number of created support counters */
  size_t   scnec;               /* number of necessary supp. counters */
  size_t   scprn;               /* number of pruned support counters */
  size_t   cpcnt;               /* number of created child pointers */
  size_t   cpnec;               /* number of necessary child pointers */
  size_t   cpprn;               /* number of pruned child pointers */
#endif
} ISTREE;                       /* (item set tree) */

/*----------------------------------------------------------------------
  Functions
----------------------------------------------------------------------*/
extern ISTREE*   ist_create  (ITEMBASE *base, int mode,
                              SUPP smin, SUPP body, double conf);
extern void      ist_delete  (ISTREE *ist);
extern ITEMBASE* ist_base    (ISTREE *ist);
extern ITEM      ist_itemcnt (ISTREE *ist);

extern void      ist_count   (ISTREE *ist,
                              const ITEM *items, ITEM n, SUPP wgt);
extern void      ist_countt  (ISTREE *ist, const TRACT  *tract);
extern void      ist_countb  (ISTREE *ist, const TABAG  *bag);
#ifdef TATREEFN
extern void      ist_countx  (ISTREE *ist, const TATREE *tree);
#endif
extern void      ist_commit  (ISTREE *ist);
extern ITEM      ist_check   (ISTREE *ist, int *marks);
extern void      ist_prune   (ISTREE *ist);
extern int       ist_addlvl  (ISTREE *ist);

extern ITEM      ist_zmin    (ISTREE *ist);
extern ITEM      ist_zmax    (ISTREE *ist);
extern ITEM      ist_height  (ISTREE *ist);
extern SUPP      ist_getwgt  (ISTREE *ist);
extern SUPP      ist_setwgt  (ISTREE *ist, SUPP wgt);
extern SUPP      ist_incwgt  (ISTREE *ist, SUPP wgt);

extern void      ist_root    (ISTREE *ist);
extern void      ist_up      (ISTREE *ist);
extern int       ist_down    (ISTREE *ist, ITEM item);
extern ITEM      ist_depth   (ISTREE *ist);
extern ITEM      ist_next    (ISTREE *ist, ITEM item);
extern SUPP      ist_getsupp (ISTREE *ist, ITEM item);
extern SUPP      ist_setsupp (ISTREE *ist, ITEM item, SUPP supp);
extern SUPP      ist_incsupp (ISTREE *ist, ITEM item, SUPP supp);
extern int       ist_xable   (ISTREE *ist, ITEM n);
extern int       ist_addchn  (ISTREE *ist);
extern SUPP      ist_supp    (ISTREE *ist, ITEM *items, ITEM n);

extern void      ist_clear   (ISTREE *ist);
extern void      ist_filter  (ISTREE *ist, ITEM size);
extern void      ist_clomax  (ISTREE *ist, int target);
extern void      ist_setsize (ISTREE *ist, ITEM zmin, ITEM zmax);
extern void      ist_seteval (ISTREE *ist, int eval, int agg,
                              double thresh, ITEM prune);

extern void      ist_init    (ISTREE *ist, int order);
extern ITEM      ist_iset    (ISTREE *ist, ITEM *items, SUPP *supp,
                              double *eval);
extern ITEM      ist_rule    (ISTREE *ist, ITEM *rule,  SUPP *sset,
                              SUPP *sbody, SUPP *shead, double *eval);
extern int       ist_report  (ISTREE *ist, ISREPORT *rep, int target);

extern double    ist_eval    (ISTREE *ist);
extern double    ist_evalx   (ISREPORT *rep, void *data);

#ifdef BENCH
extern void      ist_stats   (ISTREE *ist);
#endif
#ifndef NDEBUG
extern void      ist_show    (ISTREE *ist);
#endif

/*----------------------------------------------------------------------
  Preprocessor Definitions
----------------------------------------------------------------------*/
#define ist_base(t)       ((t)->base)
#define ist_itemcnt(t)    ((t)->levels[0]->size)
#define ist_zmin(t)       ((t)->zmin)
#define ist_zmax(t)       ((t)->zmax)
#define ist_height(t)     ((t)->height)
#define ist_getwgt(t)     ((t)->wgt & ~SUPP_MIN)
#define ist_setwgt(t,n)   ((t)->wgt = (n))
#define ist_incwgt(t,n)   ((t)->wgt = ((t)->wgt & ~SUPP_MIN) +(n))
#define ist_depth(t)      ((t)->depth)
#define ist_xable(t,n)    ((t)->depth+(n) <= (t)->zmax)

#endif
