#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void copyCharacterByCharacter(const string &inputFile, const string &outputFile)
{
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open() || !outFile.is_open())
    {
        cerr << "Error opening files." << endl;
        return;
    }

    char ch;
    while (inFile.get(ch))
    {                    // Read each character
        outFile.put(ch); // Write each character to the output file
    }

    inFile.close();
    outFile.close();
}

void copyLineByLine(const string &inputFile, const string &outputFile)
{
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open() || !outFile.is_open())
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    while (getline(inFile, line))
    {                            // Read each line
        outFile << line << endl; // Write each line to the output file
    }

    inFile.close();
    outFile.close();
}

int main()
{
    string inputFile = "input.txt";
    string outputFileCharacter = "output_character_by_character.txt";
    string outputFileLine = "output_line_by_line.txt";

    // Copy file character by character
    copyCharacterByCharacter(inputFile, outputFileCharacter);
    cout << "File copied character by character to " << outputFileCharacter << endl;

    // Copy file line by line
    copyLineByLine(inputFile, outputFileLine);
    cout << "File copied line by line to " << outputFileLine << endl;

    return 0;
}