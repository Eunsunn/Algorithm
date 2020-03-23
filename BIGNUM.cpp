#include <iostream>
#include <string>
#include <vector>

using namespace std;

//문제: https://programmers.co.kr/learn/courses/30/lessons/42883
//프로그래머스 큰 수 만들기

string solution(string number, int k) {
	vector<char> ls;
	for (int i = 0; i < number.size(); i++)
		ls.push_back(number[i]);
	for (int remv = 0; remv < k; remv++) {
		//삭제할거 찾기
		vector<char>::iterator it = ls.begin();
		while (true) {
			int temp1 = *it++ -'0';
			int temp2 = *it - '0';
			if (temp1< temp2 || it==ls.end())
				break;
		}
		ls.erase(--it);
	}
	string out = "";
	for (int i = 0; i < ls.size(); i++)
		out += ls[i];
	return out;
}
