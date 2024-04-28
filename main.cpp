#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

//class for the grocery list
class GroceryManager {
private:
    map<string, int> frequencies;
    string fileName;

public:
    GroceryManager(const string& fileName) : fileName(fileName) {
        loadFrequencies();
        backupData();
    }

    void loadFrequencies() {
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << fileName << endl;
            exit(EXIT_FAILURE);
        }
        string item;
        int count;
        while (file >> item >> count) {
            frequencies[item] = count;
        }
        file.close();
    }

//function for first menu option
    void searchItem(const string& item) {
        if (frequencies.find(item) != frequencies.end()) {
            cout << "The frequency of " << item << " is: " << frequencies[item] << endl;
        } else {
            cout << item << " not found in the input file." << endl;
        }
    }

//function for second menu option
    void printFrequency() {
        for (const auto& pair : frequencies) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

//function for third menu option
    void printHistogram() {
        for (const auto& pair : frequencies) {
            cout << pair.first << ": ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

//output file creation
    void backupData() {
        ofstream outFile("frequency.dat");
        if (!outFile.is_open()) {
            cerr << "Error: Unable to create backup file." << endl;
            return;
        }
        for (const auto& pair : frequencies) {
            outFile << pair.first << " " << pair.second << endl;
        }
        outFile.close();
    }
};

//menu funcitonality
int main() {
    const string fileName = "CS210_Project_Three_Input_File.txt";
    GroceryManager manager(fileName);
    
    int choice;
    while (true) {
        cout << "\nMenu Options:" << endl;
        cout << "1. Search for an item" << endl;
        cout << "2. Print list with item frequencies" << endl;
        cout << "3. Print histogram of item frequencies" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string item;
                cout << "Enter the item you wish to search for: ";
                cin >> item;
                manager.searchItem(item);
                break;
            }
            case 2: {
                manager.printFrequency();
                break;
            }
            case 3: {
                manager.printHistogram();
                break;
            }
            case 4: {
                cout << "Exiting the program." << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
            }
        }
    }
    return 0;
}
