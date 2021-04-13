# CS466 Programming Homework Peptide BLAST Search

Peptide BLAST search tool based on BLOSUM matrix.

Generate database from input subjects in fasta format.
Iterate through all possible triplets and stored the index in the sequence.

Query is loaded and traverse all possible triplets generate seeds through both exact match and fuzzy match.

After generating seeds, expend alignment sequences from left and right side of seeds through editing distance algorithm.

Alignment of matching domain is printed in the console.

# Unaddressed issues

Even though I implemented the sequence expending through editing distance, the result is not desired because the output for mismatch/gapped tests are too short and the gapping and mismatch did not worked as expected.

# User guide

Put the query sequence in fasta format in InputQuery folder.
Put the subject sequences in fasta format in InputSubjects folder. </bar>

To compile program    $ make                                              </bar>
To compile test suite $ make test                                         </bar>  
To excute program     $ ./main <query file name> <subject file name>      </bar>
To excute test cases  $ ./test                                            </bar>

# Example:

    $ ./main
    $ ./main query.txt gfps.txt

