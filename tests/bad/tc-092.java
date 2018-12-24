class TestCase {
    public static void main(String[] args) {
        System.out.println(new TestCaseAtomic().Test());
    }
}

class TestCaseAtomic {
    public int Test() {
        int x;
        x[2] = 1;
        return 1;
    }
}
