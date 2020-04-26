package snake;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Point;
import java.util.ArrayList;

import javax.swing.JLabel;
import javax.swing.JPanel;

public class Snake {
	private Segment head = new Segment();
	private ArrayList<Segment> body = new ArrayList<>();
	
	public void draw(JPanel pane) {
		head.draw(pane);
	}
	
	public void setIntersections() {
		for (Segment seg : body) {
			seg.intersections.add(head.getLocation());
		}
	}
	
	public void reset() {
		body.clear();
	}
	
	public void move() {		
		Point oldPos = head.getLocation();
		
		switch (head.getDirection()) {
			case "up": {
				head.setLocation(oldPos.x, oldPos.y - Config.step);
			}break;
			case "down": {
				head.setLocation(oldPos.x, oldPos.y + Config.step);
			}break;
			case "right": {
				head.setLocation(oldPos.x + Config.step, oldPos.y);
			}break;
			case "left": {
				head.setLocation(oldPos.x - Config.step, oldPos.y);
			}break;
		}
		
		for (int i = 0; i < body.size(); i++) {
			oldPos = body.get(i).getLocation();
			
			if (i == 0) {
				Point removed = null;
				for (Point point : body.get(i).intersections) {
					
					if (point.x == body.get(i).getLocation().x && point.y == body.get(i).getLocation().y) {
						body.get(i).setDirection(head.getDirection());
						removed = point;
					}
				}
				if (removed != null) body.get(i).intersections.remove(removed);
			} else {
				Point removed = null;
				for (Point point : body.get(i).intersections)
					if (point.x == body.get(i).getLocation().x && point.y == body.get(i).getLocation().y) {
						body.get(i).setDirection(body.get(i-1).getDirection());
						removed = point;
					}
				if (removed != null) body.get(i).intersections.remove(removed);
			}
			
			
			switch (body.get(i).getDirection()) {
				case "up": {
					body.get(i).setLocation(oldPos.x, oldPos.y - Config.step);
				}break;
				case "down": {
					body.get(i).setLocation(oldPos.x, oldPos.y + Config.step);
				}break;
				case "right": {
					body.get(i).setLocation(oldPos.x + Config.step, oldPos.y);
				}break;
				case "left": {
					body.get(i).setLocation(oldPos.x - Config.step, oldPos.y);
				}break;
			}
		}
	}
	
	private Segment getLastElement() {
		if (body.size() == 0)
			return head;
		return body.get(body.size()-1);
	}
	
	public void setDirection(String dir) {
		head.setDirection(dir);
	}
	
	public String getDirection() {
		return head.getDirection();
	}
	
	public Point getLocation() {
		return head.getLocation();
	}
	
	public Dimension getSize() {
		return head.getSize();
	}
	
	public void setLocation(int x, int y) {
		head.setLocation(x, y);
	}
	
	public void push(Food food) {
		Segment seg = getLastElement();
		String dir = seg.getDirection();
		switch (dir) {
			case "right": {
				food.setLocation(seg.getLocation().x - Config.segmentSize, seg.getLocation().y);
			} break;
			case "left": {
				food.setLocation(seg.getLocation().x + Config.segmentSize, seg.getLocation().y);
			} break;
			case "down": {
				food.setLocation(seg.getLocation().x, seg.getLocation().y - Config.segmentSize);
			} break;
			case "up": {
				food.setLocation(seg.getLocation().x, seg.getLocation().y + Config.segmentSize);
			} break;
		}
		food.setDirection(dir);
		for (Point point : seg.intersections) {
			food.intersections.add(point);
		}
		food.setColor(Config.bodyColor);
		body.add(food);
	}
	
	public boolean isOppositeDir(String key) {

		if (head.getDirection().equals("left") && key.equals("right")) return true;
		if (head.getDirection().equals("right") && key.equals("left")) return true;
		if (head.getDirection().equals("up") && key.equals("down")) return true;
		if (head.getDirection().equals("down") && key.equals("up")) return true;
		
		return false;
	}
	
	public boolean checkCollisionWithBody() {
		for (int i = 1; i < body.size(); i++) {
			if (Service.isInsideBox(head.getLocation().x, head.getLocation().y, body.get(i).getLocation(), body.get(i).getSize())) {
				return true;
			}
		}
		
		return false;
	}
}
