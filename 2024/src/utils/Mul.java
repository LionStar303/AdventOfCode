package utils;

public class Mul {
    private int a;
    private int b;
    private boolean valid;

    public Mul(int a, int b, boolean valid) {
        this.a = a;
        this.b = b;
        this.valid = valid;
    }
    public int getP() {
        return a*b;
    }
    public boolean isValid() {
        return valid;
    }
}