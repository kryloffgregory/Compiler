class TestCase {
    public static void main(String[] args) {
        System.out.println(0);
    }
}

class Test1 extends Test2 {
    public int Foo() {
        return this.Bar();
    }
}

class Test2 extends Test3 {
}

class Test3 {
	public int Bar() {
		return 0;
	}
}