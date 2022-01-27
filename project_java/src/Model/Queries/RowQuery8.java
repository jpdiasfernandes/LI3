package Model.Queries;
import java.io.Serializable;


public class RowQuery8 implements Serializable {
    private String userId;
    private int numBus;

    public RowQuery8(String userId, int numBus) {
        this.userId = userId;
        this.numBus = numBus;
    }

    public RowQuery8(RowQuery8 row) {
        this.userId = row.getUserId();
        this.numBus = row.getNumBus();
    }

    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

    public int getNumBus() {
        return numBus;
    }

    public void setNumBus(int numBus) {
        this.numBus = numBus;
    }

    public RowQuery8 clone() {
        return new RowQuery8(this);
    }

}


