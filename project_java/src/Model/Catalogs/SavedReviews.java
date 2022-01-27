package Model.Catalogs;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.io.Serializable;

public class SavedReviews implements Parser, Serializable {
	private Reviews reviews;
	public SavedReviews(String filename) throws IOException, LoadInfoException {
		this.reviews = new Reviews();
		this.reviews = (Reviews) parser(filename);
	}
	public Catalog parser(String filename) throws IOException, LoadInfoException {
		Reviews parsed = this.reviews;
		Map<String, RowReviews> parsedTable = parsed.getMainTable();

		File f = new File(filename);
		BufferedReader br = new BufferedReader(new FileReader(f));
		String str;
		br.readLine();

		while ((str = br.readLine()) != null) {
			String[] data = str.split(";", 9);
			if (data.length == 9) {
				RowReviews r = new RowReviews(data[0], data[1], data[2],
						Float.parseFloat(data[3]), Integer.parseInt(data[4]),
						Integer.parseInt(data[5]), Integer.parseInt(data[6]), data[7],
						data[8]);
				RowReviews tmp = parsedTable.put(data[0], r);
			}

		}
		br.close();

		parsed.setMainTable(parsedTable);
		return parsed;
	}

	public Reviews getReviews() {
		return this.reviews;
	}
}
