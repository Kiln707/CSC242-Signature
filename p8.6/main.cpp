#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>


using namespace std;

string pad_right(string input, int num_spaces)
{
    /* Format the input string so that it will be exactly length = num_spaces.
     * This pretty's the formatting so it is easier to read.
     */
    string output = input;
    for (int i = input.size(); i < num_spaces; i++)
    {
        output += " ";
    }
    return output;
}

void extract_country_name_pop(ifstream &in_file, vector<string> &country_names, vector<int> &country_pop)
{
    /* Extract from open file, the country names and populations in the file. */
    char ch;
    string country_name;
    bool whitespace = false;
    while (! in_file.eof())
    {
        in_file.get(ch);
        // cout << ch << isspace(ch) << isdigit(ch) << endl;;
        if (!isspace(ch) and !isdigit(ch))
        {
            // If this is alpha character, then save as part of country name
            if (whitespace and country_name.empty())
            {
                // If whitespace is flagged, but country-name is empty
                // then newline reached, false flag, remove.
                whitespace = false;
            }
            if (whitespace)
            {
                // If whitespace reached add space between words.
                country_name += " ";
                whitespace = false;
            }
            // While reading the file, save each non-digit to string
            // If we previously hit a whitespace (and not a digit) then add a space
            country_name += ch;
        }
        else if (isdigit(ch))
        {
            // We reached population, read the number.
            // Unget the character we are looking at
            // create temp variable and store integer there.
            // Store pop in vector
            // remove whitespace flag, so that we dont prepend space to next country.
            in_file.unget();
            int pop;
            in_file >> pop;
            cout << pop << endl;
            whitespace = false;
            // Now that the values of country name and country pop has been extracted
            // Add to vector and clear country name for next Iteration.
            country_names.push_back(country_name);
            country_name = "";
            country_pop.push_back(pop);
        }
        else
        {
            // If we hit a white space, do nothing but proceed until
            // non-whitespace character reached.
            whitespace = true;
        }
    }
}

int main()
{
    // Declare Const & Variables
    const string INPUT_FILE = "./worldpop.txt";
    ifstream in_file;

    in_file.open(INPUT_FILE);
    // if we cannot open the file, we cannot run the program
    if (in_file.fail())
    {
        cout << "Failed to open file " << INPUT_FILE << endl;
        return -1;
    }

    //Extract the country names and populations from file.
    vector<string> country_names;
    vector<int> country_pop;
    extract_country_name_pop(in_file, country_names, country_pop);

    // For each entry extracted,
    for (int i = 0; i < country_names.size(); i++)
    {
        string name = country_names[i];
        int pop = country_pop[i];
        
        if (name == "European Union")
        {
            // European Union is to be skipped.
            continue;
        }
        cout << pad_right(name, 35) << "Population: " << pop << endl;
    }
}
