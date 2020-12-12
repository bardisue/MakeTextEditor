#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>

using namespace std;

vector<vector<string>> fullContents;
int firstPage = 0;
int lastPage = 20;

class excuteStrategy {
public:
    virtual void excute() = 0;
};

class textEditor {
public:
    textEditor(excuteStrategy *excutestrategy) {
        excutestrategy->excute();
    }
    void setExcuteStrategy(excuteStrategy* excute) {
        excutestrategy = excute;
    }
    virtual void excute() {
        excutestrategy->excute();
    }
protected:
    excuteStrategy *excutestrategy;
};

string strategy;

void makeConsole(string message) {
    for (int i = 0; i < 80; i++) {
        cout << "-";
    }
    cout << endl;
    cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후 종료" << endl;
    for (int i = 0; i < 80; i++) {
        cout << "-";
    }
    cout << endl;
    cout << message << endl;
    for (int i = 0; i < 80; i++) {
        cout << "-";
    }
    cout << endl;
    cout << "입력 :";
    cin >> strategy;
}

void showContext(int start, int end) {
    for (int i = start; i < end; i++) {
        cout.width(2);
        cout.fill(' ');
        cout << i + 1 << "| ";
        for (int j = 0; j < fullContents[i].size(); j++)
        {
            cout << fullContents[i][j];
        }
        cout << endl;
    }
}

int checkBytes(int index) {
    int bytes = 0;
    for (int i = 0; i < fullContents[index].size(); i++) {
        bytes += fullContents[index][i].length();
    }
    return bytes;
}

void makeSF(int start) {
    for (int i = start; i < fullContents.size(); i++) {
        while (checkBytes(i) > 76) {
            string toInsert = fullContents[i][fullContents[i].size() - 1];
            fullContents[i].pop_back();
            if (i == fullContents.size()-1) {
                fullContents.push_back(*new vector<string>);
            }
            fullContents[i + 1].insert(fullContents[i + 1].begin(), toInsert);
        }
    }
}

class Default : public excuteStrategy {
public:
    void excute() {
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
                int cByte = context.length()+1;
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
                fullContents[tmpLine][fullContents[tmpLine].size() - 1] = fullContents[tmpLine][fullContents[tmpLine].size() - 1] + " ";
            }
            myfile.close();
        }
        else cout << "Unable to open file";
        showContext(firstPage, lastPage);
        makeConsole("(입력메세지)");
    }
};

class Next : public excuteStrategy {
    void excute(){
        system("cls");
        if (fullContents.size() - lastPage >= 20) {
            firstPage += 20;
            lastPage += 20;
            showContext(firstPage, lastPage);
            makeConsole("(입력메세지)");
        }
        else {
            lastPage = fullContents.size();
            firstPage = lastPage - 20;
            showContext(firstPage, lastPage);
            makeConsole("마지막 페이지입니다");
        }
    }
};
class Pre : public excuteStrategy {
    void excute() {
        system("cls");
        if (firstPage== 0) {
            showContext(firstPage, lastPage);
            makeConsole("첫페이지 입니다.");
        }
        else if (firstPage < 20) {
            firstPage = 0;
            lastPage = 20;
            showContext(firstPage, lastPage);
            makeConsole("(입력메세지)");
        }
        else {
            firstPage -= 20;
            lastPage -= 20;
            showContext(firstPage, lastPage);
            makeConsole("(입력메세지)");
        }
    }
};
class Insert : public excuteStrategy {
    void excute() {
        system("cls");
        istringstream ss(strategy);
        string stringBuffer;
        vector<string> atribute;
        atribute.clear();
        while (getline(ss, stringBuffer, ',')) {
            atribute.push_back(stringBuffer);
        }
        int insertPage = firstPage + atoi(atribute[0].c_str())-1;
        int insertPoisition = atoi(atribute[1].c_str());
        string insertWord = atribute[2] + " ";
        fullContents[insertPage].insert(fullContents[insertPage].begin()+ insertPoisition, insertWord);
        makeSF(insertPage);
        showContext(firstPage, lastPage);
        makeConsole("마지막 페이지입니다");
    }
};
class Delete : public excuteStrategy {
    void excute() {

    }
};
class Change : public excuteStrategy {
    void excute() {

    }
};
class Search : public excuteStrategy {
    void excute() {

    }
};
class TextQ : public excuteStrategy {
    void excute() {

    }
};

//cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후 종료" << endl;

int main() {
    excuteStrategy *defal = new Default;
    excuteStrategy* next = new Next;
    excuteStrategy* pre = new Pre;
    excuteStrategy* insert = new Insert;
    excuteStrategy* delete1 = new Delete;
    excuteStrategy* change = new Change;
    excuteStrategy* search = new Search;
    excuteStrategy* textQ = new TextQ;
    textEditor *texteditor = new textEditor(defal);
    while (1) {
        switch (strategy[0])
        {
        case 'n':
            texteditor->setExcuteStrategy(next);
            texteditor->excute();
            break;
        case 'p':
            texteditor->setExcuteStrategy(pre);
            texteditor->excute();
            break;
        case 'i':
            strategy = strategy.substr(2, strategy.size() - 3);
            texteditor->setExcuteStrategy(insert);
            texteditor->excute();
            break;
        default:
            break;
        }
    }
    return 0;
}