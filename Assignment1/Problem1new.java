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

        //  idx/move = 0 -> topleft (either a match or a mismatch)
        //  idx/move = 1 -> left (gap for sequenceB, extension for sequenceA)
        //  idx/move = 2 -> top  (gap for sequenceA, extension for sequenceB)
        int[] dx = {-1, -1, 0}; int[] dy = {-1, 0, -1};

        // If sequenceA[i-1] == sequenceB[j-1], inherit dp[i-1][j-1]+2 for a match
        // dp[i-1][j-1]-1 for mismatch
        // dp[i-1][j]-2 for removing a char from sequenceA/extending a char for sequenceB
        // dp[i][j-1]-2 for removing a char from sequenceB/extending a char for sequenceA
        for (int y=1; y<=sequenceB.length(); y++) {
            for (int x=1; x<=sequenceA.length(); x++) {
                char charA = sequenceA.charAt(x-1), charB = sequenceB.charAt(y-1);
                int match = dp[y-1][x-1]+2, mismatch = dp[y-1][x-1]-1;
                int extendLeft = dp[y][x-1]-2, extendTop = dp[y-1][x]-2;
                dp[y][x] = Math.max(extendLeft, extendTop);
                dp[y][x] = charA == charB?Math.max(dp[y][x], match):Math.max(dp[y][x], mismatch);
            }
        }

        printDPMatrix(sequenceA, sequenceB, dp);

        StringBuilder sbA = new StringBuilder();
        StringBuilder sbB = new StringBuilder();

        return -1;
    }

    // for dp[y-1][x-1], pick the largest one to move
    // Highest priority for match/mismatch -> dp[y-1][x-1]
    public static int getMove(int x, int y, int[][] dp) {
        int top = Integer.MIN_VALUE, left = Integer.MIN_VALUE, topLeft = Integer.MIN_VALUE;
        if (validRange(x-1, y-1, dp)) topLeft = dp[y-1][x-1]+2;
        if (validRange(x-1, y, dp)) left = dp[y][x-1]-2;
        if (validRange(x, y-1, dp)) top = dp[y-1][x]-2;
        if (topLeft >= left && topLeft >= top) return 0;// match
        if (topLeft-3 >= left && topLeft-3 >= top) return 0;// mismatch
        if (left >= top) return 1;
        return 2;
    }

    // check our move is within the validRange
    public static boolean validRange(int x, int y, int[][] dp) {
        return x >= 0 && y >= 0 && x < dp[0].length && y < dp.length;
    }

    public static void printDPMatrix(String sequenceA, String sequenceB, int[][] dp) {
        // To print the dp matrix
        for (int i=0; i< sequenceA.length()+1; i++) {
            if (i == 0) {
                System.out.print("''  ");
            } else {
                System.out.print(sequenceA.charAt(i-1));
                System.out.print(" ");
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
//        String sequenceA = "GCATTGC";
//        String sequenceB = "GATTAGC";
        String sequenceA = "AAAGAATTCA";
        String sequenceB = "AAATCA";
        int score = alignmentScore(sequenceA,sequenceB, 2, -1, -2);
        System.out.print("Alignment score: "); System.out.println(score);
    }
}
