-- https://school.programmers.co.kr/learn/courses/30/lessons/276013

SELECT ID, EMAIL, FIRST_NAME, LAST_NAME FROM DEVELOPER_INFOS
WHERE SKILL_1 = "Python" or SKILL_2 = "Python" or SKILL_3 = "Python"
ORDER BY ID ASC;