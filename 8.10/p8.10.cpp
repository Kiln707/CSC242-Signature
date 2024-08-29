#include <iostream>
#include <string>

using namespace std;

void write_usage(const string program_file)
{
    cout << "Usage: " << program_file << " [-d] -k<keyword> <Input>" << endl;
    cout << "options:" << endl;
    cout << "\t-d: decrypt file" << endl;
    cout << "\t-k<keyword>: keyword for encryption/decryption" << endl;
    cout << "example: " << endl;
    cout << "To encrypt: ./" << program_file << "-kmycode My code here" << endl;
    cout << "To decrypt: ./" << program_file << "-d -kmycode My encrypted code here" << endl;
}

int get_row(const char cipher[5][5], char character)
{
    if (character == 'j')
    {
        character = 'i';
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (cipher[i][j] == character)
            {
                return i;
            }
        }
    }
    return -1;
}
int get_col(const char cipher[5][5], char character)
{
    if (character == 'j')
    {
        character = 'i';
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (cipher[i][j] == character)
            {
                return j;
            }
        }
    }
    return -1;
}

char get_swap_character(const char cipher[5][5], int target_row, int target_col, int alternate_row, int alternate_col)
{
    if (alternate_row == target_row || alternate_col == target_col)
    {
        return cipher[alternate_row][alternate_col];
    }
    return cipher[target_row][alternate_col];
}

int main(int argc, char* argv[])
{
    const string alphabet = "abcdefghiklmnopqrstuvwxyz";
    char cipher[5][5];
    bool cipher_built = false;
    bool decrypt = false;
    string data = "";

    for (int i = 1; i < argc; i++)
    {
        string arg = argv[i];
        if (arg == "-d")
        {
            decrypt = true;
        }
        else if (arg.starts_with("-k"))
        {
            // Getting key to build cipher
            string seed = arg.substr(2, arg.length());
            // Generate code for encryption/decryption.
            string code = seed + alphabet;

            // Append seed to reversed alphabet
            // remove duplicate letters in entire string.
            for (int a = 0; a < code.size(); a++)
            {
                for (int b = a+1; b < code.size(); b++)
                {
                    if (code[a] == code[b]) { code.erase(b, 1); }
                }
            }
            // generate the 5x5 array cipher
            for (int a = 0; a < 5; a++)
            {
                for (int b = 0; b < 5; b++)
                {
                    cipher[a][b] = code[a*5 + b];
                }
            }
            // Indicate that cipher is prepared
            cipher_built = true;
        }
        else
        {
            // This is an input.
            data += arg;
        }
    }
    if (! cipher_built || data.empty())
    {
        // Missing Data
        write_usage(argv[0]);
        return 1;
    }

    int i = 0;
    string output = "";
    // If data is uneven append Z to ensure input is encrypted.
    if (data.size() % 2 != 0)
    {
        data += "z";
    }
    // We know that data is even in size, so we can grab two at a time.
    while (i < data.size())
    {
        char first = data[i];
        bool first_is_upper = isupper(first);
        const int first_row = get_row(cipher, tolower(first));
        if (first_row == -1){ return -1; }
        const int first_col = get_col(cipher, tolower(first));
        if (first_col == -1){ return -1; }
        i++;
        char second = data[i];
        bool second_is_upper = isupper(second);
        const int second_row = get_row(cipher, tolower(second));
        if (second_row == -1){ return -1; }
        const int second_col = get_col(cipher, tolower(second));
        if (second_col == -1){ return -1; }
        i++;

        first = get_swap_character(cipher, first_row, first_col, second_row, second_col);
        second = get_swap_character(cipher, second_row, second_col, first_row, first_col);

        if (first_is_upper){ first = toupper(first); }
        if (second_is_upper){ second = toupper(second); }
        output += first + second;
    }
    cout << output << endl;
}
