#ifndef HUC_ALGEBRAICS_STRUCTURES_HH
#define HUC_ALGEBRAICS_STRUCTURES_HH

#include "huc/algebraic/Operations.hh"

namespace huc{

/** Group like - one operation */

// Magma
// - a set M with a binary operation +: M x M -> M
template<typename M>
concept Magma = has_add<M>;

// Semi-group
// - a Magma S whose binary operation + is associative

// Monoid
// - a Semi-group M with a zero
template<typename M>
concept Monoid = Magma<M> && has_zero<M>;

// Group
// - a Semi-group with a unary inverse and in turn subtraction
template<typename G>
concept Group = Monoid<G> && has_neg<G> && has_sub<G>;

// Abelian group 
// - a Group G whose binary operation + is commutative

// Some others - Semilattice, Quasigroup, Loop

/** Ring like (ringoid) - two operations, muliplication distributing over addition 
 *  - definitions are more depedent on associativity and commutivity
 */

// Semi-ring
// - a ringoid SR that is a Monoid under each operation 
template<typename SR>
concept Semiring = Monoid<SR> && has_mult<SR> && has_one<SR>;

// Ring 
// - a Semi-ring whose additive Monoid is an abelian group
template<typename R>
concept Ring = Semiring<R> && Group<R>;

// Field
// - a Ring that has a multiplicative inverse for every non-zero element
template<typename F>
concept Field = Ring<F> && has_div<F>;

}

#endif
