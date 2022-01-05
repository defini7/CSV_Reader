#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>

namespace def
{
	class CSV_Reader
	{
	public:
		CSV_Reader(std::string file)
		{
			sFileName = file;
			Load();
		}

	private:
		std::ifstream ifCsvFile;
		std::string sFileName;

		struct sCell
		{
			uint64_t row; // unsigned long long
			uint64_t col; // unsigned long long

			std::string value;
		};

		std::vector<sCell> vecCells;

		void Split(std::string sInput, std::vector<std::string>* vecOutput)
		{
			std::string s;

			for (uint64_t c = 0; c < sInput.length(); c++)
			{
				switch (sInput[c])
				{
				case ',':
				{
					vecOutput->push_back(s);
					s.clear();
				}
				break;

				case ' ':
					break;

				default:
					s.push_back(sInput[c]);
				}
			}

		}

		bool Load()
		{
			if (!ifCsvFile.is_open())
				ifCsvFile.open(sFileName, std::ios::binary);

			if (!ifCsvFile.is_open())
				return false;

			for (uint64_t i = 0; !ifCsvFile.eof(); i++)
			{
				if (ifCsvFile.bad())
					return false;

				std::string s;
				std::vector<std::string> vecOut;
				sCell c;

				std::getline(ifCsvFile, s);
				Split(s, &vecOut);

				for (uint64_t j = 0; j < vecOut.size(); j++)
				{
					c.col = j;
					c.row = i;

					c.value = vecOut[j];

					vecCells.push_back(c);
				}

				c.col++;
				c.value = '\n';

				vecCells.push_back(c);
			}

			vecCells.pop_back(); vecCells.pop_back();

			ifCsvFile.close();

			return true;
		}

	public:

		std::string GetValue(uint64_t col, uint64_t row)
		{
			for (const auto cell : vecCells)
			{
				if (col == cell.col && row == cell.row)
					return cell.value;
			}
		}

		void Print()
		{
			std::cout << "1 ";

			for (const auto cell : vecCells)
			{
				if (cell.value == "\n")
					std::cout << "\n" << cell.row + 2 << " ";
				else
					std::cout << " " << cell.value;
			}
		}

		uint64_t GetTotalCols()
		{
			return vecCells[vecCells.size() - 1].col + 1;
		}

		uint64_t GetTotalRows()
		{
			return vecCells[vecCells.size() - 1].row + 1;
		}

	};
}
