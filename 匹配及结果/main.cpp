#include <iostream>
#include <string>
#include <vector>
#include <map>
#include<fstream>
#include <ctime>
#include <cstdlib>
#include <cstdio>

using namespace std;

vector<int> initNext(string T) {
    int i = 0, j = 0;
    vector<int> res;
    res.push_back(-1);
    res.resize(T.size() + 1);
    j = res[i];
    while (i < T.size()) {
        if (j == -1 || T[i] == T[j]) {
            res[++i] = ++j;
        } else {
            j = res[j];
        }
    }
    return res;
}


int KMPMatch(string p, string t) {
    vector<int> next = initNext(p);
    int i = 0, j = 0;
    while (i < (int) t.length() && j < (int) p.length()) {
        if (j == -1 || t[i] == p[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }

    if (j == p.length()) {
        return i - j;
    } else {
        return -1;
    }

}

ostream &operator<<(ostream &os, vector<int> a) {
    for (auto x: a) {
        os << x << ' ';
    }
    os << endl;
    return os;
}

struct initNum {
    int num;

    initNum() : num(-1) {}

    initNum(int x) : num(x) {}

};

ostream &operator<<(ostream &os, initNum a) {
    return os << a.num;
}

map<char, initNum> initBadChar(string s) {
    map<char, initNum> m;
    for (int i = 0; i < s.length(); i++) {
        m[s[i]] = i;
    }
    return m;
}


vector<int> suffix(string s) {
    int len = (int) s.length();
    vector<int> res(len + 2);
    int q;
    for (int i = len - 2; i >= 0; --i) {
        q = i;
        while (q >= 0 && s[q] == s[len - 1 - i + q]) {
            --q;
        }
        res[i] = i - q;
    }
    return res;
}

vector<int> initGoodString(string s) {

    int i, j;
    int len = (int) s.length();
    vector<int> ans(len);
    vector<int> suf = suffix(s);


    for (i = 0; i < len; ++i) {
        ans[i] = len;
    }
    for (i = len - 1; i >= 0; --i) {
        if (suf[i] == i + 1) {
            for (j = 0; j < len - 1; ++j) {
                if (ans[j] == len) {
                    ans[j] = len - 1 - i;
                }
            }
        }
    }

    for (i = 0; i < len - 1; ++i) {
        ans[len - 1 - suf[i]] = len - 1 - i;
    }
    return ans;
}

int BMMatch(string P, string T) {
    int m = P.length(), n = T.length();
    vector<int> Gs = initGoodString(P);
    map<char, initNum> Bc = initBadChar(P);
    int j = 0, i = m - 1;
    while (j <= n - m) {
        i = m - 1;
//        cout << P[i] << ' ' << T[i + j] << endl;
        while (i >= 0 && P[i] == T[i + j]) {
//            cout << P[i] << ' ' << T[i + j] << endl;
            i--;
        }
        if (i == -1) {
            return j;
        } else {
//            if (Gs[i] > i - Bc[T[i + j]].num) {
//                cout << "GS:";
//            } else {
//                cout << "BC:";
//            }
//            cout << "hhh" << max(Gs[i], i - Bc[T[i + j]].num) << endl;
            j += max(Gs[i], i - Bc[T[i + j]].num);
        }

    }
    return -1;
}

clock_t start, end;

int main() {
    freopen("../out.txt", "w", stdout);
    string y[100];
//    cin >> x >> y;


//    start = clock();
//    while (in >> y[cnt++]);
//    ::end = clock();
//    printf("数据全为01的情况：\n");
//    cout << (double) ((double) (-start + ::end) / CLOCKS_PER_SEC) << endl;
    for (int t = 1; t <= 3; t++) {
        ifstream in;
        int cnt = 0;
        string filename = "../strings";
        filename += to_string(t);
        filename += ".txt";
        cout << filename << endl;
        in.open(filename);
        while (in >> y[cnt++]);
        for (int i = 0; i < 10; i += 2) {
            printf("第%d次测试：\n主串尺寸为：%d，模式串尺寸为：%d\n\n", i / 2 + 1, y[i].length(), y[i + 1].length());

            start = clock();
            cout << "BM算法匹配结果：" << BMMatch(y[i + 1], y[i]) << endl;
            ::end = clock();
            cout << "BM算法耗费时间：" << (double) ((double) (-start + ::end) / CLOCKS_PER_SEC) << 's' << endl;
            cout << endl;
            start = clock();
            cout << "KMP算法匹配结果：" << KMPMatch(y[i + 1], y[i]) << endl;
            ::end = clock();
            cout << "KMP算法耗费时间：" << (double) ((double) (-start + ::end) / CLOCKS_PER_SEC) << 's' << endl << endl;
        }
        in.close();
        cout << endl;
    }


//    in.open("../strings2.txt");
//    cnt = 0;
//    while (in >> y[cnt++]);
//    printf("数据全为数字的情况：\n");
//    for (int i = 0; i < 10; i += 2) {
//        printf("第%d次测试：\n主串尺寸为：%d，模式串尺寸为：%d\n", i / 2 + 1, y[i].length(), y[i + 1].length());
//
//        start = clock();
//        cout << "BM算法匹配结果：" << BMMatch(y[i + 1], y[i]) << endl;
//        ::end = clock();
//        cout << "BM算法耗费时间：" << (double) ((double) (-start + ::end) / CLOCKS_PER_SEC) << 's' << endl;
//        start = clock();
//        cout << "KMP算法匹配结果：" << KMPMatch(y[i + 1], y[i]) << endl;
//        ::end = clock();
//        cout << "KMP算法耗费时间：" << (double) ((double) (-start + ::end) / CLOCKS_PER_SEC) << 's' << endl;
//    }
//    in.close();


    fclose(stdout);
//    cout << BMMatch(x, y) << endl;
//    cout << KMPMatch(x, y) << endl;

}
