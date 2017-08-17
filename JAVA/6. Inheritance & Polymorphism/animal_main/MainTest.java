package edu.mds.main;

import edu.mds.animal.Animal;
import edu.mds.animal.Bird;
import edu.mds.animal.Dog;
import edu.mds.animal.Human;
import edu.mds.animal.Superman;

public class MainTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Dog d = new Dog();
		Bird b = new Bird();
		Human h = new Human();
		Superman s = new Superman();
		
		toMove(d);
	}
	
	public static void toMove(Animal a) {
		a.move();
	}

}
