package Exceptions;

public class UserInexistente extends Exception {
    public UserInexistente() {
        super();
    }

    public UserInexistente(String msg) {
        super(msg);
    }
}
