class Road{
	int toRight;
	int toDown;

	Road(int right, int down) {
		toRight = right;
		toDown = down;
	}
}

public class Manhatten{

	public static int maxPoint(Road[][] weightMap) {
		int[][] dp = new int[weightMap.length][weightMap[0].length];

		for (int j=1; j<weightMap.length; j++) {
			dp[0][j] = dp[0][j-1] + weightMap[0][j-1].toRight;
		}

		for (int i=1; i<weightMap[0].length; i++) {
			dp[i][0] = dp[i-1][0] + weightMap[i-1][0].toDown;
		}

		for (int i=1; i<weightMap.length; i++) {
			for (int j=1; j<weightMap.length; j++) {
				int fromTop = dp[i-1][j] + weightMap[i-1][j].toDown;
				int fromLeft = dp[i][j-1] + weightMap[i][j-1].toRight;
				dp[i][j] = Math.max(fromTop, fromLeft);
			}
		}

		return dp[weightMap.length-1][weightMap[0].length-1];
	}


	public static void main(String[] args) {
		Road[][]weightMap = new Road[4][4];
		int[][] rightWeights = {{1,2,5,-1},{-5,1,-5,-1},{-5,3,3,-1}, {0,0,0,-1}};
		int[][] downWeights = {{5,3,10,-5},{3,5,-3,2},{-0,0,-5,1}, {-1,-1,-1,-1}};

		for (int i=0; i<4; i++) {
			for (int j=0; j<4; j++) {
				int right = rightWeights[i][j];
				int down = downWeights[i][j];
				weightMap[i][j] = new Road(right, down);
			}
		}

		System.out.println(maxPoint(weightMap));
	}
}