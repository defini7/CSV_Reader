#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#pragma region LICENSE
/**
	BSD 3-Clause License
	Copyright (c) 2022, Alex
	All rights reserved.
	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	1. Redistributions of source code must retain the above copyright notice, this
	   list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright notice,
	   this list of conditions and the following disclaimer in the documentation
	   and/or other materials provided with the distribution.
	3. Neither the name of the copyright holder nor the names of its
	   contributors may be used to endorse or promote products derived from
	   this software without specific prior written permission.
	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/
#pragma endregion

#pragma region EXAMPLE
/**
	#include "defCSV_Reader.h"
	int main()
	{
		def::CSV_Reader* reader = new def::CSV_Reader("large.csv");
		reader->Print();
		std::cout << "\nTotal Cols: " << reader->GetTotalCols() << "\n" << "Total Rows: " << reader->GetTotalRows() << "\n\n";
		std::cout << reader->GetValue(0, 0) << "\n";
		delete reader;
		return 0;
	}
**/
#pragma endregion

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
			int row; // unsigned long long
			int col; // unsigned long long

			std::string value;
		};

		std::vector<sCell> vecCells;

		void Split(std::string sInput, std::vector<std::string>* vecOutput)
		{
			std::string s;

			for (int c = 0; c < sInput.length(); c++)
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

			for (int i = 0; !ifCsvFile.eof(); i++)
			{
				if (ifCsvFile.bad())
					return false;

				std::string s;
				std::vector<std::string> vecOut;
				sCell c;

				std::getline(ifCsvFile, s);
				Split(s, &vecOut);

				for (int j = 0; j < vecOut.size(); j++)
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

		std::string GetValue(int row, int col)
		{
			for (const auto cell : vecCells)
			{
				if (cell.row == row && cell.col == col)
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

		inline int GetTotalCols()
		{
			return vecCells[vecCells.size() - 1].col + 1;
		}

		inline int GetTotalRows()
		{
			return vecCells[vecCells.size() - 1].row + 1;
		}

	};
}
