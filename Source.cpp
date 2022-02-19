#define _CRT_SECURE_NO_WARNINGS
#include "CSV_Reader.hpp"

int main() {
	def::CSV_Reader* pReader = nullptr;

	std::cout << "DEFINIT CSV READER v0.1\n";

	while (1) {
		std::cout << "> ";

		std::string s;
		std::getline(std::cin, s);

		std::vector<char*> vecInput;

		char* word = strtok((char*)s.c_str(), " ");
		
		while (word != NULL) {
			vecInput.push_back(word);
			word = strtok(NULL, " ");
		}

		if (strcmp(vecInput[0], "load") == 0) {
			pReader = new def::CSV_Reader(vecInput[1]);
		}
		else if (strcmp(vecInput[0], "print") == 0) {
			pReader->Print();
		}
		else if (strcmp(vecInput[0], "get") == 0) {
			if (strcmp(vecInput[1], "col") == 0) {
				std::cout << pReader->GetTotalCols() << "\n";
			} else if (strcmp(vecInput[1], "row") == 0) {
				std::cout << pReader->GetTotalRows() << "\n";
			} else {
				std::string value = pReader->GetValue(std::atoi(vecInput[1]), std::atoi(vecInput[2]));
				std::cout << value << "\n";
			}
		}
		else if (strcmp(vecInput[0], "clear") == 0) {
			system("cls");
		}
		else {
			std::cout << "Error: unexpected command.\n";
		}
	}

	return 0;
}
