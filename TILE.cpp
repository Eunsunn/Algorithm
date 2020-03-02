//문제: https://programmers.co.kr/learn/courses/30/lessons/43104
//프로그래머스 타일장식물
#include <string>
#include <vector>

using namespace std;
vector<long long> fibo = {4, 6};

long long solution(int N) {
    if (fibo.size() >= N) return fibo.at(N - 1);
    long long answer = solution(N-1) + solution(N-2);
    fibo.push_back(answer);
    return answer;
}

