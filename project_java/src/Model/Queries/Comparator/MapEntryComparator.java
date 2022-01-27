package Model.Queries.Comparator;
import java.util.Map;
import java.util.Comparator;
import java.io.Serializable;

public class MapEntryComparator implements Comparator<Map.Entry<String, Integer>>, Serializable {

    public int compare(Map.Entry<String, Integer> m1, Map.Entry<String, Integer> m2) {
        int r = 0;

        if (m2.getValue().equals(m1.getValue()))
            return m2.getKey().compareTo(m1.getKey());

        else
            return m2.getValue() - m1.getValue();
    }

}
