
public class OverloadTest {
	
	int plus(int a, int b) {
		
		return a + b;
	}

	float plus(int a, float b) {
		
		return a + b;
	}
	
	public static void main(String args[]) {
		
		OverloadTest ol = new OverloadTest();
		int plus = ol.plus(10, 20);
		System.out.println(plus);
		
		plus = (int) ol.plus(10,  20.0f);
		System.out.println(plus);
	}
}
