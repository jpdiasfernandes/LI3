package Model;

import Model.Catalogs.*;

import java.io.*;
import java.util.Objects;

public class GestReviewsModel implements Serializable {
    private Catalog user;
    private Catalog reviews;
    private Catalog businesses;
    String fileUsers = "users_full.csv";
    String fileBusiness = "business_full.csv";
    String fileReviews = "reviews_1M.csv";

    public GestReviewsModel() {

        SavedBusinesses infoBusinesses;
        SavedUsers infoUsers;
        SavedReviews infoReviews;

        Users users = new Users();
        Businesses businesses = new Businesses();
        Reviews reviews = new Reviews();
        try {

            infoBusinesses = new SavedBusinesses("business_full.csv");
            infoReviews = new SavedReviews("reviews_1M.csv");
            infoUsers = new SavedUsers("users_full.csv");

            businesses = infoBusinesses.getBusinesses();
            reviews = infoReviews.getReviews();
            users = infoUsers.getUsers();
        }
        catch (LoadInfoException | IOException e) {
            System.out.println(e.getMessage());
        }

        this.user = users;
        this.reviews = reviews;
        this.businesses = businesses;
    }

    public GestReviewsModel(GestReviewsModel g) {
        this.user = g.getUser();
        this.reviews = g.getReviews();
        this.businesses = g.getBusinesses();
    }

    public GestReviewsModel(Catalog user, Catalog reviews, Catalog businesses) {
        this.user = user;
        this.reviews = reviews;
        this.businesses = businesses;
    }


    public void saveObjectFile(String filename)  {
        try {
            FileOutputStream fos = new FileOutputStream(filename);
            BufferedOutputStream bos = new BufferedOutputStream(fos);
            ObjectOutputStream oos = new ObjectOutputStream(bos);
            oos.writeObject(this);
            oos.flush();
            oos.close();
        }
        catch(IOException e) {
            e.printStackTrace();
        }
    }

    public static GestReviewsModel readObjectFile(String filename) {
        try {
            ObjectInputStream ois = new ObjectInputStream(new FileInputStream(filename));
            GestReviewsModel model = (GestReviewsModel) ois.readObject();
            ois.close();
            return model;
       }
        catch(IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
        return null;
    }

    public GestReviewsModel clone() {
        return new GestReviewsModel(this);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        GestReviewsModel that = (GestReviewsModel) o;
        return getUser().equals(that.getUser()) && getReviews().equals(that.getReviews()) && getBusinesses().equals(that.getBusinesses());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getUser(), getReviews(), getBusinesses());
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("GestReviewsModel {");
        sb.append("user = ").append(user);
        sb.append(", reviews = ").append(reviews);
        sb.append(", businesses = ").append(businesses);
        sb.append('}');
        return sb.toString();
    }

    // Fazer o encapsulamento
    public Catalog getUser() {
        return user;
    }

    public void setUser(Catalog user) {
        this.user = user;
    }

    public Catalog getReviews() {
        return reviews;
    }

    public void setReviews(Catalog reviews) {
        this.reviews = reviews;
    }

    public Catalog getBusinesses() {
        return businesses;
    }

    public void setBusinesses(Catalog businesses) {
        this.businesses = businesses;
    }

    String getFileUsers(){
        return fileUsers;
    }

    String getFileBusiness(){
        return fileBusiness;
    }

    String getFileReviews(){
        return fileReviews;
    }

    String filesToString(){
        return " " + getFileUsers() + ", " + getFileBusiness() + ", " + getFileReviews();
    }
}
