package Model.Catalogs;

import java.io.*;
import java.util.*;


public class RowUsers implements Serializable {
    private String user_id;
    private String name;
    private List<String> friends;

    public RowUsers() {
        this.user_id = "";
        this.name = "";
        this.friends = new ArrayList<>();
    }

    public RowUsers(RowUsers r) {
        this.user_id = r.getUser_id();
        this.name = r.getName();
        this.friends = r.getFriends();
    }

    public RowUsers(String user_id, String name, List<String> friends) {
        this.user_id = user_id;
        this.name = name;
        this.friends = friends;
    }

    public RowUsers clone() {
        return new RowUsers(this);
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("RowUsers{");
        sb.append("user_id='").append(user_id).append('\'');
        sb.append(", name='").append(name).append('\'');
        sb.append(", friends=").append(friends);
        sb.append('}');
        return sb.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        RowUsers rowUsers = (RowUsers) o;
        return getUser_id().equals(rowUsers.getUser_id()) && getName().equals(rowUsers.getName()) && getFriends().equals(rowUsers.getFriends());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getUser_id(), getName(), getFriends());
    }

    public String getUser_id() { return user_id; }

    public void setUser_id(String user_id) { this.user_id = user_id; }

    public String getName() { return name; }

    public void setName(String name) { this.name = name; }

    public List<String> getFriends() {
        return new ArrayList<>(this.friends);
    }

    public void setFriends(List<String> friends) {
        this.friends = new ArrayList<>(friends);
    }
}
