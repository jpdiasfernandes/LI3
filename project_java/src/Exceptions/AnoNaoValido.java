package Exceptions;

public class AnoNaoValido extends Exception {
    public AnoNaoValido (){
        super();
    }
    public AnoNaoValido (String msg) {
        super(msg);
    }
}
