package Assignment1;

import static Assignment1.Problem1new.alignmentScore;

public class Problem2 {

    public static void main(String[] args) {
        String leftA = "TCTGC", midA = "C", rightA="TCTGC";
        String leftB = "ACTGAC", midB = "C", rightB="ACTGAC";
        int score = 0;
        score += alignmentScore(leftA, leftB, 2, -1, -2);
        score += alignmentScore(midA,midB,2,-1,-2);
        score+= alignmentScore(rightA,rightB,2,-1,-2);

        System.out.print("Score for problem2: ");
        System.out.println(score);
    }
}
