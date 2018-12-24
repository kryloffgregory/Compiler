class TestCase {
    public static void main(String[] args) {
        System.out.println(0);
    }
}

class TestCaseAtomic extends TestCaseNonAtomic {
}

class TestCaseNonAtomic extends TestCaseAtomic{
}
