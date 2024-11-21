#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int MEMORY_SIZE = 1024; // Size of the main memory

void loadALPToMemory(const string &inputFile, vector<int> &memory)
{
    ifstream inFile(inputFile);
    if (!inFile.is_open())
    {
        cerr << "Error opening file: " << inputFile << endl;
        return;
    }

    int address = 0; // Starting memory address
    string line;
    while (getline(inFile, line))
    {
        if (address >= MEMORY_SIZE)
        {
            cerr << "Memory overflow: Program is too large to fit in memory." << endl;
            break;
        }

        // Convert hex string to an integer
        int instruction = stoi(line, nullptr, 16);

        // Load instruction into memory
        memory[address] = instruction;
        cout << "Loaded instruction " << hex << instruction << " at address " << address << endl;

        address++;
    }

    inFile.close();
}

int main()
{
    vector<int> memory(MEMORY_SIZE, 0); // Initialize memory with zeros

    string inputFile = "ALP_program.txt"; // Input file with ALP instructions
    loadALPToMemory(inputFile, memory);

    cout << "Program loaded into memory successfully." << endl;

    return 0;
}