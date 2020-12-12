#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
vector<vector<string>> fullContents;

class textEditor {
public:
    textEditor() {
        initEditor();
        //showContext();
    }
private:
    void initEditor() {
        string context;
        ifstream myfile("test.txt");
        if (myfile.is_open())
        {
            fullContents.push_back(*new vector<string>);
            int tmpBytes = 0;
            int tmpLine = 0;
            while (!myfile.eof())
            {
                myfile >> context;
                int cByte = context.size();
                tmpBytes += cByte;
                if (tmpBytes <= 75)
                {
                    fullContents[tmpLine].push_back(context);
                }
                else {
                    fullContents.push_back(*new vector<string>);
                    tmpBytes = cByte;
                    tmpLine++;
                    fullContents[tmpLine].push_back(context);
                }
                if (tmpBytes != 75) {
                    fullContents[tmpLine][fullContents[tmpLine].size() - 1] = fullContents[tmpLine][fullContents[tmpLine].size() - 1] + " ";
                }
            }
            for (int i = 0; i < fullContents.size(); i++) {
                cout << i << "| ";
                for (int j = 0; i < fullContents[i].size(); j++)
                {
                    cout << fullContents[i][j];
                }
                cout << endl;
            }
            myfile.close();
        }
        else cout << "Unable to open file";
    }
    /**
    void showContext() {
        for (int i = 0; i < fullContents.size(); i++) {
            cout << i << "| ";
            for (int j = 0; i < fullContents[i].size(); j++)
            {
                cout << fullContents[i][j];
            }
            cout << endl;
        }
    }
    **/
};

int main() {
    textEditor calculator;
    
    return 0;
}