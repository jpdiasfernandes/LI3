package Model.Queries;
import java.util.Set;
import java.util.Map;
import java.io.Serializable;

public class RowQuery7 implements Serializable {
    private String city;
    private int num_reviews;
    private Set<Map.Entry<String, Integer>> top3;

    public RowQuery7(String city, int num_reviews, Set<Map.Entry<String, Integer>> top3) {
        this.city = city;
        this.num_reviews = num_reviews;
        this.top3 = top3;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public int getNum_reviews() {
        return num_reviews;
    }

    public void setNum_reviews(int num_reviews) {
        this.num_reviews = num_reviews;
    }

    public Set<Map.Entry<String, Integer>> getTop3() {
        return top3;
    }

    public void setTop3(Set<Map.Entry<String, Integer>> top3) {
        this.top3 = top3;
    }
}
