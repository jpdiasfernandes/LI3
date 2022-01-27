package Model.Catalogs;

import java.util.Map;
import java.util.Objects;
import java.io.Serializable;

public class RowBusinesses implements Serializable {
    private String business_id;
    private String name;
    private String city;
    private String state;
    private String categories;


    public RowBusinesses() {
        this.business_id = "";
        this.name = "";
        this.city = "";
        this.state = "";
        this.categories = "";
    }

    public RowBusinesses(RowBusinesses r) {
        this.business_id = r.getBusiness_id();
        this.name = r.getName();
        this.city = r.getCity();
        this.state = r.getState();
        this.categories = r.getCategories();
    }

    public RowBusinesses(String business_id) {
        this.business_id = business_id;
    }

    public RowBusinesses(String business_id, String name, String city, String state, String categories) {
        this.business_id = business_id;
        this.name = name;
        this.city = city;
        this.state = state;
        this.categories = categories;
    }

    public RowBusinesses clone() {
        return new RowBusinesses(this);
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("RowBusinesses{");
        sb.append("business_id='").append(business_id).append('\'');
        sb.append(", name='").append(name).append('\'');
        sb.append(", city='").append(city).append('\'');
        sb.append(", state='").append(state).append('\'');
        sb.append(", categories='").append(categories).append('\'');
        sb.append('}');
        return sb.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        RowBusinesses that = (RowBusinesses) o;
        return getBusiness_id().equals(that.getBusiness_id()) && getName().equals(that.getName()) && getCity().equals(that.getCity())
                && getState().equals(that.getState()) && getCategories().equals(that.getCategories());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getBusiness_id(), getName(), getCity(), getState(), getCategories());
    }

    public String getBusiness_id() { return business_id; }

    public void setBusiness_id(String business_id) { this.business_id = business_id; }

    public String getName() { return name; }

    public void setName(String name) { this.name = name; }

    public String getCity() { return city; }

    public void setCity(String city) { this.city = city; }

    public String getState() { return state; }

    public void setState(String state) { this.state = state; }

    public String getCategories() { return categories; }

    public void setCategories(String categories) { this.categories = categories; }
}
