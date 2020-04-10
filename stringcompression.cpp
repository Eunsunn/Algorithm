#include <string>
#include <vector>

using namespace std;

int solution(string s) {
    int n = s.size() / 2;
    int answer = s.size();
    //n~1 순서로 탐색한다
    while (n > 0) {
        string sub = s.substr(0, n);
        int count = 1;
        string out = "";

        for (int i = n; i<= s.size(); i += n) {
            if (sub != s.substr(i, n)) {
                if (count == 1)//sub문자열이 반복되지 않으면
                    out += sub;
                else //반복되면
                    out += to_string(count) + sub; //횟수+문자열
                //다음 문자열을 찾는다
                count = 1;
                sub = s.substr(i, n);
            }
            else
                count++;
        }

        //나머지 문자열 더해주기
        if (s.size() % n != 0)
            out += s.substr((s.size() / n) * n);
        if (answer > out.size()) answer = out.size();
        n--;
    }
    return answer;
}

