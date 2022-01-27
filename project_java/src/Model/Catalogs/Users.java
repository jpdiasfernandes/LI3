package Model.Catalogs;


import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;

public class Users implements Catalog, Serializable {
    private Map<String, RowUsers> mainTable;

    public void parser(String fich) {;}

    public Users() {
        this.mainTable = new HashMap<>();
    }

    public Users(Users u) {
        this.mainTable = u.getMainTable();
    }


    public Users(Map<String, RowUsers> mainTable) {
        setMainTable(mainTable);
    }

    public Users clone() {
        return new Users(this);
    }

    public Map<String, RowUsers> getMainTable() {
        Map<String, RowUsers> res = new HashMap<>();

        for (Map.Entry<String, RowUsers> entry : this.mainTable.entrySet())
            res.put(entry.getKey(), entry.getValue().clone());

        return res;
    }

    public void setMainTable(Map<String, RowUsers> mainTable) {
        this.mainTable = mainTable;
    }

}
