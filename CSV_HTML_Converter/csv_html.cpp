/*Input:
column1,column2,column3
a,123,abc123
b,234,bcd234
c,345,cde345
*/

/* Expected Output:
<!DOCTYPE html>
<html>
	<body>
		<table>
			<tr><th>column1</th><th>column2</th><th>column3</th></tr>
			<tr><td>a</td><td>123</td><td>abc123</td></tr>
			<tr><td>b</td><td>234</td><td>bcd234</td></tr>
			<tr><td>c</td><td>345</td><td>cde345</td></tr>
		</table>
	</body>
</html>
*/

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
	string ifname = "C://Users//geeky//Desktop//test_small.csv";
	string ofname = "C://Users//geeky//Desktop//output.html";
	string_view preTag = "<!DOCTYPE html>\n<html>\n\t<body>\n\t\t<table>\n\t\t\th";
	string_view postTag = "\t\t</table>\n\t</body>\n</html>\n";
	string_view preRow = "<tr>";
	string_view postRow = "</tr>";
	string_view preHeading = "<th>";
	string_view postHeading = "</tr>";
	string_view preCell = "<td>";
	string_view postCell = "</rd>";
	vector <string> headings;
	vector <string> rows;
	unique_ptr<char[]> buffer;
	string_view svBuffer;

	void getHeadings();
	void getRows();
	void getCSVLine();
public:
	void readFile();
	void writeFile();
	void processFile();
};

void getHeadings() {

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

	return;
}

void CSV_HTML::writeFile() {
	outFile.open(ofname);
	outFile.rdbuf()->pubsetbuf(write_buffer, SIZE);
	outFile << preTag << '\n' << postTag;
	outFile.close();
}

int main() {
	CSV_HTML converter;
	converter.readFile();
	converter.writeFile();
	return 0;
}