from typing import List
from collections import defaultdict

def racing_results(races: List[List[int]]) -> str:
    result = ""
    dic = {1:10, 2:6, 3:4, 4:3, 5:2}
    scores = defaultdict(int)

    for element in races:
        [race, racer_name, position] = element
        scores[racer_name] += dic[position]

    max_score = 0
    for name, score in scores.items():
        if score > max_score:
            max_score = score
            result = name
        elif score == max_score:
            result = min(result, name)

    return result, max_score

if __name__ == "__main__":
    races = [[2001, 1001, 3], [2001, 1002, 2], [2002, 1003, 1], 
             [2002, 1001, 2], [2002, 1002, 3], [2001, 1003, 1]]
    print(racing_results(races))

    races = [[2001, 1001, 1], [2001, 1002, 1], [2002, 1003, 1], 
             [2002, 1001, 1], [2002, 1002, 1], [2001, 1003, 1]]
    print(racing_results(races))