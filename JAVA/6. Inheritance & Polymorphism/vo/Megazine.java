package edu.mds.vo;

public class Megazine extends Book {
	
	private int year;
	private int date;
	
	public Megazine(String title, String author, String publisher, String isbn, 
			String desc, int year, int date) {
		
		super(title, author, publisher, isbn, desc);
		this.year = year;
		this.date = date;
	}
	
	public Megazine() {
		
	}

	public int getYear() {
		return year;
	}

	public void setYear(int year) {
		this.year = year;
	}

	public int getDate() {
		return date;
	}

	public void setDate(int date) {
		this.date = date;
	}

	@Override
	public String toString() {
		return "Megazine [year=" + year + ", date=" + date + ", Title=" + getTitle() + ", Author="
				+ getAuthor() + ", Publisher=" + getPublisher() + ", Isbn=" + getIsbn() + ", Desc="
				+ getDesc() + "]";
	}

	
	
	

}
