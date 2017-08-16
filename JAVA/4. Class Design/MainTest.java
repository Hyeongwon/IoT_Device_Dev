package edu.mds.vo;

public class MainTest {
	
	public static void main(String args[]) {
		
		// TODO Auto-generated method stub
		Customer c = new Customer("Josh", 19, false);
	
		/*c.name = "Josh";
		c.age = 19;
		c.gender = false;*/
		
		c.printfCustomer();
		
		Customer c2 = new Customer("Ann", 20, true);
		
		/*c2.name = "Ann";
		c2.age = 20;
		c2.gender = true;*/
		c2.printfCustomer();
	}

}
