package Model.Catalogs;

import Exceptions.BusinessSemReview;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.Serializable;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.HashMap;
import java.util.Map;
import java.io.IOException;
import java.util.TreeMap;

public class Reviews implements Catalog, Serializable {

    private Map<String, RowReviews> mainTable;

    public Reviews() {
        this.mainTable = new HashMap<>();
    }

    public Reviews(Reviews r) {
        this.mainTable = r.getMainTable();
    }

    public Reviews(Map<String, RowReviews> mainTable) {
        this.mainTable = mainTable;
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("Reviews{");
        sb.append("mainTable=").append(mainTable);
        sb.append(", clone=").append(clone());
        sb.append('}');
        return sb.toString();
    }



    public Reviews clone() {
        return new Reviews(this);
    }


    public Map<String, RowReviews> getMainTable() {
        Map<String, RowReviews> res = new HashMap<>();

        for (Map.Entry<String, RowReviews> entry : this.mainTable.entrySet())
            res.put(entry.getKey(), entry.getValue().clone());

        return res;
    }

    public void setMainTable(Map<String, RowReviews> mainTable) {
        this.mainTable = mainTable;
    }

}
