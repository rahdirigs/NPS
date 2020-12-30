#include <bits/stdc++.h>
using namespace std;

int generate_checksum(string& s) {
    int n = s.length();

    vector<int> s_data(n);
    for (int i = 0; i < n; i++) {
        s_data[i] = s[i] - '0';
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += s_data[i];
    }

    int checksum = ~sum;
    return checksum;
}

bool validate_checksum(string& r, int checksum) {
    int n = r.length();

    vector<int> r_data(n);
    for (int i = 0; i < n; i++) {
        r_data[i] = r[i] - '0';
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += r_data[i];
    }

    sum += checksum;
    int ret = ~sum;

    if (ret == 0)
        return true;
    else
        return false;
}

int main() {
    string s;
    cout << "Enter the sender's string: ";
    cin >> s;

    int checksum = generate_checksum(s);
    cerr << "Generated checksum:" << checksum << '\n';

    string recv_str;
    cout << "Enter the string at the receiver end: ";
    cin >> recv_str;

    if (s.length() != recv_str.length()) {
        cout << "Mismatch in string lengths!!!";
        return 0;
    }

    bool valid = validate_checksum(recv_str, checksum);

    if (valid) {
        cout << "No error in transmission...";
        return 0;
    } else {
        cout << "Error recognised in the received string!!!\n";
    }
}
