package edu.jaen.java;
import java.util.Random;

class Lotto{
	
	int [] su = new int[6];
	
	//TODO 임의의 값 6개 저장
	public void input() {  
		// 구현해 봅시다.
		for(int i = 0; i < su.length; i++) {
			su[i] = uniqueValue(i);
		}
	}
	
	//TODO 배열 출력
	void print() {
		// 구현해 봅시다 
		for(int i = 0; i < su.length; i++) {
			System.out.print(su[i] + "\t");
		}
	}
	
	//main()....
	public static void main(String[] args) { 
		Lotto lo=new Lotto();
		lo.input();
		lo.print();
	}
	
	//TODO 중복되지 않는 값 찾아서 반환
	public int uniqueValue(int index) {
		
		int imsi;
		boolean eq;   //중복된 값 여부
		Random ran = new Random();
		
		do{
			eq = false;
			imsi = ran.nextInt(45)+1;
			
			for (int j = 0; j < index; j++ ){  
				
				if(imsi == su[j]){
					
			        eq = true ;
			        break;
				}
			}
		}while (eq);
		
		return imsi;
	}
}// end  class
