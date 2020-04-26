package snake;

import java.awt.Color;
import java.awt.Point;

public class Config {
	public static int segmentSize = 15;
	public static int slowSpeed = 30;
	public static int mediumSpeed = 20;
	public static int fastSpeed = 10;
	public static int step = 1;
	public static Point snakeStartPoint = new Point(0, 0);
	public static String initDirection = "down";
	public static int speedFoodRespown = 3000;
	public static int[] foodValues = {1, 2, 3};
	public static Color headColor = Color.RED;
	public static Color foodColor = Color.GREEN;
	public static Color bodyColor = Color.BLUE;
	public static Color backgroundColor = Color.BLACK;
}
