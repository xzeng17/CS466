package Assignment1;
import static Assignment1.Problem1new.*;
public class Problem4 {
    /*               seqA
                  A T T G C

             A
       seqB  G
             C
     */
    public static void gapAlignment(String seqA, String seqB, int mtScore, int mismtScore,
                                    int gapInitScore, int gapScore) {
        int[][] dp = new int[seqB.length()+1][seqA.length()+1];
        // Track number of continuous gap from left to right for sequenceA
        int[][] GapA = new int[seqB.length()+1][seqA.length()+1];
        // Track number of continuous gap from up to down for sequenceB
        int[][] GapB = new int[seqB.length()+1][seqA.length()+1];
        for (int i=1; i<dp[0].length; i++) {
            if (GapA[0][i-1] == 0) {
                dp[0][i] = gapInitScore;
            } else {
                dp[0][i] = dp[0][i-1]+gapScore;
            }
            GapA[0][i] = GapA[0][i-1]+1;
        }

        for (int i=1; i<dp.length; i++) {
            if (GapB[i-1][0] == 0) {
                dp[i][0] = gapInitScore;
            } else {
                dp[i][0] = dp[i-1][0]+gapScore;
            }
            GapB[i][0] = GapB[i-1][0]+1;
        }
        // print initial row and column construction
        printDPMatrix(seqA, seqB, dp);
        printDPMatrix(seqA, seqB, GapA);
        printDPMatrix(seqA, seqB, GapB);

        for (int y=1; y<dp.length; y++) {
            for (int x=1; x<dp[0].length; x++) {
                char charA = seqA.charAt(x-1), charB = seqB.charAt(y-1);
                int match = charA == charB ? dp[y-1][x-1]+mtScore : Integer.MIN_VALUE;
                int mismatch = charA != charB ? dp[y-1][x-1]+mismtScore : Integer.MIN_VALUE;
                int gapLeft = GapA[y][x-1] == 0 ? dp[y][x-1]+gapInitScore : dp[y][x-1]+gapScore;
                int gapTop = GapB[y-1][x] == 0 ? dp[y-1][x]+gapInitScore : dp[y-1][x]+gapScore;
                int[] candidates = {match, mismatch, gapLeft, gapTop};
                if (match != Integer.MIN_VALUE && isMax(match, candidates)) {
                    dp[y][x] = match;
                } else if (match != Integer.MIN_VALUE && isMax(mismatch, candidates)){
                    dp[y][x] = mismatch;
                } else if (isMax(gapLeft, candidates)) {
                    dp[y][x] = gapLeft; GapA[y][x] = GapA[y][x-1]+1;
                } else {
                    dp[y][x] = gapTop; GapB[y][x] = GapB[y-1][x]+1;
                }
            }
        }
        printDPMatrix(seqA, seqB, dp);
        printDPMatrix(seqA, seqB, GapA);
        printDPMatrix(seqA, seqB, GapB);

    }


    public static boolean isMax(int query, int[] numbers) {
        for (int ele : numbers) {
            if (ele > query) return false;
        }
        return true;
    }

    public static void main(String[] args) {
        gapAlignment("ATTGC", "AGC", 5, -5, -10,-5);
    }
}
