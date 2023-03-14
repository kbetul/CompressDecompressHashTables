#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "hashTable.h"

using namespace std;

int main()
{
    HashTable<int,string> keys(-1, 4096); //initial array

    for  (int i =0; i <= 255; i++){ //add the first 255 character from ASCII table
        string character = "";
        character += char(i);
        keys.insert(i,character);
    }

    char ch;
    string add = "", p = "", c = "", output = "";
    ifstream read("compin.txt");
    ofstream write("compout.txt");

    vector<string> file; 
    while (!read.eof())
    { //reading the input file into a vector
        read.get(ch);
        add += ch;
        file.push_back(add);
        add = "";
    }
    file.pop_back();

    p += file[0];
    int code = 256;
    for (int i = 0; i < file.size(); i++){
        if (i != file.size()-1) // if index is not the last one
            c += file[i+1]; // add the next index to c
        if (keys.find(p+c) > -1){ //if p + c is in the array
            p = p + c; //update p as p + c
        } else { //if p + c is not in the array
            output += to_string(keys.find(p)) + " "; //add it to output
            keys.insert(code, p+c); //insert p + c to array
            code++;
            p = c;
        }
        c = "";
    }
    output += to_string(keys.find(p)) + " "; //add the last element into output too
    write << output; //write output to output file
    write.close();
    read.close();

    return 0;
}