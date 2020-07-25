// Algospot DFS/BFS 
// https://programmers.co.kr/learn/courses/30/lessons/43165

#include <string>
#include <vector>
#include <iostream>
using namespace std;


//number를 DFS탐색해 target에 도달하는 경우의 수 반환
int DFS(vector<int> numbers, int idx, int sum, int target) {
    //마지막에 도착한 경우
    if (idx == numbers.size()) {
        if (sum == target) return 1;
        else return 0;
    }

    int ret = 0;
    //더하는 경우
    int add = sum + numbers[idx];
    ret += DFS(numbers, idx + 1, add, target);
    //뺴는 경우
    int dedu = sum - numbers[idx];
    ret += DFS(numbers, idx + 1, dedu, target);

    return ret;
}

int solution(vector<int> numbers, int target) {
    int answer = 0;

    //DFS
    answer = DFS(numbers, 0, 0, target);

    return answer;
}
