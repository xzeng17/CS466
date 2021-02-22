package Assignment1;

import static Assignment1.Problem1.alignmentScore;

public class Problem2 {

    public static void main(String[] args) {
        String leftA = "TCTGC"; String middleA = "C"; String rightA = "TCTGC";
        String leftB = "ACTGAC"; String middleB = "C"; String rightB = "ACTGAC";
        int leftScore = alignmentScore(leftA,leftB, 2, -1, -2);
        int middleScore = alignmentScore(middleA,middleB, 2, -1, -2);
        int rightScore = alignmentScore(rightA,rightB, 2, -1, -2);
        System.out.print("Alignment score: "); System.out.println(leftScore+middleScore+rightScore);
    }
}
