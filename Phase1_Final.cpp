#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class OS {
public:
    char M[100][4];
    char IR[4];
    char R[4];
    int IC;
    bool C;

    ifstream fin;
    ofstream fout;

    //  INIT
    void init() {
        for (int i = 0; i < 100; i++)
            for (int j = 0; j < 4; j++)
                M[i][j] = '*';   // better than space

        IC = 0;
        C = false;
    }

    //  PRINT MEMORY
    void printMemory() {
        for (int i = 0; i < 100; i++) {
            cout << i << " : ";
            for (int j = 0; j < 4; j++) {
                cout << "|" << M[i][j];
            }
            cout << "|\n";
        }
        cout << endl;
    }

    //  LOAD
    void load() {
        string line;
        int m = 0;

        fin.open("input1.txt");   
        fout.open("output.txt");

        if (!fin) {
            cout << "Error opening input file\n";
            return;
        }

        while (getline(fin, line)) {

            if (line.substr(0, 4) == "$AMJ") {
                init();
                printMemory();
                m = 0;
            }

            else if (line.substr(0, 4) == "$DTA") {
                printMemory();
                execute();
                printMemory();
            }

            else if (line.substr(0, 4) == "$END") {
                continue;
            }

            else {
                int i = 0;
                while (i < line.length()) {
                    for (int j = 0; j < 4; j++) {
                        if (i < line.length())
                            M[m][j] = line[i++];
                        else
                            M[m][j] = '*';
                    }
                    m++;
                }
            }
        }

        fin.close();
        fout.close();
    }

    //  EXECUTE
    void execute() {
        IC = 0;

        while (IC < 100) {

            // FETCH
            for (int i = 0; i < 4; i++)
                IR[i] = M[IC][i];

            IC++;

            // DEBUG TRACE
            cout << "IC=" << IC-1 << " IR=";
            for (int i = 0; i < 4; i++) cout << IR[i];
            cout << " C=" << C << endl;

            // DECODE + EXECUTE
            if (IR[0] == 'G' && IR[1] == 'D') {
                GD(getAddr());
            }
            else if (IR[0] == 'P' && IR[1] == 'D') {
                PD(getAddr());
            }
            else if (IR[0] == 'L' && IR[1] == 'R') {
                LR(getAddr());
            }
            else if (IR[0] == 'S' && IR[1] == 'R') {
                SR(getAddr());
            }
            else if (IR[0] == 'C' && IR[1] == 'R') {
                CR(getAddr());
            }
            else if (IR[0] == 'B' && IR[1] == 'T') {
                BT(getAddr());
            }
            else if (IR[0] == 'H') {
                break;
            }
            else {
                cout << "Invalid Instruction: ";
                for (int i = 0; i < 4; i++) cout << IR[i];
                cout << endl;
                break;
            }
        }
    }

    //  ADDRESS
    int getAddr() {
        return (IR[2] - '0') * 10 + (IR[3] - '0');
    }

    //  GD
    void GD(int addr) {
        string line;
        getline(fin, line);

        int k = 0;
        for (int i = addr; i < addr + 10 && i < 100; i++) {
            for (int j = 0; j < 4; j++) {
                if (k < line.length())
                    M[i][j] = line[k++];
                else
                    M[i][j] = '*';
            }
        }
    }

    //  PD
    void PD(int addr) {
        for (int i = addr; i < addr + 10 && i < 100; i++) {
            for (int j = 0; j < 4; j++) {
                if (M[i][j] == '*') return;
                fout << M[i][j];
            }
        }
        fout << endl;
    }

    //  LR
    void LR(int addr) {
        for (int i = 0; i < 4; i++)
            R[i] = M[addr][i];
    }

    //  SR
    void SR(int addr) {
        for (int i = 0; i < 4; i++)
            M[addr][i] = R[i];
    }

    //  CR
    void CR(int addr) {
        C = true;
        for (int i = 0; i < 4; i++) {
            if (R[i] != M[addr][i]) {
                C = false;
                break;
            }
        }
    }

    //  BT
    void BT(int addr) {
        if (C)
            IC = addr;
    }
};

int main() {
    OS os;
    os.load();
    return 0;
}