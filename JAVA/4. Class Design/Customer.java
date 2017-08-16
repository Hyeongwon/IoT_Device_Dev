package edu.mds.vo;

public class Customer {

	String name;
	int age;
	boolean gender;
	
	public Customer(String _name, int _age, boolean _gender) {
		
		System.out.println("Construct...");
		
		this.name = _name;
		this.age = _age;
		this.gender = _gender;
	}
	
	public Customer() {
		
	}
	
	String getGender() {
		
		if(this.gender) return "Woman";
		
		else return "Man";
		
	}
	
	public void printfCustomer() {
		
		System.out.println("name : " + name + ", age : " + age + 
				", gender : " + ((gender) ? "woman" : "man"));
	}
}
