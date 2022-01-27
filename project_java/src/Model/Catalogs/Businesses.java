package Model.Catalogs;

import java.io.*;
import java.util.HashMap;
import java.util.Map;


public class Businesses implements Catalog, Serializable {
    private Map<String, RowBusinesses> mainTable;

    public Businesses() {
        this.mainTable = new HashMap<>();
    }

    public Businesses(Businesses u) {
        this.mainTable = u.getMainTable();
    }

    public Businesses(Map<String, RowBusinesses> mainTable) {
        this.mainTable = mainTable;
    }

    public Map<String, RowBusinesses> getMainTable() {
        Map<String, RowBusinesses> res = new HashMap<>();

        for (Map.Entry<String, RowBusinesses> entry : this.mainTable.entrySet())
            res.put(entry.getKey(), entry.getValue().clone());

        return res;
    }

    public void setMainTable(Map<String, RowBusinesses> mainTable) {
        this.mainTable = mainTable;
    }


}
