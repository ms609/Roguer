# Rogue v2.1.6.9001 (development)

- Simplify vignette with new `TreeTools::ReadMrBayesTrees()`.


# Rogue v2.1.6

- Legend annotations in documentation.
- Disable parallel evaluation by default in `TipInstability()`,
  adding `parallel` parameter to allow user to override.
- Use format string in REprintf().


# Rogue v2.1.5

- Call C functions using symbols, not strings.


# Rogue v2.1.4

- C2X compliant function prototypes.

- Remove unused `sprintf()` calls.


# Rogue v2.1.3

- `ColByStability()` gains `pal` argument to allow specification of custom
  palettes.


# Rogue v2.1.2

- Faster rogue detection when edge lengths provided, per report by Joe Keating.

- Don't list `neverDrop` in `QuickRogue(fullSeq = TRUE)`.


# Rogue v2.1.1

- Handle `ColByStability(trees = NULL)`.


# Rogue v2.1.0

- Early termination of `QuickRogue()` when no further improvement possible.

- `Cophenetic()` renamed to the more accurate `GraphGeodesic()`.

- Calculate information content of consensus trees with p > 0.5 (#15).

- Improve support for `multiPhylo` objects.

- New vignette detailing rogue detection with Bayesian tree samples.


# Rogue v2.0.0

- Information theoretic rogue detection (per Smith, 2022).


# Rogue v1.0.0

 - R interface to RogueNaRok.
