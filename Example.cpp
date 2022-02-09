#include "defCSV_Reader.h"

int main()
{
	def::CSV_Reader* reader = new def::CSV_Reader("csvs/large.csv");

	reader->Print();

	std::cout << "\nTotal Cols: " << reader->GetTotalCols() << "\n" << "Total Rows: " << reader->GetTotalRows() << "\n\n";

	std::cout << reader->GetValue(0, 0) << "\n";

	return 0;
}
