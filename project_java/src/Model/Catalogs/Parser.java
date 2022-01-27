package Model.Catalogs;

import java.io.IOException;
import java.io.Serializable;

public interface Parser extends Serializable {
	Catalog parser(String filename) throws IOException, LoadInfoException;
}
