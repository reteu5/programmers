# https://www.acmicpc.net/problem/1669

# 1 1 2 2 3 3 4 4 ...

def solution(x, y) :
    diff = y - x
    day = 0
    if diff == 0:
        return 0
    
    while True:
        day += 1
        if calcMaxFromDate(day) >= diff:
            return day
    
def calcMaxFromDate(day):
    if day % 2 == 0 :
        return (day // 2) * ((day // 2) + 1)
    else :
        return ((day // 2) * ((day // 2) + 1)) + ((day // 2) + 1)
    
if __name__ == "__main__" :
    x, y = map(int, input().split())
    print(solution(x, y))