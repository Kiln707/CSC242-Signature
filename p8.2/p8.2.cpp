/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 	Week 5, p8.2
** File: 	p8.2.cpp
** Description: this program reads from a file and will write to console all
** words not found in /usr/share/dict/words
**
** Author: 	Steven Swanson
** Date: 	13 Aug 2024
** -------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/***************************
 * get_dictionary
 ***************************/
vector<string> get_dictionary(ifstream& in_dict)
{
        vector<string> words;
        const string dict_path = "/usr/share/dict/words";

        // Open, confirm opened, dictionary.
        in_dict.open(dict_path);
        if (in_dict.fail())
        {
                cout << "Failed to open Dictionary at " << dict_path << " something is wrong." << endl;
                return vector<string>();
        }
        // Dictionary is open, load dictionary vector:
        string line;
        while (getline(in_dict, line))
        {
                words.push_back(line);
        }
        in_dict.close(); // close file now that it has been read, to prevent issues.
        // Dictionary table is now filled.
        return words;
}

int main(int argc, char* argv[])
{
        // Check if correct number of arguments has been passed.
        // Exit with code 1 if incorrect number of arguments.
        if (argc < 2 or argc > 2)
        {
                cout << "Invalid number of arguments. Program accepts a single path to file." << endl;
                return 1;
        }

        // Set variables and constants for program.
        string input_file = argv[1];
        ifstream in_dict;
        vector<string> words = get_dictionary(in_dict);
        if (words.empty())
        {
                return 1;
        }
        ifstream in_file;

        // Open and confirm open the input file.
        in_file.open(input_file);
        if (in_file.fail())
        {
                cout << "Failed to open file at " << input_file << ". Please confirm file exists." << endl;
                return 1;
        }
        string word;
        // While we receive a word in the file
        while (in_file >> word)
        {
                // Check to see if we can find a match in the words dictionary.
                bool match = false;
                for (int i = 0; i < words.size(); i++)
                {
                        // If a match is found, change flag to show it was found
                        // and break from the for loop to continue processing.
                        if (word == words[i])
                        {
                                match = true;
                                break;
                        }
                }
                // if we did not find a match, write the word to console.
                if (! match)
                {
                        cout << word << endl;
                }
        }
        in_file.close(); //ensure that we close the file when we are done.
        return 0;
}
