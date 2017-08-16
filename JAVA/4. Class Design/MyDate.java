package edu.mds.vo;

public class MyDate {
	
	private int year;
	private int month;
	private int day;
	
	public int getYear() {
		return year;
	}
	
	public void setYear(int year) {
		this.year = year;
	}

	public int getMonth() {
		return month;
	}

	public void setMonth(int month) {
		
		if(1 < month || month > 12) {
			
			System.out.println("다시 월을 입력하세요 1 ~ 12");
			return;
		}
		
		this.month = month;
	}

	public int getDay() {
		return day;
	}

	public void setDay(int day) {
		this.day = day;
	}

	void printDate() {
		System.out.println("year = " + year + ", month = " + month + ", day = " + day);
	}
}
