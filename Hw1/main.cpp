//
//  main.cpp
//  Hw1
////
//  Created by Eder Aguilar on 9/6/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cctype>




using namespace std;
//Structure containing contents of file opened. 
struct bookInfo {
    string title; //book title
    string author; //book author, later parsed into first and last name in output. 
    int wordCount=0; 
    map<char, double> letterFreq; //letter frequency 
    int lineCount=0;
    //called in constructor to initialize letterFreq
    map<char, double> calculateLetterFrequency(const string& text);
    //Constructor initializing all relevant information. 
    bookInfo(fstream& iFile) {
        //string title, authorFull, line;
        string line;
        string content;
        //from the files, we can just get the first two lines since both files start off similarly.
        getline(iFile, title);
        getline(iFile, author);

        //get passed the contents empty lines...peter pan text file has extra lines
        while (getline(iFile, line)) {
            if (line.empty()) continue;

            else break;
        }

        //this next piece will get the contents
        if (title.empty() || author.empty()) {
            cout << "Error: Invalid file format. The file should contain a title and author information." << endl;
            return;
        }

        // Read the rest of the content
        while (getline(iFile, line)) {
            //account for the line break between "contents" and "all children" in peter pan text
            if (line.empty()) continue;

            content += line + "\n";
        }

        // Calculate word count
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
        for (char c : content) {
            if (c == '\n') {
                lineCount++;
            }
        }

        // Calculate letter frequency
        letterFreq = calculateLetterFrequency(content);
        return;
    }
};

// Prototype Function to calculate letter frequency ;SPJII
map<char, double> bookInfo::calculateLetterFrequency(const string& text) {
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
void writeOutput(bookInfo book) {
          ofstream catalog("CardCatalog.txt", ios::app);
        if (catalog.is_open()) {
            catalog << "Title: " << book.title << endl;
            catalog << "Full Author: " << book.author << endl;
            string authorTemp = book.author;
            catalog << "Author First Name: " << book.author.substr(0, book.author.find(' ')) << endl;
            catalog << "Author Last Name: " << book.author.substr(book.author.find(' ') + 1) << endl;
            catalog << "Word count: " << book.wordCount << endl;
            catalog << "Line count: " << book.lineCount << endl;
            catalog << endl;
            catalog.close();
            cout << "Book information for '" << book.title << "' saved to CardCatalog.txt." << endl;

            // Ask if the user wants to see letter frequency
            string seeLetterFrequency;
            cout << "Do you want to see the letter frequency? (yes/no): ";
            cin >> seeLetterFrequency;
            if (seeLetterFrequency == "yes") {
                cout << book.title << " letter frequency:" << endl;
                for (const auto& pair : book.letterFreq) {
                    cout << pair.first << ": " << fixed << pair.second << "%" << endl;
                }
            }
        }
        else {
            cout << "Error: Unable to open CardCatalog.txt for writing." << endl;
      }
}
int main() {
    // insert code here...
    fstream iFile; //for reading input from a file
    string name; //contains name of file
    string line; //hold line for parsing
    string decision;

    //outer while loop will be responsible for prompting user if they want to parse another file.
    while (true) {
        //while the file isn't opened up correctly, continue prompting the user until a valid file name is provided
        do {
            cout << "Enter the files name please: ";
            getline(cin, name);
            iFile.open(name, ios::in);
        } while (iFile.fail());

        //This is parsing logic. SPJII
        //Since the file is opened on line 139, we should be using that same filestream...pass into process book method by reference
      //constructor for book, all relevant information will be stored on here. CS
        bookInfo book(iFile);
        writeOutput(book);

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
        }
    }

    cout << "Successfully processed the file. Now closing  " << name << " and terminating program." << endl;
    iFile.close();

    return 0;
}



