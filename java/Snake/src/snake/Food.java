package snake;

import java.awt.Color;
import java.util.Random;

import javax.swing.JPanel;
import javax.swing.SwingConstants;

public class Food extends Segment{
	private int value = 0;
	private boolean eaten = false;
	
	Food() {
		Random rand = new Random();
		value = Config.foodValues[rand.nextInt(Config.foodValues.length)];
		super.color = Config.foodColor;
		super.square.setText(value + "");
		super.square.setHorizontalAlignment(SwingConstants.CENTER);
		super.square.setVerticalAlignment(SwingConstants.CENTER);
	}
	
	public void setEaten() {
		eaten = true;
	}
	
	public boolean isEasten() {
		return eaten;
	}
	
	public int getValue() {
		return value;
	}
}
