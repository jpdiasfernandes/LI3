#include "../queries/includes/queries.h"
#include "../table/includes/table.h"
#include "../pagination/includes/show.h"

int main () {

	SGR sgr = load_sgr("tests/users","tests/business","tests/reviews");

	/*querie 3
	TABLE * t = business_info (sgr, "business_id_3");
	*/

	/* querie 4*/
	TABLE *t4 = businesses_reviewed (sgr, "user_id_3");
	
	/*querie 5 */
	TABLE *t5 = businesses_with_starts_and_city (sgr, 3, "cidade_5");
	
	/* table pagination */
	table_pagination (get_table_users (get_users(sgr)));
	table_pagination (get_table_business (get_businesses(sgr)));
	table_pagination (get_table_reviews (get_reviews(sgr)));
	table_pagination (t4);
	table_pagination (t5);

	/* table to file with delim */
	FILE * fp = fopen ("tbf_test", "w");
	table_to_file_delim (fp, t5,";");
	fclose (fp);
}
