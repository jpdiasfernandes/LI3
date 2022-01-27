package Model.Catalogs;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Map;
import java.io.Serializable;

public class SavedBusinesses implements Parser, Serializable {
	private Businesses businesses;
	public SavedBusinesses(String filename) throws IOException, LoadInfoException{
		this.businesses = new Businesses();
		this.businesses = (Businesses) parser(filename);
	}

	public Catalog parser(String filename) throws IOException, LoadInfoException {
		Businesses parsed = this.businesses;
		Map<String, RowBusinesses> parsedTable = parsed.getMainTable();

		File f = new File(filename);
		BufferedReader br = new BufferedReader(new FileReader(f));
		String str;
		br.readLine();

		while ((str = br.readLine())  != null) {
			String[] data = str.split(";", 5);

			if(data.length == 5) {
				RowBusinesses r = new RowBusinesses(data[0], data[1], data[2], data[3], data[4]);
				RowBusinesses tmp = parsedTable.put(data[0],r);
				parsedTable.put(data[0], r.clone());
			}

		}
		br.close();
		parsed.setMainTable(parsedTable);
		return parsed;
	}

	public Businesses getBusinesses() {
		return this.businesses;
	}
}
