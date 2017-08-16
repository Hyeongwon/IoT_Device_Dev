package edu.jaen.java;
import java.util.Random;

class Lotto{
	
	int [] su = new int[6];
	
	//TODO ������ �� 6�� ����
	public void input() {  
		// ������ ���ô�.
		for(int i = 0; i < su.length; i++) {
			su[i] = uniqueValue(i);
		}
	}
	
	//TODO �迭 ���
	void print() {
		// ������ ���ô� 
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
	
	//TODO �ߺ����� �ʴ� �� ã�Ƽ� ��ȯ
	public int uniqueValue(int index) {
		
		int imsi;
		boolean eq;   //�ߺ��� �� ����
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
