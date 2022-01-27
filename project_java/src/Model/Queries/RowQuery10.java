package Model.Queries;
import java.io.Serializable;

public class RowQuery10 implements Serializable {
    private int numReviews;
    private int numBusinesses;
    private float media;

    public RowQuery10(int numReviews, int numBusinesses, float media) {
        this.numReviews = numReviews;
        this.numBusinesses = numBusinesses;
        this.media = media;
    }

    public RowQuery10(RowQuery10 row) {
        this.media = row.getMedia();
        this.numBusinesses = row.getNumBusinesses();
        this.numReviews = row.getNumReviews();
    }


    public int getNumReviews() {
        return numReviews;
    }

    public void setNumReviews(int numReviews) {
        this.numReviews = numReviews;
    }

    public int getNumBusinesses() {
        return numBusinesses;
    }

    public void setNumBusinesses(int numBusinesses) {
        this.numBusinesses = numBusinesses;
    }

    public float getMedia() {
        return media;
    }

    public void setMedia(float media) {
        this.media = media;
    }

    public RowQuery10 clone () {
        return new RowQuery10(this);
    }
}
