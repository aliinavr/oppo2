#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <iomanip>

using namespace std;

struct measurements {
    string date;
    double height;
    int value;
};


measurements parseMeasurement(const string& line) {
    regex pattern(R"((\d{4}-\d{2}-\d{2})\s+(\d+(?:\.\d+)?)\s+(\d+))");
    smatch match;
    measurements measurement = { "", 0.0, 0 };

    if (!regex_match(line, match, pattern)) {
        cerr << "Ошибка парсинга строки: " << line << endl;
        return measurement; // Возвращаем значение по умолчанию в случае ошибки
    }

    measurement.date = match[1];
    measurement.height = stod(match[2]);
    measurement.value = stoi(match[3]);
    return measurement;
}


void displayMeasurement(const measurements& measurement) {
    cout << "Дата: " << measurement.date << ", Высота: " << fixed << setprecision(2) << measurement.height << ", Значение: " << measurement.value << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    ifstream inputFile("measurements.txt");

    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return 1;
    }

    vector<measurements> measurementsVector;
    string line;

    while (getline(inputFile, line)) {
        measurements measurement = parseMeasurement(line);
        if (!measurement.date.empty()) {
            measurementsVector.push_back(measurement);
        }
    }

    inputFile.close();

    // Сортировка по дате 
    sort(measurementsVector.begin(), measurementsVector.end(), [](const measurements& a, const measurements& b) {
        return a.date < b.date;
        });

    // Вывод всех измерений
    cout << "Все измерения:" << endl;
    for (const auto& item : measurementsVector) {
        displayMeasurement(item);
    }

    // Поиск по заданной высоте
    double targetHeight;
    cout << "\nВведите высоту для поиска: ";
    cin >> targetHeight;

    cout << "\nИзмерения с высотой " << targetHeight << ":" << endl;

    bool found = false; // Флаг для проверки наличия хотя бы одного совпадения

    for (const auto& item : measurementsVector) {
        if (abs(item.height - targetHeight) < 1e-6) {
            displayMeasurement(item);
            found = true;
        }
    }

    if (!found) {
        cout << "Измерения с такой высотой не найдены." << endl;
    }

    return 0;
}