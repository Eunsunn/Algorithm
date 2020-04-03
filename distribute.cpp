#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> budgets, int M) {
    sort(budgets.begin(), budgets.end());

    if (budgets[0] * budgets.size() > M)
        return M / budgets.size();
    
    long sum = 0;
    for (int i = 0; i < budgets.size(); i++)
        sum += budgets[i];
    if (sum <= M)
        return budgets[budgets.size()-1];

    int lo = M/budgets.size(), hi = budgets[budgets.size()-1];
    int mid;
    int temp = 0;
    int answer = 0;

    while (true) {
        mid = (lo + hi) / 2;

        sum = 0;
        int i = 0;
        for (; i < budgets.size(); i++)
            if (budgets[i] < mid)
                sum += budgets[i];
            else
                sum += mid;

        if (temp == mid) {
            answer = mid;
            break;
        }

        if (sum > M)
            hi = mid;
        else
            lo = mid;
        temp = mid;
    }
    return answer;
}
