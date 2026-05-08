/*
    [터렛]
    Source : https://www.acmicpc.net/problem/1002

    # 요약
    두 정점에서 각각 반지름이 r1, r2인 원을 그렸을 때, 두 원이 만나는 점의 개수를 구하여라.
    다만, 중심과 반지름의 구성에 따라 다양한 양상이 나타날 수 있으니, 모두 커버할 수 있도록 만전 ㄱ
*/

#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while(T--)
    {
        ll x1, y1, r1, x2, y2, r2;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        
        ll dx = x1 - x2;
        ll dy = y1 - y2;
        ll dist_sq = dx*dx + dy*dy;
        ll r_sum = r1 + r2;
        ll r_sum_sq = r_sum * r_sum;
        ll r_diff = (r1 > r2) ? (r1 - r2) : (r2 - r1);
        ll r_diff_sq = r_diff * r_diff;
        
        // 두 원의 중심이 일치하는 경우
        if(dist_sq == 0)
        {
            if(r1 == r2)
            {
                cout << "-1" << endl;
            }
            else
            {
                cout << "0" << endl;
            }
        }
        else
        {
            // 접점 X, 포함 X; 남남
            if(dist_sq > r_sum_sq)
            {
                cout << "0" << endl;
            }
            // 외접
            else if(dist_sq == r_sum_sq)
            {
                cout << "1" << endl;
            }
            // 하나가 다른 원을 포함하는 경우
            else
            {
                if(dist_sq < r_diff_sq)
                {
                    cout << "0" << endl;
                }
                // 내접
                else if(dist_sq == r_diff_sq)
                {
                    cout << "1" << endl;
                }
                else
                {
                    cout << "2" << endl;
                }
            }
        }
    }
}
