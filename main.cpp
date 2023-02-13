#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <ctime>

using namespace std;

map<string, pair<int, int> > magic_dict;

int main() {
    ifstream reviews_file("reviews.csv");

    // Skip heading
    string heading;
    getline(reviews_file, heading);

    while(reviews_file.good()) {
        string row;
        getline(reviews_file, row);
        int semicolon_pos = row.find(";");
        string date_string = row.substr(0, semicolon_pos);
        tm date = {};
        strptime(date_string.c_str(), "%Y-%m-%d %H:%M:%S", &date);
        char formated_date[20];
        strftime(formated_date, sizeof(formated_date), "%Y-%m", &date);

        string rating_string = row.substr(semicolon_pos + 1);
        int rating = stoi(rating_string);

        if (magic_dict.count(formated_date) == 0) {
            magic_dict[formated_date] = make_pair(rating, 1);
        } else {
            magic_dict[formated_date].first += rating;
            magic_dict[formated_date].second++;
        }
    }

    ofstream output_file("output.csv", ios::app);
    output_file << "year-mounth,media" << endl;
    for (const auto &kv : magic_dict) {
        output_file << kv.first << ", " << (double)kv.second.first / kv.second.second << endl;
    }

    return 0;
}