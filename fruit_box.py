def solution(k, m, score):
    answer = 0

    score = sort_score(score)
    if (k < score[0]) :
        print("error")
    numberOfBox = len(score) // m

    # numberOfBox 만큼 score 배열을 앞에서부터 m개씩 나누고, (나눠진 배열의 원소 중 가장 작은 수) * m 을 answer에 더함
    for i in range(numberOfBox) :
        answer += min(score[i*m:(i+1)*m]) * m
    return answer

# int 배열인 score에 대하여 내림차순 정렬
def sort_score(score) :
    return sorted(score, reverse=True)