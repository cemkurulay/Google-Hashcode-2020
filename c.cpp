#include <bits/stdc++.h>
using namespace std;
//unordered_map<int, int> scores;
int scores[100005];
bool bookTaken[100005];

struct Library {
    int bookCount;
    int sign;
    int scanPerDay;
    vector<pair<int,int>> books;
};

Library libraries[100005];
bool libTaken[100005];

int main() {
    int b, l, d, tmp;
    cin >> b;
    cin >> l;
    cin >> d;
    for (int i = 0; i < b; i++) {
        cin >> tmp;
        scores[i] = tmp;
    }

    for (int i = 0; i < l; i++) {
        cin >> tmp;
        libraries[i].bookCount = tmp;
        cin >> tmp;
        libraries[i].sign = tmp;
        cin >> tmp;
        libraries[i].scanPerDay = tmp;
        for (int j = 0; j < libraries[i].bookCount; j++) {
            cin >> tmp;
            libraries[i].books.push_back(make_pair(scores[tmp], tmp));
        }
        sort(libraries[i].books.begin(), libraries[i].books.end(), greater<>());
    }

    //en son l -1 , d - sign up seçilen lib, booktaken libtaken marks
    int score = -1;
    int selectedLib = 0;
    int c;
    int libCount = l;
    vector<int> selectedLibBooks;
    vector<int> tmpBooks;
    int maxScore;
    int currentIndex;
    queue<pair<int, vector<int>>> que;
    while (libCount > 0 && d > 0 && score != 0 && selectedLib != -1) {
        selectedLib = -1;
        maxScore = 0;
        for (int i = 0; i < l; i++) {
            score = 0;
            tmpBooks = vector<int>();
            if (!libTaken[i] && libraries[i].sign <= d) {
                if ((d - libraries[i].sign) * libraries[i].scanPerDay > libraries[i].bookCount) {
                    c = libraries[i].bookCount;
                } else {
                    c = (d - libraries[i].sign) * libraries[i].scanPerDay;
                }
                for (int j = 0; j < c; j++) {
                    if (bookTaken[libraries[i].books[j].second]) {
                        if (!(libraries[i].bookCount < c + 1)) {
                            c++;
                        }
                    } else {
                        score += scores[libraries[i].books[j].second];
                        tmpBooks.push_back(libraries[i].books[j].second);
                    }
                }
            }
            if (score > maxScore) {
                selectedLib = i;
                selectedLibBooks = tmpBooks;
                maxScore = score;
            }
        }
        if (selectedLib != -1) {
            for (int j = 0; j < selectedLibBooks.size(); j++) {
                bookTaken[selectedLibBooks[j]] = 1;
            }
            libTaken[selectedLib] = 1;
            que.push(make_pair(selectedLib, selectedLibBooks));
            libCount--;
            d -= libraries[selectedLib].sign;
        }
    }

    pair<int, vector<int>> tmpPair;
    cout << que.size() << endl;
    int queS = que.size();
    //cout << "Que Size " <<  que.size() << endl;
    for (int i = 0; i < queS; i++) {
        tmpPair = que.front();
        cout << tmpPair.first << " " << tmpPair.second.size() << endl;
        for (int j = 0; j < tmpPair.second.size(); j++) {
            cout << tmpPair.second[j] << " "; 
        }
        cout << endl;
        que.pop();
    }
    
    return 0;
}