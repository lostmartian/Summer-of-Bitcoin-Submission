#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <assert.h>
#include <map>
using namespace std;

#define max_weight 4000000

// Functions
void readCSV();  // Read the CSV data
void writeCSV(); // Write the CSV data
void printData(int k); // Print the CSV data loaded onto arr
int noviceTesting();

// Tree struct for Connected Components to keep track of parent transactions
struct Tree {
    string tx_id;
    int fee, weight;
    vector<string> pid;
};

// Variable Declarations
map<string, vector<string>> check_for_parent;
vector<pair<pair<string, int>, pair<int, vector<string>>>> arr;
int main()
{
    readCSV();
    // cout<<arr.size()<<"\n";
    // printData(arr.size());
    cout<<noviceTesting()<<"\n";





    return 0;
}

void printData(int k) {
    for (int i = 0; i < min(k, 5214); i++) {
        cout << arr[i].first.first << " " << arr[i].first.second << " " << arr[i].second.first << " ";
        for (string s : arr[i].second.second) {
            cout << s << " ";
        }
        cout << "\n";
    }
    cout << "Total Size:" << arr.size() << "\n";
}

int noviceTesting() {
    int total_fee = 0, total_weight=0, tfee=0, tweight=0;
    vector<pair<pair<string, int>, pair<int, vector<string>>>> transact;
    for (int i = 0; i < arr.size(); i++) {
        tfee+=arr[i].first.second;
        tweight+=arr[i].second.first;
        string parent_id = arr[i].second.second[0];
        if (parent_id == "") {
            transact.push_back(arr[i]);
        }
    }
    cout<<transact.size()<<"\n";
    sort(transact.begin(), transact.end(), [](const pair<pair<string, int>, pair<int, vector<string>>> &a, const pair<pair<string, int>, pair<int, vector<string>>> &b) {
        double fee_a = a.first.second, fee_b = b.first.second;
        double weight_a = a.second.first, weight_b = b.second.first;
        double epsilon = 0.01;
        double A = fee_a/weight_a;
        double B = fee_b/weight_b;
        return (A - B) > ( (fabs(A) < fabs(B) ? fabs(B) : fabs(A)) * epsilon);
    });
    for(int i=0; i<transact.size(); i++) {
        if((total_weight+transact[i].second.first)>max_weight) {
            break;
        }
        cout<<transact[i].first.first<<"\n";
        total_fee += transact[i].first.second;
        total_weight += transact[i].second.first;
    }
    cout<<total_weight<<"\n";
    return total_fee;
}

void readCSV()
{
    ifstream inputFile("../data/mempool.csv");
    bool flag = 0;
    string word, tmp, line;
    vector<string> elements;
    // CSV variables
    int fee, weight;
    string txid;
    vector<string> parents;
    while (inputFile)
    {
        elements.clear();
        parents.clear();
        getline(inputFile, line);
        istringstream s(line);
        while (s) {
            if (!getline(s, word, ',')) {
                break;
            }
            else {
                if (word == "tx_id") {
                    flag = 1;
                    continue;
                }
                elements.push_back(word);
            }
        }
        if (flag) {
            flag = 0;
            continue;
        }
        if (elements.size() < 3) {
            continue;
        }
        int semi_count = 0;
        txid = elements[0], fee = stoi(elements[1], nullptr, 10), weight = stoi(elements[2], nullptr, 10);
        if (elements.size() > 3) {
            for (int i = 0; i < elements[3].size(); i++) {
                if (elements[3][i] == ';') {
                    semi_count++;
                    word = "";
                    for (int j = i - 64; j < i; j++) {
                        word.push_back(elements[3][j]);
                    }
                    parents.push_back(word);
                }
            }
        }
        word = "";
        if (elements.size() > 3) {
            for (int i = elements[3].size() - 1; i >= elements[3].size() - 64 - (semi_count - 1); i--) {
                word.push_back(elements[3][i]);
            }
        }
        reverse(word.begin(), word.end());
        parents.push_back(word);
        arr.push_back({{txid, fee}, {weight, parents}});
    }
}
