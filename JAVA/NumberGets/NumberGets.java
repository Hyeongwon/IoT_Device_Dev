package edu.jaen.java.stmt;

import java.util.Random;
import java.util.Scanner;

/*
 * 1 ~ 100 ���� ���� ����ϴ�. 
 * ����ڷκ��� 1~100 ������ ���� �Է¹޽��ϴ�.
 * ��Һ�
 * ������ ���ݴ� ū �� �Է�
 */

public class NumberGets {
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Random random = new Random();
		int r = random.nextInt(100) + 1;
		Scanner s = new Scanner(System.in);
		
		long start = System.currentTimeMillis();
		System.out.println("1 ~ 100 ������ ���� �Է��ϼ��� : ");
		int num = s.nextInt();
		System.out.println("Random ���� : " + r + " , �Է°��� : " + num);
		
		int cnt = 1;
		
		// �ݺ���(������ ���� loop)
		while(true) {
			
			// ���ǹ� (�Է°��� ������ ��)
			if(num > r) System.out.println("�� ���� �� �Է�");
		
			else if(num < r) System.out.println("�� ū �� �Է�");
		
			else break;
			
			System.out.println("1 ~ 100 ������ ���� �Է��ϼ��� : ");
			num = s.nextInt();
			cnt++;
		}
		
		System.out.println("�Է� Ƚ�� : " + cnt);
		long end = System.currentTimeMillis();
		System.out.println( "���� �ð� : " + ( end - start ) / 1000.0 );
		
		s.close();
	}

}
