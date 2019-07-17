//
//  main.cpp
//  ISBN Converter

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

ifstream in;

//check digit for isbn10to13
string check10 (int input[], int size) {
    int mod = 10, sum = 0;
    int check;
    string finalcheck;
    
    for (int i = 0; i < size; i++) {
        if (i%2 == 0) {
            sum += input[i];
        }
        else {
            sum += input[i] * 3;
        }
    }
    check = mod - (sum % mod);
    if (sum%mod == 0) {
        finalcheck = '0';
    }
    else {
        finalcheck = to_string(check);
    }
    return finalcheck;
}

//check digit for isbn13to10
string check13 (int input[], int size) {
    int mod = 11, sum = 0;
    int check;
    string finalcheck;
    
    for (int i = 0; i < size; i++) {
        input[i] = input[i] * (10 - i);
        sum += input[i];
    }
    check = mod - (sum % mod);
    if (sum % mod==0) {
        finalcheck = '0';
    }
    else if (check == 10) {
        finalcheck = "X";
    }
    else {
        finalcheck = to_string(check);
    }
    return finalcheck;
}

//string -> int array
long str_int(string str, int output[]) {
    long size = str.length();
    for (int i = 0; i < size; i++) {
        output[i] = (int) str[i] - '0';
    }
    return size;
}

string isbn10to13 (string isbn10) {
    string isbn13, check, newstr;
    int out[12] = {};
    
    newstr = "978" + isbn10.substr(0,9);
    str_int(newstr, out);
    check = check10(out, 12);
    isbn13 = newstr.append(check);
    return isbn13;
}

string isbn13to10 (string isbn13) {
    string isbn10, check, newstr;
    int out[10] = {};
    
    newstr = isbn13.substr(3,9);
    str_int(newstr, out);
    check = check13(out, 9);
    isbn10 = newstr.append(check);
    return isbn10;
}


//main
int main(int argc, const char * argv[]) {
    in.open("input.txt", ios::in);
    if (in.fail()) {
        cout << "Could not open file.";
        return 9;
    }
    
    string isbn;
    int end = 0;
    
    while (end == 0) {
        in >> isbn;
        if (isbn.size() == 10) {
            cout << isbn10to13(isbn) << endl;
        }
        else if (isbn.size() == 13) {
            cout << isbn13to10(isbn) << endl;
        }
        else if (isbn == "-1") {
            end = -1;
        }
        else {
            cout << "Invalid input" << endl;
        }
    }
    return 0;
}
