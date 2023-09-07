//
//  main.cpp
//  Hw1
//
//  Created by Eder Aguilar on 9/6/23.
//

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int main() {
    // insert code here...
    fstream iFile; //for reading input from a file
    fstream oFile; //for writing output to a file
    string name; //contains name of file
    string line; //hold line for parsing
    bool choice = true;
    string decision;
    
    //outer while loop will be responsible for prompting user if they want to parse another file.
    while(choice) {
        //while the file isn't opened up correctly, continue prompting the user until a valid file name is provided
        do {
            std::cout << "Please enter name of file" << endl;
            getline(cin, name);
            iFile.open(name, ios::in);
            
        } while(iFile.fail());
        
        //If the file is open correctly,cout the contents
        //Delete this code and replace with parsing logic. I believe this is stephen's task
        if(iFile) {
            while(getline(iFile, line)) {
                cout << line << endl;;
            }
        }
        //prompt the user if they want to parse another file
        cout << "Finished parsing file.\nParse another file?" << endl;
        getline(cin, decision);
        if(decision == "yes" || decision == "y" || decision =="Y") {
            //need to close the current file in order to reuse iFile variable
            iFile.close();
            continue;
        } else {
            break;
        }
    }
    
    cout << "Successfully processed the file. Now closing  " << name << "and terminating program."<< endl;
    iFile.close();
    
    return 0;
}
