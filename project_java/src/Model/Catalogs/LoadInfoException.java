package Model.Catalogs;
import java.io.Serializable;

public class LoadInfoException extends Exception implements Serializable {
    public LoadInfoException() {
        super();
    }

    public LoadInfoException(String msg) {
        super(msg);
    }
}
