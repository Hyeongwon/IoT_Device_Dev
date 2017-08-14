package edu.jaen.java.stmt;

import java.util.Random;
import java.util.Scanner;

/*
 * 1 ~ 100 랜덤 값을 얻습니다. 
 * 사용자로부터 1~100 사이의 값을 입력받습니다.
 * 대소비교
 * 작으면 조금더 큰 값 입력
 */

public class NumberGets {
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Random random = new Random();
		int r = random.nextInt(100) + 1;
		Scanner s = new Scanner(System.in);
		
		long start = System.currentTimeMillis();
		System.out.println("1 ~ 100 사이의 값을 입력하세요 : ");
		int num = s.nextInt();
		System.out.println("Random 값은 : " + r + " , 입력값은 : " + num);
		
		int cnt = 1;
		
		// 반복문(맞을때 까지 loop)
		while(true) {
			
			// 조건문 (입력값과 랜덤값 비교)
			if(num > r) System.out.println("더 작은 값 입력");
		
			else if(num < r) System.out.println("더 큰 값 입력");
		
			else break;
			
			System.out.println("1 ~ 100 사이의 값을 입력하세요 : ");
			num = s.nextInt();
			cnt++;
		}
		
		System.out.println("입력 횟수 : " + cnt);
		long end = System.currentTimeMillis();
		System.out.println( "실행 시간 : " + ( end - start ) / 1000.0 );
		
		s.close();
	}

}
