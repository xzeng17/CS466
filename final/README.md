# CS466 Programming Homework Peptide BLAST Search

Peptide BLAST search tool based on BLOSUM matrix.

Generate database from input subjects in fasta format.
Iterate through all possible triplets and stored the index in the sequence.

Query is loaded and traverse all possible triplets generate seeds through both exact match and fuzzy match.

After generating seeds, expend alignment sequences from left and right side of seeds through editing distance algorithm.

Alignment of matching domain is printed in the console.

# Unaddressed issues

Even though I implemented the sequence expending through editing distance, the result is not desired. The output for mismatch/gapped tests are too short and the gapping and mismatch did not worked as expected.

# User guide

Make sure you have Clang and libc++ and the libc++abi
$ sudo apt-get update; sudo apt-get install clang-6.0 libc++abi-dev libc++-dev

Place the query sequences in fasta format in InputQuery folder.           <br>
Place the subject sequences in fasta format in InputSubjects folder.      <br>

To compile program    $ make blast                                        <br>
To compile test suite $ make test                                         <br>
To excute program     $ ./blast [query file name] [subject file name]     <br>
To excute test cases  $ ./test                                            <br>

# Example

    $ ./blast
    $ ./blast queries.txt gfps.txt

