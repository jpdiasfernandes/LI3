package Model.Queries;

import java.util.Set;

import java.io.Serializable;

public class RowQuery6 implements Serializable {
    private int numDistinctUsers;
    private String businessId;
    private int numReviews;

    public RowQuery6(String businessId, int numDistinctUsers, int numReviews) {
        this.numDistinctUsers = numDistinctUsers;
        this.businessId = businessId;
        this.numReviews = numReviews;
    }

    public int getNumDistinctUsers() {
        return numDistinctUsers;
    }

    public void setNumDistinctUsers(int numDistinctUsers) {
        this.numDistinctUsers = numDistinctUsers;
    }

    public String getBusinessId() { return businessId; }

    public void setBusinessId(String businessId) { this.businessId = businessId; }

    public int getNumReviews() { return numReviews; }

    public void setNumReviews(int numReviews) { this.numReviews = numReviews; }
}
