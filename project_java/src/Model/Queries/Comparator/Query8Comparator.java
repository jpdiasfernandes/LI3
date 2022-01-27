package Model.Queries.Comparator;

import Model.Queries.RowQuery8;

import java.util.Comparator;

public class Query8Comparator implements Comparator<RowQuery8> {
    public int compare(RowQuery8 r1, RowQuery8 r2) {
        if (r1.getNumBus() == r2.getNumBus())
            return r1.getUserId().compareTo(r2.getUserId());
        else return r2.getNumBus() - r1.getNumBus();
    }
}
