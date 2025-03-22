#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;


void print(vector<string>& ans) {
    for (int i = 0; i < ans.size(); i++) {
        cout << setw(2) << setfill('0') << i + 1 << " " << ans[i] << endl ;
    }
}


void swap(char& a, char& b) {
    char temp = a ;
    a = b ;
    b = temp ;
}


void permutation(string& s, int start, int n, vector<string>& ans) {
    if (start == n-1) {
        ans.push_back(s) ;
        return ;
    }

    for (int i = start; i < n; i++) {
        swap(s[start], s[i]) ;
        permutation(s, start+1, n, ans) ;
        swap(s[start], s[i]) ;
    }
}


void dfs(int n, string track, string s, vector<string>& ans) {
    if (track.size() == n) {
        ans.push_back(track) ;
        return ;
    }

    for (int i = 0; i < n; i++) {
        if (track.find(s[i]) == string::npos) {
            track.push_back(s[i]) ;
            dfs(n, track, s, ans) ;
            track.pop_back() ;
        }
    }
}


int main() {
    string s = "abcde" ;
    int n = s.size() ;
    vector<string> ans ;
    // permutation(s, 0, n, ans) ;
    // print(ans) ;

    dfs(n, "", s, ans) ;
    print(ans) ;
    return 0 ;
}
