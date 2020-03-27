#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//결정문제: location중 cameras를 선택해 모든 카메라의 간격이
//			gap이상이 되는 방법이 있는지 반환
bool decision(const vector<double>& location, int cameras, double gap) {
	double limit = -1;
	int installed = 0;
	for(int i=0; i<location.size(); i++)
		if (limit <= location[i]) {
			++installed;
			//location[i]+gap 이후는 되어야 카메라를 설치할 수 있음
			limit = location[i] + gap;
		}
	//cameras대 이상 설치할 수 있으면 성공
	return installed >= cameras;
}

//최적화 문제: 정렬된 locations 중 cameras를 선택해 최소간격을 최대화
double optimize(const vector<double>& location, int cameras) {
	double lo = 0, hi = 241;
	//반복문 불변식: decision(lo) && !decision(hi)
	//while(lo+1<hi) (X)
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2.0;
		//간격이 mid 이상이 되도록 할 수 있으면 답은 [mid, hi]에 있음
		if (decision(location, cameras, mid))
			lo = mid;
		else //hi에는 답이 없음
			hi = mid;
	}
	return lo;
}

int main() {
	int test;
	cin >> test;
	int cameras, spots;
	vector<double> location;
	
	for (int t = 0; t < test; t++) {
		double temp;
		location.clear();
		cin >> cameras >> spots;
		for (int i = 0; i < spots; i++)
		{
			cin >> temp;
			location.push_back(temp);
		}
		printf("%.2f\n", optimize(location, cameras));
	}
}
