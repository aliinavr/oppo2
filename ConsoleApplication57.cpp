#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
using namespace std;

struct measurements {
	string date;
	double height;
	int value;
};

measurements parseMeasurement(const string& line) {
	regex pattern(R"((\d{4}-\d{2}-\d{2})\s+(\d+(?:\.\d+)?)\s+(\d+))");
	smatch match;
	measurements measurement;

	if (regex_match(line, match, pattern)) {
		measurement.date = match[1];
		measurement.height = stod(match[2]);
		measurement.value = stoi(match[3]);
	}

	return measurement;
}

void displayMeasurement(const measurements& measurement) {
	cout << "Дата: " << measurement.date << ", Высота: " << measurement.height << ", Значение: " << measurement.value << endl;
}

bool compareByDate(const measurements& a, const measurements& b) {
	return a.date < b.date;
}

int main() {
	setlocale(LC_ALL, "ru");
	ifstream inputFile("measurements.txt");

	if (!inputFile) {
		cerr << "Ошибка открытия файла!" << endl;
		return 1;
	}

	vector<measurements> x;
	string line;

	while (getline(inputFile, line)) {
		line.erase(0, line.find_first_not_of(" "));
		line.erase(line.find_last_not_of(" ") + 1);
		if (line.empty()) continue;
		measurements measurement = parseMeasurement(line);
		if (!measurement.date.empty()) {
			x.push_back(measurement);
		}
	}

	inputFile.close();

	// Сортировка по дате
	sort(x.begin(), x.end(), compareByDate);

	// Вывод всех измерений
	cout << "Все измерения:" << endl;
	for (const auto& item : x) {
		displayMeasurement(item);
	}

	// Поиск по заданной высоте
	double targetHeight;
	cout << "\nВведите высоту для поиска: ";
	cin >> targetHeight;

	cout << "\nИзмерения с высотой " << targetHeight << ":" << endl;
	for (const auto& item : x) {
		if (item.height == targetHeight) {
			displayMeasurement(item);
		}
	}

	return 0;
}