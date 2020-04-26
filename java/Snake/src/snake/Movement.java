package snake;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Movement implements KeyListener {
	private Snake snake = new Snake();
	
	public void setDirection(Snake s) {
		// to pass by reference
		snake = s;
	}
	
	public void keyPressed(KeyEvent k) {
		final String key = k.getKeyText(k.getKeyCode());
		if (snake.getDirection() != key.toLowerCase()) 
			snake.setIntersections();
		
//		System.out.println(snake.isOppositeDir(key.toLowerCase()));
		if (!snake.isOppositeDir(key.toLowerCase())) snake.setDirection(key.toLowerCase());
	}
	
	public void keyTyped(KeyEvent k) {
	}

	@Override
	public void keyReleased(KeyEvent arg0) {
	}
}
