package snake;

import java.awt.Dimension;
import java.awt.Point;

public class Service {
	static public boolean isInsideBox(int x, int y, Point loc, Dimension dim) {
		boolean isInside = false;
		if (x > loc.x && x < loc.x + dim.width &&
			y > loc.y && y < loc.y + dim.height) isInside = true;
		
		return isInside;
	}
}
