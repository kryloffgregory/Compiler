class TestCase {
    public static void main(String[] args) {
        while (false) {}
    }
}

class UserType extends Barer {
    public int Foo() {
        return this.Bar();
    }
}

class Barer {
    public int Bar() {
        return 0;
    }
}
