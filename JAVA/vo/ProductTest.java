package edu.mds.vo;

import jdk.nashorn.internal.ir.debug.ObjectSizeCalculator;

public class ProductTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		//int pcode, String pname, int price, int qunat, String pdesc
		Product p = new Product(1, "apple", 15, 10, "this is an apple");
		
		System.out.println(p.toString());
		
		
	}

}
