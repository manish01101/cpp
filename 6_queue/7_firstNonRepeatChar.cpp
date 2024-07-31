#include<iostream>
#include<unordered_map>
#include<queue>
using namespace std;

string firstNon(string s) {
    unordered_map<char, int> count;
    queue<int> q;
    string ans = "";

    for (int i = 0; i < s.length(); i++) {
        char ch = s[i];
        //increase count
        count[ch]++;

        q.push(ch);

        while (!q.empty()) {
            if (count[q.front()] > 1) {
                //repeating char
                q.pop();
            }
            else {
                //non repeating
                ans.push_back(q.front());
                break;
            }
        }
        if (q.empty())
            ans.push_back('#');
    }
    return ans;
}
int main() {
    string s = "aabc";
    string ans = firstNon(s);
    cout << ans << endl;
}
