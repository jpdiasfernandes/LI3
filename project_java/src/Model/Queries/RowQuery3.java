package Model.Queries;

import java.io.Serializable;

public class RowQuery3 implements Serializable {
    private int mes;
    private int numReviews;
    private int numBusinesses;
    private float media;

    public RowQuery3(int mes, int numReviews, int numBusinesses, float media) {
        this.mes = mes;
        this.numReviews = numReviews;
        this.numBusinesses = numBusinesses;
        this.media = media;
    }

    public RowQuery3(RowQuery3 row) {
        this.media = row.getMedia();
        this.mes = row.getMes();
        this.numBusinesses = row.getNumBusinesses();
        this.numReviews = row.getNumReviews();
    }

    public int getMes() {
        return mes;
    }

    public void setMes(int mes) {
        this.mes = mes;
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

    public RowQuery3 clone () {
        return new RowQuery3(this);
    }
}
