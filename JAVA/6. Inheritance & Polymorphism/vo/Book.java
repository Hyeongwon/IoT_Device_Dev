package edu.mds.vo;

public class Book {
	
	private String title;
	private String author;
	private String publisher;
	private String isbn;
	private String desc;
	
	public Book(String title, String author, String publisher, String desc, String isbn) {
		
		this.title = title;
		this.author = author;
		this.publisher = publisher;
		this.isbn = isbn;
		this.desc = desc;
	}
	
	public Book() {
		
	}
	
	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public String getAuthor() {
		return author;
	}

	public void setAuthor(String author) {
		this.author = author;
	}

	public String getPublisher() {
		return publisher;
	}

	public void setPublisher(String publisher) {
		this.publisher = publisher;
	}

	public String getIsbn() {
		return isbn;
	}

	public void setIsbn(String isbn) {
		this.isbn = isbn;
	}

	public String getDesc() {
		return desc;
	}

	public void setDesc(String desc) {
		this.desc = desc;
	}

	@Override
	public String toString() {
		return "Book [title=" + title + ", author=" + author + 
				", publisher=" + publisher + ", isbn=" + isbn + ", desc="
				+ desc + "]";
	}
	
	

}
