package edu.mds.manager;

import edu.mds.vo.Book;
import edu.mds.vo.Megazine;

public class BookArraymanager {
	
	private Book[] books;
	
	public BookArraymanager() {
		
		books = new Book[10];
	}
	
	public void add(String title, String author, 
			String publisher, String desc, String isbn) {
		
		books[Integer.parseInt(isbn)] = new Book(title, author, publisher, desc, isbn);
	}
	
	public void add(String title, String author, 
			String publisher, String desc, int year, int date,  String isbn) {
		
		books[Integer.parseInt(isbn)] = new Megazine(title, author, publisher, desc, isbn, year, date);
	}
	
	public Book[] bookList() {
		
		return books;
	}
	
	public Book[] MegazineList() {
		
		return books;
	}
	
	public String search(String title) {
		
		for(int i = 0; books[i] != null; i++) {
			System.out.println(books[i].getTitle());
			if(books[i].getTitle().equals(title)) {
				
				return books[i].getIsbn();
			}
		}
		
		return "No Search Result";
	}

}
