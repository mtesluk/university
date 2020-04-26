package snake;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Point;
import java.util.ArrayList;

import javax.swing.JLabel;
import javax.swing.JPanel;

public class Segment {
	public JLabel square = new JLabel("");
	public Color color = Color.RED;
	public String direction = "";
	public ArrayList<Point> intersections = new ArrayList<>();
	
	public void draw(JPanel pane, int x, int y) {
		square.setOpaque(true);
		square.setBackground(color);
		square.setBounds(x, y, Config.segmentSize, Config.segmentSize);
		pane.add(square);
		pane.repaint();
	}
	
	public void setDirection(String dir) {
		direction = dir;
	}
	
	public String getDirection() {
		return direction;
	}
	
	public void removeLabel(JPanel pane) {
		pane.remove(square);
		pane.repaint();
	}
	
	public void pop(JPanel pane) {
		pane.remove(square);
		pane.repaint();
	}
	
	public void draw(JPanel pane) {
		square.setOpaque(true);
		square.setBackground(color);
		square.setBounds(Config.snakeStartPoint.x, Config.snakeStartPoint.y, Config.segmentSize, Config.segmentSize);
		pane.add(square);
	}
	
	public Point getLocation() {
		return square.getLocation();
	}
	
	public Dimension getSize() {
		return square.getSize();
	}
	
	public void setLocation(int x, int y) {
		square.setLocation(x, y);
	}
	
	public void setColor(Color clr) {
		square.setBackground(clr);
	}
}
