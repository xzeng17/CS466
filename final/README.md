# CS466 Programming Homework Peptide BLAST Search

Peptide BLAST search tool based on BLOSUM matrix.

Generate database from input subjects in fasta format.
Iterate through all possible triplets and stored the index in the sequence.

Query is loaded and traverse all possible triplets generate seeds through both exact match and fuzzy match.

After generating seeds, expend alignment sequences from left and right side of seeds through editing distance algorithm.

Alignment of matching domain is printed in the console.

# User guide

To compile program    $ make
To compile test suite $ make test
To excute program     $ ./main
To excute test cases  $ ./test