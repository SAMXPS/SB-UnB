package custom;

public class StaticTest {
    
    public static int static_field = 0;
    public int instance_field = 0;

    public static void static_method() {
        static_field++;
    }

    public void instance_method() {
        instance_field++;
    }

    public static void main(String[] args) {
        StaticTest.static_method();
        StaticTest test = new StaticTest();
        test.instance_method();
    }

}