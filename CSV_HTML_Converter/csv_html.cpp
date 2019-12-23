#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <memory>
#include <vector>

using namespace std;

#define SIZE 80000000
char write_buffer[SIZE];


class CSV_HTML {
private:
	ifstream inFile;
	ofstream outFile;
	string ifname = "C://Users//geeky//Desktop//test_enormous.csv";
	string ofname = "C://Users//geeky//Desktop//output.html";
	string preTag = "<!DOCTYPE html>\n<html>\n\t<body>\n\t\t<table>\n";
	string postTag = "\t\t</table>\n\t</body>\n</html>\n";
	string preRow = "\t\t\t<tr>";
	string postRow = "</tr>";
	string preHeading = "<th>";
	string postHeading = "</th>";
	string preCell = "<td>";
	string postCell = "</rd>";
	string line;
	vector <string> rows;
	unique_ptr<char[]> buffer;
	string_view svBuffer;

	void getcsvLine();
	void getHeaders();
	void getRows();
public:
	void readFile();
	void writeFile();
	void processFile();
};

void CSV_HTML::getcsvLine() {
	auto lineend = svBuffer.find("\n");
	if (lineend == string_view::npos) {
		line = static_cast<string>(svBuffer.substr(0, string_view::npos));
		svBuffer = "";
		return;
	}
	line = static_cast<string>(svBuffer.substr(0, lineend));
	svBuffer.remove_prefix(lineend + 1);
	return;
}

void CSV_HTML::getHeaders() {
	size_t start = 0;
	string row = preRow;
	getcsvLine();
	while (true) {
		auto end = line.find(",", start);
		if (end != string::npos) {
			row += preHeading + line.substr(start, end - start) + postHeading;
			start = end + 1;;
		}
		else {
			row += preHeading + line.substr(start, end) + postHeading;
			row += postRow;
			rows.emplace_back(row);
			return;
		}
			
	}
}

void CSV_HTML::getRows() {
	while (!svBuffer.empty()) {
		string row = preRow;
		size_t start = 0;
		getcsvLine();
		while (true) {
			auto end = line.find(",", start);
			if (end != string::npos) {
				row += preCell + line.substr(start, end - start) + postCell;
				start = end + 1;;
			}
			else {
				row += preCell + line.substr(start, end) + postCell;
				row += postRow;
				rows.emplace_back(row);
				break;
			}
		}
	}
	return;
}

void CSV_HTML::readFile() {
	inFile.open(ifname);
	if (!inFile.is_open()) {
		cout << "Error opening file";
		exit(1);
	}
	inFile.seekg(0, inFile.end);
	const auto length = static_cast<size_t>(inFile.tellg()) + 1;
	inFile.seekg(0, inFile.beg);
	buffer = make_unique<char[]>(length);
	memset(buffer.get(), 0, length);
	inFile.read(buffer.get(), length);
	svBuffer = buffer.get();
	inFile.close();
	return;
}

void CSV_HTML::processFile() {
	getHeaders();
	getRows();
	return;
}

void CSV_HTML::writeFile() {
	outFile.open(ofname);
	outFile.rdbuf()->pubsetbuf(write_buffer, SIZE);
	outFile << preTag;
	for (auto r : rows)
		outFile << r << '\n';
	outFile << postTag;
	outFile.close();
}

int main() {
	CSV_HTML converter;
	converter.readFile();
	converter.processFile();
	converter.writeFile();
	return 0;
}