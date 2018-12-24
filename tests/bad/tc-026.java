class TestCase {
    public static void main(String[] args) {
        System.out.println(new TestCaseAtomic().Test());
    }
}

class TestCaseAtomic {
    public int Test() {
        return new int[3] + true;
    }
}
