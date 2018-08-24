#### 已知有如下4张表：
学生表：`Student(s_id,s_name,s_birth,s_sex)` –学生编号,学生姓名, 出生年月,学生性别

课程表：`Course(c_id,c_name,t_id)` – –课程编号, 课程名称, 教师编号

教师表：`Teacher(t_id,t_name)` –教师编号,教师姓名

成绩表：`Score(s_id,c_id,s_s_score)` –学生编号,课程编号,分数

1、查询课程编号为“001”的课程比“002”的课程成绩高的所有学生的学号。
【解题思路】首先查询课程编号分别为001和002的所有学生的学号及其分数作为内嵌视图A和B，然后将A和B通过学号关联，过滤条件就是A的分数大于B的分数，最终SQL如下：
```

SELECT A.S_ID

FROM(SELECT S_ID,S_SCORE FROM Score WHERE C_ID='001') A,

(SELECT S_ID,S_SCORE FROM Score WHERE C_ID='002')B

WHERE A.S_SCORE>B.S_SCORE

AND A.S_ID=B.S_ID;

```

