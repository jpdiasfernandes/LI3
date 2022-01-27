package Model.Queries.Query9;

import java.io.Serializable;

public class RowQuery9Tuplas implements Serializable {
    String name;
    float stars;

    public RowQuery9Tuplas(String name, float stars) {
        this.name = name;
        this.stars = stars;
    }

    public RowQuery9Tuplas(RowQuery9Tuplas tupla) {
        this.name = tupla.getName();
        this.stars = tupla.getStars();
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public float getStars() {
        return stars;
    }

    public void setStars(float stars) {
        this.stars = stars;
    }

    @Override
    public String toString() {
        return "    > UserId: " +
                name + "» Stars: " +
                stars + "\n";
    }
}
