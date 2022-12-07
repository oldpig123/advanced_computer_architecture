#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    ifstream testbench;
    ofstream test_result;

    cout << "enter k for lenth of LBHT(2^k): ";
    int k = 5, m = 2;  // set 2 for default
    cin >> k;
    int LBHT_lenth = (int)(pow(2, k));
    m = (int)(64 / pow(2, k));
    int column = (int)pow(2, m), row = (int)pow(2, 10 - m);
    int predictor_stat[column][row];

    for (int i = 1; i <= 10; i++) {
        for (int ii = 0; ii < column; ii++) {
            for (int jj = 0; jj < row; jj++) {
                predictor_stat[ii][jj] = 3;
            }
        }
        cout << "../testbench/test_" + to_string(i) + ".bench" << endl;
        testbench.open("testbench/test_" + to_string(i) + ".bench");
        test_result.open("test_result/test_" + to_string(i) + ".txt");
        test_result << left << setw(12) << "address" << setw(14) << "branch taken" << setw(12) << "prediction" << setw(18) << "predictor status" << endl;
        test_result << "-----------------------------------------------------------------" << endl;
        int branch_history[LBHT_lenth];
        for (int j = 0; j < LBHT_lenth; j++) {
            branch_history[j] = 0;
        }

        double counter = 0, correct_predict = 0;

        while (!testbench.eof()) {
            long long int addr;
            char t_or_n, prediction;
            testbench >> addr;
            testbench >> t_or_n;

            int status = predictor_stat[branch_history[addr % LBHT_lenth]][addr % row];

            if (status == 3) {
                prediction = 'T';
                if (t_or_n == 'T') {
                    correct_predict++;
                } else {
                    predictor_stat[branch_history[addr % LBHT_lenth]][addr % row] = 2;
                }
            } else if (status == 2) {
                prediction = 'T';
                if (t_or_n == 'T') {
                    correct_predict++;
                    predictor_stat[branch_history[addr % LBHT_lenth]][addr % row] = 3;
                } else {
                    predictor_stat[branch_history[addr % LBHT_lenth]][addr % row] = 0;
                }
            } else if (status == 0) {
                prediction = 'N';
                if (t_or_n == 'N') {
                    correct_predict++;
                } else {
                    predictor_stat[branch_history[addr % LBHT_lenth]][addr % row] = 1;
                }
            } else {
                prediction = 'N';
                if (t_or_n == 'N') {
                    predictor_stat[branch_history[addr % LBHT_lenth]][addr % row] = 0;
                    correct_predict++;
                } else {
                    predictor_stat[branch_history[addr % LBHT_lenth]][addr % row] = 3;
                }
            }

            branch_history[addr % LBHT_lenth] = (branch_history[addr % LBHT_lenth] * 2 + ((t_or_n == 'T') ? 1 : 0)) % column;

            test_result << left << setw(12) << addr << setw(14) << t_or_n << setw(12) << prediction << setw(18) << status << " " << ((t_or_n == prediction) ? "correct prediction" : "wrong prediction") << endl;
            counter++;
        }
        test_result << "-----------------------------------------------------------------" << endl;
        test_result << "total instuctions: " << counter << endl;
        test_result << "correct predictions: " << correct_predict << endl;
        test_result << "accuracy: " << correct_predict / counter;
        cout << "total instuctions: " << counter << endl;
        cout << "correct predictions: " << correct_predict << endl;
        cout << "accuracy: " << correct_predict / counter << endl;
        testbench.close();
        test_result.close();
    }
}
