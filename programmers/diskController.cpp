// URL: https://school.programmers.co.kr/learn/courses/30/lessons/42627

#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// SJF 방식. (처리시간 짧은 순 >> 먼저 요청한 순 >> id 작은 순) && 한 번 착수하면 LOCK.
// 반환시간 (turnaround) == 요청 시점 ~ 완수 시점.
// (in) - vector of [요청시점s, 소요시간l].
// (out) - AVG(TaT).
// (opt) - jobs.length <= 500.
/* approach --> 우선순위 큐(heap)
 * 요청 순으로 담고, 꺼낼 때에는 {1. 작업 시간 짧은 순, 2. 먼저 들어간 순 3. id 순}으로 호출
 */




struct Job {
    int id;
    int start;
    int length;
};

struct Compare {
    bool operator()(const Job& a, const Job& b) {
        // 1. SJF
        if (a.length != b.length) {
            return a.length > b.length;
        }

        // 2. FC-FS
        if (a.start != b.start) {
            return a.start > b.start;
        }

        // 3. ORDER BY id ASC
        return a.id > b.id;
    }
};

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    int n = jobs.size();

    vector<Job> arr;

    for (int i = 0; i < n; i++) {
        arr.push_back({i, jobs[i][0], jobs[i][1]});
    }

    // 요청 시각 순 정렬
    sort(arr.begin(), arr.end(), [](const Job& a, const Job& b) {
        if (a.start != b.start) {
            return a.start < b.start;
        }
        return a.id < b.id;
    });

    priority_queue<Job, vector<Job>, Compare> pq;

    long long currentTime = 0;
    long long totalTurnaround = 0;

    int idx = 0;
    int finished = 0;

    while (finished < n) {
        // currentTime까지의 요청 추가 (pq 갱신)
        while (idx < n && arr[idx].start <= currentTime) {
            pq.push(arr[idx]);
            idx++;
        }

        // 대기 큐가 비어 있으면 다음 작업 요청 시각으로 점프
        if (pq.empty()) {
            currentTime = arr[idx].start;
            continue;
        }

        // 우선순위 가장 높은 작업 수행
        Job cur = pq.top();
        pq.pop();

        currentTime += cur.length;

        // 반환 시간 = 작업 종료 시각 - 요청 시각
        totalTurnaround += currentTime - cur.start;

        finished++;
    }

    answer = totalTurnaround / n;
    
    return answer;
}