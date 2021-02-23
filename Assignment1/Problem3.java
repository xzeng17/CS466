package Assignment1;

import static Assignment1.Problem1new.*;

public class Problem3 {
    /*                  seqA
                   A  T  A  T  C  T  C
                0  0  0  0  0  0  0  0
   seqB     A   0  5  0  5  0  0  0  0
            T   0  0 10  5 10  5  5  0
            C   0  0  5  0  5 15 10 10
     */
    public static void localAlignment(String seqA, String seqB,
                                      int mtScore, int mismtScore, int gapScore) {
        if (seqA.length() < seqB.length()) {
            localAlignment(seqB, seqA, mtScore, mismtScore, gapScore);
            return;
        }
        int[][] dp = new int[seqB.length()+1][seqA.length()+1];

        for (int y=1; y<dp.length; y++) {
            for (int x=1; x<dp[0].length; x++) {
                char charA = seqA.charAt(x-1), charB = seqB.charAt(y-1);
                int match = charA == charB ? dp[y-1][x-1]+mtScore : 0;
                int mismatch = charA != charB ? dp[y-1][x-1]+mismtScore : 0;
                int extend = Math.max(0,Math.max(dp[y][x-1],dp[y-1][x])+gapScore);
                dp[y][x] = Math.max(extend,Math.max(match, mismatch));
            }
        }
        printDPMatrix(seqA,seqB,dp);

        int sX = 0, sY = 0, maxVal = 0;
        for (int y=1; y<dp.length; y++) {
            for (int x=1; x<dp[0].length; x++) {
                if (dp[y][x] > maxVal) {
                    maxVal = dp[y][x]; sX = x; sY = y;
                }
            }
        }
        StringBuilder sbA = new StringBuilder(), sbB = new StringBuilder();
        for (int i=dp[0].length-1; i> sX; i--) {
            sbA.append(seqA.charAt(i-1)); sbB.append("-");
        }

        while (dp[sY][sX] != 0) {
            char charA = seqA.charAt(sX-1), charB = seqB.charAt(sY-1);
            int topLeft = getNext(sX-1, sY-1,dp), left = getNext(sX-1, sY, dp),
                    top = getNext(sX, sY-1, dp), cur = getNext(sX, sY, dp);
            if ((charA == charB && topLeft == cur-mtScore) || (charA != charB && topLeft == cur-mismtScore)) {
                sbA.append(charA); sbB.append(charB); sY--; sX--;
            } else if (top == cur - gapScore) {
                sbA.append("-"); sbB.append(charB); sY--;
            } else if (left == cur - gapScore) {
                sbA.append(charA); sbB.append("-"); sX--;
            }
        }

        for (int i=sX; i> 0; i--) {
            sbA.append(seqA.charAt(i-1)); sbB.append("-");
        }

        System.out.println(sbA.reverse().toString());
        System.out.println(sbB.reverse().toString());
    }


    public static void main(String[]args) {
        localAlignment("ATATCTC", "ATC", 5, -10, -5);
//        String seqA = "ATATCTC";
//        String seqB = "ATC";
//        int score = alignmentScore(seqA, seqB, 5, -10, -5);
    }
}
