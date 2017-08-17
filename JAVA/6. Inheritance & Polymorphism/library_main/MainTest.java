package edu.mds.main;

import java.util.Scanner;

import edu.mds.manager.BookArraymanager;
import edu.mds.vo.Megazine;

public class MainTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		BookArraymanager bam = new BookArraymanager();
		
		char input = 0;
		int cnt = 0;
		
		while(input != 'q') {
			
			System.out.println("1. 책 입력, 2. 잡지 입력, "
					+ "3. 책 출력, 4. 잡지 출력, 5. 검색, 6. 종료(q)");
			
			input = sc.next().charAt(0);
			System.out.println(cnt);
			
			switch (input) {
				
				case '1':
					System.out.println("Enter title, author, publisher, desc");
					bam.add(sc.next(), sc.next(), sc.next(), 
							sc.next(), Integer.toString(cnt++));
					break;
					
				case '2':
					System.out.println("Enter title, author, publisher, desc, year, date");
					bam.add(sc.next(), sc.next(), sc.next(), sc.next(), 
							Integer.parseInt(sc.next()), Integer.parseInt(sc.next()), Integer.toString(cnt++));		
					break;
					
				case '3':
					
					for(int i = 0; i < cnt; i++) {
						
						if(!((bam.bookList()[i]) instanceof Megazine))
							System.out.println(bam.bookList()[i].toString());
					}
					
					break;
					
				case '4':
					
					for(int i = 0; i < cnt; i++) {
						if((bam.bookList()[i] instanceof Megazine))
							System.out.println(bam.bookList()[i].toString());
					}
					
					break;
					
				case '5':
					
					System.out.println("검색할 title name");
					String title = sc.next();
					System.out.println("검색 결과 : " + bam.search(title));
					
					break;
					
				case '6':
					
					input = 'q';
					break;
					
				default:
					break;
			}
		}
		
		sc.close();
	}

}
