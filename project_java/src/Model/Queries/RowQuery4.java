package Model.Queries;

import java.util.TreeSet;
import java.io.Serializable;

public class RowQuery4 implements Serializable {
    private int numReviewed;
    private float media;
    private int numUnique;

    public RowQuery4(int numReviewed, float media, int numUnique) {
        this.numReviewed = numReviewed;
        this.media = media;
        this.numUnique = numUnique;
    }

    public RowQuery4(RowQuery4 rq) {
        this.numReviewed = rq.getNumReviewed();
        this.media = rq.getMedia();
        this.numUnique = rq.getNumUnique();
    }

    public int getNumUnique() {
        return numUnique;
    }

    public void setNumUnique(int numUnique) {
        this.numUnique = numUnique;
    }

    public int getNumReviewed() {
        return numReviewed;
    }

    public void setNumReviewed(int numReviewed) {
        this.numReviewed = numReviewed;
    }

    public float getMedia() {
        return media;
    }

    public void setMedia(float media) {
        this.media = media;
    }


    public RowQuery4 clone() {
        return new RowQuery4(this);
    }




}


