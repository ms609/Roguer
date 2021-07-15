#include <R.h>
#include <Rinternals.h>
#include <assert.h>

#define NOTMYDEBUG
#define DEBUG

#define RET(i, j) ret[(i) + *all_nodes * (j)]
#define GET(i, j) ((i) > (j) ? RET((i), (j)) : RET((j), (i)))
#define SETBOTH(i, j, k) RET((i), (j)) = RET((j), (i)) = (k)
#define SETNODE(i, j, k) if ((i) > (j)) RET((i), (j)) = (k); else RET((j), (i)) = (k)

// Algorithm following ape::dist_nodes
void cophenetic_phylo(const int *n_tip, const int *n_node,
                      const int *parent, const int *child,
                      const int *n_edge, const int *all_nodes,
                      int *ret) {
  const int
    root_node = parent[0],
    root_child = child[0]
  ;
  for (int i = *all_nodes; i--; ) {
    RET(i, i) = 0;
  }

#ifdef MYDEBUG
  Rprintf("Start: SetN %i > %i = %i\n", root_node, root_child, 1);
#endif
  SETNODE(root_node, root_child, 1);
  for (int i = 1; i != *n_edge; ++i) {
    const int parent_i = parent[i], child_i = child[i];
#ifdef MYDEBUG
    Rprintf("\n edge_i = %i: SetN %i > %i = %i\n", i, parent_i, child_i, 1);
#endif
    SETNODE(parent_i, child_i, 1);

    for (int j = i - 1; j >= 0; --j) {
      const int child_j = child[j];
      if (child_j == parent_i) {
#ifdef MYDEBUG
        Rprintf("j = %i: Skip %i = %i\n", j, parent_i, child_j);
#endif
        continue;
      }
#ifdef MYDEBUG
      Rprintf("j = %i: SetB [%i]-%i = 1+ (%i - %i) =  %i\n", j, child_j, child_i,
              parent_i, child_j, GET(parent_i, child_j) + 1);
#endif
      assert(parent_i > child_j);
      SETBOTH(child_j, child_i, GET(parent_i, child_j) + 1);
    }
    if (parent_i != root_node) {
#ifdef MYDEBUG
      Rprintf("Finish edge %i: SetN %i-%i = 1+ %i-%i = %i\n", i, root_node,
              child_i, root_node, parent_i, RET(parent_i, root_node) + 1);
#endif
      if (parent_i <= root_node) {
        Rprintf("Oh no! parent_i = %i <= root_node = %i", parent_i, root_node);
      }
      assert(parent_i > root_node);
      if (child_i > root_node) {
        SETNODE(child_i, root_node, RET(parent_i, root_node) + 1);
      } else {
        SETNODE(root_node, child_i, RET(parent_i, root_node) + 1);
      }
    }
  }
}

SEXP COPHENETIC(SEXP n_tip, SEXP n_node, SEXP parent, SEXP child, SEXP n_edge) {
  const int all_nodes = INTEGER(n_tip)[0] + INTEGER(n_node)[0];
  SEXP RESULT = PROTECT(allocVector(INTSXP, all_nodes * all_nodes));
  int *result = INTEGER(RESULT);

  cophenetic_phylo(INTEGER(n_tip), INTEGER(n_node), INTEGER(parent),
                   INTEGER(child), INTEGER(n_edge), &all_nodes, result);
  UNPROTECT(1);
  return(RESULT);
}
