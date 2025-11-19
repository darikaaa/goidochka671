#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Date {
    int _day;
    int _month;
    int _year;

    void Init(int year, int month, int day) {
        if (day <= 0 || day > 31) {
            throw string("day");
        }
        if (month <= 0 || month > 12) {
            throw string("month");
        }
        if (year <= 0 ) {
            throw string("year");
        }

        _day = day;
        _month = month;
        _year = year;
    }
};

Date parsing(string line) {
    if (line.empty()) {
        throw string("Empty date string");
    }

    char delim = '.';
    int delim_pos_1 = line.find(delim);
    if (delim_pos_1 == string::npos) {
        throw string("Invalid date format: first delimiter not found");
    }
    int delim_pos_2 = line.find(delim, delim_pos_1 + 1);
    if (delim_pos_2 == string::npos) {
        throw string("Invalid date format: second delimiter not found");
    }

    Date date;
    int day = stoi(line.substr(0, delim_pos_1));
    int month = stoi(line.substr(delim_pos_1 + 1, delim_pos_2 - delim_pos_1 - 1));
    int year = stoi(line.substr(delim_pos_2 + 1));
    date.Init(year, month, day);

    return date;
}

int main() {
    string source_path = "C:\\programming\\text2.txt";
    ifstream file;
    file.open(source_path);
    if (!file.is_open()) {
        cout << "File does not exist" << endl;
        return -1;
    }

    vector<Date> dates;
    string line;

    try {
        while (getline(file, line)) {
            Date date = parsing(line);
            dates.push_back(date);
        }
        file.close();
    }
    catch (string error) {
        file.close();

        if (error == "Empty date string") {
            cout << "empty date string" << endl;
            return -1;
        }
        else if (error.find("Invalid date format") != string::npos) {
            cout << error << endl;
            return -2;
        }
        else if (error == "day") {
            cout << "invalid day" << endl;
            return -3;
        }
        else if (error == "month") {
            cout << "invalid month" << endl;
            return -4;
        }
        else if (error == "year") {
            cout << "invalid year" << endl;
            return -5;
        }
    }


    for (auto str : dates) {
        cout << str._day << "." << str._month << "." << str._year << endl;
    }

    return 0;
}


