package Model.Queries;

import java.io.Serializable;

public class RowQuery2 implements Serializable {
    int numReviews;
    int numUsers;

    public RowQuery2(int numReviews, int numUsers) {
        this.numReviews = numReviews;
        this.numUsers = numUsers;
    }

    public RowQuery2(RowQuery2 r) {
        this.numReviews = r.getNumReviews();
        this.numUsers = r.getNumUsers();
    }

    public int getNumReviews() {
        return numReviews;
    }

    public void setNumReviews(int numReviews) {
        this.numReviews = numReviews;
    }

    public int getNumUsers() {
        return numUsers;
    }

    public void setNumUsers(int numUsers) {
        this.numUsers = numUsers;
    }

    public RowQuery2 clone() {
        return new RowQuery2(this);
    }

}
