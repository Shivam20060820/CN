#include <iostream>
using namespace std;

int main() {
    int h[8], r[8], p1, p2, p4, error;

    cout << "Enter 4 data bits: ";
    cin >> h[3] >> h[5] >> h[6] >> h[7];

    h[1] = h[3] ^ h[5] ^ h[7];
    h[2] = h[3] ^ h[6] ^ h[7];
    h[4] = h[5] ^ h[6] ^ h[7];

    cout << "Transmitted Hamming code: ";
    for (int i = 1; i <= 7; i++) cout << h[i];

    cout << "\nEnter bit position to introduce error (0 for none): ";
    cin >> error;
    if (error >= 1 && error <= 7) h[error] ^= 1;

    cout << "Received code: ";
    for (int i = 1; i <= 7; i++) cout << h[i];

    p1 = h[1] ^ h[3] ^ h[5] ^ h[7];
    p2 = h[2] ^ h[3] ^ h[6] ^ h[7];
    p4 = h[4] ^ h[5] ^ h[6] ^ h[7];

    error = p1 + 2 * p2 + 4 * p4;

    if (error) {
        cout << "\nError detected at bit position: " << error;
        h[error] ^= 1;
        cout << "\nCorrected code: ";
    } else {
        cout << "\nNo error detected.";
        cout << "\nReceived code is: ";
    }

    for (int i = 1; i <= 7; i++) cout << h[i];
    cout << endl;

    return 0;
}