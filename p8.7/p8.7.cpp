/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 	Lesson 5
** File: 	p8.7.cpp
** Description: Encrypts or decypts file using monoalphabet cipher with given key
**
** Author: 	Steven Swanson
** Date: 	25 AUg 2024
** -------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


string reverse(string input)
{
    // Takes string input, reverses it, and returns result.
    string output = "";
    for (int i = input.size() - 1; i >= 0; i--)
    {
        output += input[i];
    }
    return output;
}

string getCipher(const string &seed, const string &alphabet)
{
    // Generate code for encryption/decryption.
    string code = seed + reverse(alphabet);

    // Append seed to reversed alphabet
    // remove duplicate letters in entire string.
    for (int i = 0; i < code.size(); i++)
    {
        for (int j = i+1; j < code.size(); j++)
        {
            if (code[i] == code[j]) { code.erase(j, 1); }
        }
    }
    return code;
}


void process_file(ifstream &in_file, ofstream &out_file, const string &input_key, const string &output_key)
{
    char ch;
    while (in_file.get(ch))
    {
        if (! isalpha(ch))
        {
            out_file.put(ch);
        }
        for (int i = 0; i < input_key.size(); i++)
        {
            if (tolower(ch) == input_key[i])
            {
                //cout << "writing " << output_key[i] << " from " << input_key[i] << endl;
                if (isupper(ch))
                {
                    out_file.put(toupper(output_key[i]));
                }
                else
                {
                    out_file.put(output_key[i]);
                }
                break;
            }
        }
    }
}

void write_usage(const string program_file)
{
    cout << "Usage: " << program_file << " [-d] -k<code> <input_file> <output_file>" << endl;
    cout << "options:" << endl;
    cout << "\t-d: decrypt file" << endl;
    cout << "\t-k<code>: seeding code for encryption/decryption" << endl;
    cout << "example: " << endl;
    cout << "To encrypt: ./" << program_file << "-kmycode ./input.txt ./output.txt" << endl;
    cout << "To decrypt: ./" << program_file << "-d -kmycode ./input.txt ./output.txt" << endl;
}


int main(int argc, char* argv[])
{
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string code;
    bool decrypt = false;
    ifstream in_file;
    ofstream out_file;

    for (int i = 1; i < argc; i++)
    {
        string arg = argv[i];
        if (arg == "-d")
        {
            decrypt = true;
        }
        else if (arg.starts_with("-k"))
        {
            code = getCipher(arg.substr(2, arg.length()), alphabet);
        }
        else if (! in_file.is_open())
        {
            cout << "opening " << arg << " for reading" << endl;
            in_file.open(arg);
            if (in_file.fail())
            {
                cout << "error opening file " << arg << endl;
                return 1;
            }
        }
        else if ( in_file.is_open() && !out_file.is_open() )
        {
            cout << "opening " << arg << " for writing" << endl;
            out_file.open(arg);
            if (out_file.fail())
            {
                cout << "error opening file " << arg << endl;
                return 1;
            }
        }
    }
    if (code.empty() || ! in_file.is_open() || ! out_file.is_open())
    {
        write_usage(argv[0]);
        return 1;
    }

    if (decrypt)
    {
        // We want the alphabet to be writing into the outfile.
        // This will decrypt the file.
        process_file(in_file, out_file, code, alphabet);
    }
    else
    {
        // We want the key to be writing into the outfile.
        // This will encrypt the file.
        process_file(in_file, out_file, alphabet, code);
    }
    return 0;
}
