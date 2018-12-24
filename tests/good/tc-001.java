class TestCase {
    public static void main(String[] args) {
        while (false) {}
    }
}

class UserType {
    public int Foo() {
        return this.Bar();
    }

    public int Bar() {
        return 0;
    }
}
