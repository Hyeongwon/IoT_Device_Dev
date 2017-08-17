package edu.mds.animal;

public class Dog extends Animal{
	
	@Override
	public void move() {
		// TODO Auto-generated method stub
		System.out.println("개가 움직입니다.");
	}
	
	public void bark() {
		
		System.out.println("개가 짖습니다.");
	}
}
