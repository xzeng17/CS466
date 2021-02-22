package Assignment1;

/*
Calculate and show the Dynamic Programming matrix and an optimal alignment
for the DNA sequences GCATTGC and GATTAGC, scoring +2 for a match, -1
for a mismatch, and a gap penalty of 2 (i.e., each gap column contributes -2). (If
there are more than one optimal alignments, you can report any of them.)
                        sequence A
                   G   C   A   T   T   G   C
                0  1   2   3   4   5   6   7
             G  1
             A  2
    B        T  3
             T  4
             A  5
             G  6
             C  7

 */
public class Problem1 {
    public static int alignmentScore(String sequenceA, String sequenceB,
                                     int matchingScore, int mismatchingScore, int gapScore) {
        // Initialize dp matrix with height as length of sequenceB+1
        // width as length of sequenceA + 1
        int[][] dp = new int[sequenceB.length()+1][sequenceA.length()+1];

        // First column, comparing empty string to sequence B
        // Plug in default editing distance of B[0:i] from empty string
        for (int i=1; i<=sequenceB.length(); i++) {
            dp[i][0] = dp[i-1][0]+1;
        }

        // First row, comparing empty string to sequence A
        // Plug in default editing distance of A[0:i] from empty string
        for (int i=1; i<=sequenceA.length(); i++) {
            dp[0][i] = dp[0][i-1]+1;
        }

        // If sequenceA[i-1] == sequenceB[j-1], inherit dp[i-1][j-1]
        // Else, there is an addition of editing distance
        // dp[i-1][j-1]+1 for mismatch
        // dp[i-1][j]+1 for removing a char from sequenceA/extending a char for sequenceB
        // dp[i][j-1]+1 for removing a char from sequenceB/extending a char for sequenceA
        for (int i=1; i<=sequenceB.length(); i++) {
            for (int j=1; j<=sequenceA.length(); j++) {
                char charA = sequenceA.charAt(j-1), charB = sequenceB.charAt(i-1);
                if (charA == charB) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = Math.min(dp[i][j-1], Math.min(dp[i-1][j-1], dp[i-1][j]))+1;
                }
            }
        }

        printDPMatrix(sequenceA, sequenceB, dp);

        StringBuilder sbA = new StringBuilder();
        StringBuilder sbB = new StringBuilder();

        //  idx/move = 0 -> topleft (either a match or a mismatch)
        //  idx/move = 1 -> left (gap for sequenceB, extension for sequenceA)
        //  idx/move = 2 -> top  (gap for sequenceA, extension for sequenceB)
        int[] dx = {-1, -1, 0}; int[] dy = {-1, 0, -1};

        int x = sequenceA.length(), y = sequenceB.length(), score = 0;

        while (x!=0 && y!= 0) {
            char charA = '_', charB = '.';
            if (x > 0) charA = sequenceA.charAt(x-1);
            if (y > 0) charB = sequenceB.charAt(y-1);
            int move = getMove(x, y, dp);
            if (move == 0) {
                score = charA == charB ? score+matchingScore : score+mismatchingScore;
                sbA.append(charA);
                sbB.append(charB);
            } else if (move == 1) {
                score += gapScore;
                sbA.append(charA);
                sbB.append("-");
            } else {
                score += gapScore;
                sbA.append("-");
                sbB.append(charB);
            }
            x+=dx[move]; y+=dy[move];
        }
        System.out.print("SqeuenceA: "); System.out.println(sbA.reverse().toString());
        System.out.print("SqeuenceB: "); System.out.println(sbB.reverse().toString());
        return score;
    }

    // for dp[y-1][x-1], pick the smallest one to move
    // Highest priority for match/mismatch -> dp[y-1][x-1]
    public static int getMove(int x, int y, int[][] dp) {
        int top = Integer.MAX_VALUE, left = Integer.MAX_VALUE, topLeft = Integer.MAX_VALUE;
        if (validRange(x-1, y-1, dp)) topLeft = dp[y-1][x-1];
        if (validRange(x-1, y, dp)) left = dp[y][x-1];
        if (validRange(x, y-1, dp)) top = dp[y-1][x];
        if (topLeft <= left && topLeft <= top) return 0;
        if (left <= top) return 1;
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
