public class Tester {

	public static int get_int(int [] arry) {
		return arry[3];
	}

	public static void main() {
		int [] x;
		x = new int[48];
		x[3] = 56;
		get_int(x);
	}

	public static void main(String args[]) {
		main();
	}	
}
