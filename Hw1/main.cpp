//
//  main.cpp
//  Hw1
//
//  Created by Eder Aguilar on 9/6/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cctype>




using namespace std;

// Prototype Function to calculate letter frequency ;SPJII
map<char, double> calculateLetterFrequency(const string& text) {
    map<char, int> letterCount;
    int totalCharacters = 0;

    for (char c : text) {
        if (isalpha(c)) {
            char lowercaseChar = tolower(c);
            letterCount[lowercaseChar]++;
            totalCharacters++;
        }
    }

    map<char, double> letterFrequency;
    for (const auto& pair : letterCount) {
        letterFrequency[pair.first] = (static_cast<double>(pair.second) / totalCharacters) * 100.0;
    }

    return letterFrequency;
}

// Function to process a book file and update the CardCatalog.txt ;SPJII
void processBook(string& name) {
    ifstream iFile(name);

    string title, authorFull, line;
    string content;
    while (getline(iFile, line)) {
        if (line.empty()) {
            break;
        }
        if (title.empty()) {
            title = line;
        }
        else {
            authorFull = line;
        }
    }

    if (title.empty() || authorFull.empty()) {
        cout << "Error: Invalid file format. The file should contain a title and author information." << endl;
        return;
    }

    // Read the rest of the content
    while (getline(iFile, line)) {
        content += line + "\n";
    }

    // Calculate word count
    int wordCount = 0;
    bool inWord = false;
    for (char c : content) {
        if (isalpha(c)) {
            if (!inWord) {
                inWord = true;
                wordCount++;
            }
        }
        else {
            inWord = false;
        }
    }

    // Calculate line count
    int lineCount = 0;
    for (char c : content) {
        if (c == '\n') {
            lineCount++;
        }
    }

    // Calculate letter frequency
    map<char, double> letterFrequency = calculateLetterFrequency(content);

    // Write to CardCatalog.txt
    ofstream catalog("CardCatalog.txt", ios::app);
    if (catalog.is_open()) {
        catalog << "Title: " << title << endl;
        catalog << "Full Author: " << authorFull << endl;
        catalog << "Author First Name: " << authorFull.substr(0, authorFull.find(' ')) << endl;
        catalog << "Author Last Name: " << authorFull.substr(authorFull.find(' ') + 1) << endl;
        catalog << "Word count: " << wordCount << endl;
        catalog << "Line count: " << lineCount << endl;
        catalog << endl;
        catalog.close();

        cout << "Book information for '" << title << "' saved to CardCatalog.txt." << endl;

        // Ask if the user wants to see letter frequency
        string seeLetterFrequency;
        cout << "Do you want to see the letter frequency? (yes/no): ";
        cin >> seeLetterFrequency;
        if (seeLetterFrequency == "yes") {
            cout << title << " letter frequency:" << endl;
            for (const auto& pair : letterFrequency) {
                cout << pair.first << ": " << fixed << pair.second << "%" << endl;
            }
        }
    }
    else {
        cout << "Error: Unable to open CardCatalog.txt for writing." << endl;
    }
    return;
}

int main() {
    // insert code here...
    fstream iFile; //for reading input from a file
    fstream oFile; //for writing output to a file
    string name; //contains name of file
    string line; //hold line for parsing
	string decision;

    //outer while loop will be responsible for prompting user if they want to parse another file.
    while (true){
        //while the file isn't opened up correctly, continue prompting the user until a valid file name is provided
        do {
			cout << "Enter the files name please: ";
            getline(cin, name);
            iFile.open(name, ios::in);

		} while (iFile.fail());

        //This is parsing logic. SPJII
        processBook(name);

        //prompt the user if they want to parse another file
        cout << "Finished parsing file.\nWould you like to parse another file (yes/no)?" << endl;
		cin >> decision;
        if (decision == "yes") {
            //need to close the current file in order to reuse ifile variable
            iFile.close();
            continue;
        }
        else {
          break;
		  return false;
        }
    }

    cout << "Successfully processed the file. Now closing  " << name << " and terminating program." << endl;
    iFile.close();

    return 0;
}



