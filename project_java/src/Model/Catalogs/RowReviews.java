package Model.Catalogs;

import java.time.LocalDate;
import java.util.Objects;
import java.io.Serializable;

public class RowReviews implements Serializable {
    private String review_id;
    private String user_id;
    private String business_id;
    private float stars;
    private int useful;
    private int funny;
    private int cool;
    private String date;
    private String text;


    public RowReviews() {
        this.review_id = "";
        this.user_id = "";
        this.business_id = "";
        this.stars = 0;
        this.useful = 0;
        this.funny = 0;
        this.cool = 0;
        this.date = "";
        this.text = "";
    }

    public RowReviews(RowReviews r) {
        this.review_id = r.getReview_id();
        this.user_id = r.getUser_id();
        this.business_id = r.getBusiness_id();
        this.stars = r.getStars();
        this.useful = r.getUseful();
        this.funny = r.getFunny();
        this.cool = r.getCool();
        this.date = r.getDate();
        this.text = r.getText();
    }

    public RowReviews(String review_id, String user_id, String business_id, float stars, int useful, int funny, int cool, String date, String text) {
        this.review_id = review_id;
        this.user_id = user_id;
        this.business_id = business_id;
        this.stars = stars;
        this.useful = useful;
        this.funny = funny;
        this.cool = cool;
        this.date = date;
        this.text = text;
    }

    public RowReviews clone() {
        return new RowReviews(this);
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("RowReviews{");
        sb.append("review_id='").append(review_id).append('\'');
        sb.append(", user_id='").append(user_id).append('\'');
        sb.append(", business_id='").append(business_id).append('\'');
        sb.append(", stars=").append(stars);
        sb.append(", useful=").append(useful);
        sb.append(", funny=").append(funny);
        sb.append(", cool=").append(cool);
        sb.append(", date=").append(date);
        sb.append(", text='").append(text).append('\'');
        sb.append('}');
        return sb.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        RowReviews that = (RowReviews) o;
        return Float.compare(that.getStars(), getStars()) == 0 && getUseful() == that.getUseful()
                && getFunny() == that.getFunny() && getCool() == that.getCool() && getReview_id().equals(that.getReview_id())
                && getUser_id().equals(that.getUser_id()) && getBusiness_id().equals(that.getBusiness_id()) && getDate().equals(that.getDate())
                && getText().equals(that.getText());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getReview_id(), getUser_id(), getBusiness_id(), getStars(), getUseful(), getFunny(), getCool(), getDate(), getText());
    }

    public String getReview_id() {
        return review_id;
    }

    public void setReview_id(String review_id) {
        this.review_id = review_id;
    }

    public String getUser_id() {
        return user_id;
    }

    public void setUser_id(String user_id) {
        this.user_id = user_id;
    }

    public String getBusiness_id() {
        return business_id;
    }

    public void setBusiness_id(String business_id) {
        this.business_id = business_id;
    }

    public float getStars() {
        return stars;
    }

    public void setStars(float stars) {
        this.stars = stars;
    }

    public int getUseful() {
        return useful;
    }

    public void setUseful(int useful) {
        this.useful = useful;
    }

    public int getFunny() {
        return funny;
    }

    public void setFunny(int funny) {
        this.funny = funny;
    }

    public int getCool() {
        return cool;
    }

    public void setCool(int cool) {
        this.cool = cool;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }
}
