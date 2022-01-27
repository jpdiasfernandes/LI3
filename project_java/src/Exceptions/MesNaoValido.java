package Exceptions;

public class MesNaoValido extends Exception{
    public MesNaoValido() {
        super();
    }

    public MesNaoValido(String msg) {
        super(msg);
    }
}
