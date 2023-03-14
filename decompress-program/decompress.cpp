#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "hashTable.h"

using namespace std;

int main()
{
    string notFound = ""; //empty string for initializing
    HashTable<int,string> keys(notFound, 4096); //initial array

    for (int i =0; i <= 255; i++){ //add the first 255 character from ASCII table
        string character = "";
        character += char(i);
        keys.insert(i,character);
    }

    int num; 
    ifstream read("compout.txt");
    ofstream write("decompout.txt");

    vector<int> file; //reading the input file into a vector
    while (!read.eof())
    { 
        read >> num;
        file.push_back(num);
    }
    file.pop_back(); //removing the last int because the while loop adds the last element 2 times
    
    int cur_code = 0, prev_code = 0; 
    string cur_text = "" , output = "";
    cur_code = file[0]; //take the first int of file as the current input
    output += keys.find(cur_code); //find cur_code and add it to output
    prev_code = cur_code;

    int code = 256; //start from code 256
    for (int i = 1; i < file.size(); i++){
        cur_code = file[i];
        if (keys.find(cur_code) == keys.getItemNotFound()) { //if the code is not in the array
            cur_text = keys.find(prev_code) + keys.find(prev_code)[0];
            output+=cur_text;
            keys.insert(code, cur_text); //add the prev key + first char of prev key to the array
            code++;
        } else { //the code is in the array
            cur_text = keys.find(cur_code); 
            output += cur_text; //find and add it to output
            keys.insert(code, keys.find(prev_code)+cur_text[0]); //and insert the prev key + first char of current key to array
            code++;
        }
        prev_code = cur_code;
    }
    write << output; //write output to output file
    write.close();
    read.close();

    return 0;
}