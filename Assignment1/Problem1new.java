package Assignment1;

/*
Calculate and show the Dynamic Programming matrix and an optimal alignment
for the DNA sequences GCATTGC and GATTAGC, scoring +2 for a match, -1
for a mismatch, and a gap penalty of 2 (i.e., each gap column contributes -2). (If
there are more than one optimal alignments, you can report any of them.)
                        sequence A
                   G   C   A   T   T   G   C
                0 -2  -4  -6  -8 -10 -12 -14
             G -2
             A -4
    B        T -6
             T -8
             A-10
             G-12
             C-14

 */
public class Problem1new {
    public static int alignmentScore(String sequenceA, String sequenceB,
                                     int matchingScore, int mismatchingScore, int gapScore) {
        // Initialize dp matrix with height as length of sequenceB+1
        // width as length of sequenceA + 1
        int[][] dp = new int[sequenceB.length()+1][sequenceA.length()+1];

        // First column, comparing empty string to sequence B
        // Calculate gaping score of B[0:i] from empty string
        for (int i=1; i<=sequenceB.length(); i++) {
            dp[i][0] = dp[i-1][0]-2;
        }

        // First row, comparing empty string to sequence A
        // Calculate gaping score  of A[0:i] from empty string
        for (int i=1; i<=sequenceA.length(); i++) {
            dp[0][i] = dp[0][i-1]-2;
        }

        // If sequenceA[i-1] == sequenceB[j-1], inherit dp[i-1][j-1]+2 for a match
        // dp[i-1][j-1]-1 for mismatch
        // dp[i-1][j]-2 for removing a char from sequenceA/extending a char for sequenceB
        // dp[i][j-1]-2 for removing a char from sequenceB/extending a char for sequenceA
        for (int y=1; y<=sequenceB.length(); y++) {
            for (int x=1; x<=sequenceA.length(); x++) {
                char charA = sequenceA.charAt(x-1), charB = sequenceB.charAt(y-1);
                int match = dp[y-1][x-1]+matchingScore, mismatch = dp[y-1][x-1]+mismatchingScore;
                int extendLeft = dp[y][x-1]+gapScore, extendTop = dp[y-1][x]+gapScore;
                dp[y][x] = Math.max(extendLeft, extendTop);
                dp[y][x] = charA == charB?Math.max(dp[y][x], match):Math.max(dp[y][x], mismatch);
            }
        }

        StringBuilder sbA = new StringBuilder(), sbB = new StringBuilder();
        int x=dp[0].length-1, y=dp.length-1;
        while  (x >0 && y > 0) {
            char charA = '_', charB = '.';
            if (x < sequenceA.length()) charA = sequenceA.charAt(x);
            if (y < sequenceB.length()) charB = sequenceB.charAt(y);
            int match = getNext(x + 1, y + 1, dp),
                    mismatch = getNext(x + 1, y + 1, dp),
                    extendA = getNext(x + 1, y, dp), extendB = getNext(x, y + 1, dp);
            int move = getMove(match, mismatch, extendA, extendB);
            if (move == 0) {
                sbA.append(charA); sbB.append(charB); x++; y++;
            } else if (move == 1) {
                sbA.append(charA + 32); sbB.append(charB + 32); x++; y++;
            } else if (move == 2) {
                sbA.append(charA); sbB.append("-"); x++;
            } else if (move == 3) {
                sbA.append("-"); sbB.append(charB); y++;
            }
        }

        printDPMatrix(sequenceA, sequenceB, dp);
        System.out.print("SequenceA: "); System.out.println(sbA.reverse().toString());
        System.out.print("SequenceB: "); System.out.println(sbB.reverse().toString());

        return dp[sequenceB.length()][sequenceA.length()];
    }

    public static int getNext(int x, int y, int[][]dp) {
        if (x<=0 || y<=0 || x>= dp[0].length || y >= dp.length) return Integer.MIN_VALUE;
        return dp[y][x];
    }


    // return 0 for match, 1 for mismatch, 2 for extendA/gapB, 3 for extendB/gapA
    public static int getMove(int match, int mismatch, int extendA, int extendB) {
        if (match >= mismatch && match >= extendA && match >= extendB) return 0;
        if (mismatch >= extendA && mismatch >= extendB) return 1;
        if (extendA >= extendB) return 2;
        return 3;
    }

    public static void printDPMatrix(String sequenceA, String sequenceB, int[][] dp) {
        // To print the dp matrix
        for (int i=0; i< sequenceA.length()+1; i++) {
            if (i == 0) {
                System.out.print("''    ");
            } else {
                System.out.print(sequenceA.charAt(i-1));
                System.out.print("   ");
            }
        }
        System.out.println();
        for (int i=0; i<sequenceB.length()+1; i++) {
            if (i == 0) {
                System.out.print("  ");
            }
            else {
                System.out.print(sequenceB.charAt(i - 1));
                System.out.print(" ");
            }
            for (int j = 0; j < sequenceA.length()+1; j++) {

                System.out.print(dp[i][j]);
                System.out.print(" ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        String sequenceA = "GCATTGC";
        String sequenceB = "GATTAGC";
//        String sequenceA = "AAAGAATTCA";
//        String sequenceB = "AAATCA";
        int score = alignmentScore(sequenceA,sequenceB, 2, -1, -2);
        System.out.print("Alignment score: "); System.out.println(score);
    }
}
