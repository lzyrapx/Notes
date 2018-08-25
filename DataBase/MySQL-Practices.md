#### 已知有如下4张表：
#### 学生表：`Student(s_id,s_name,s_birth,s_sex)` –学生编号,学生姓名, 出生年月,学生性别

#### 课程表：`Course(c_id,c_name,t_id)` – –课程编号, 课程名称, 教师编号

#### 教师表：`Teacher(t_id,t_name)` –教师编号,教师姓名

#### 成绩表：`Score(s_id,c_id,s_s_score)` –学生编号,课程编号,分数

#### 1、查询课程编号为“001”的课程比“002”的课程成绩高的所有学生的学号。

【解题思路】首先查询课程编号分别为001和002的所有学生的学号及其分数作为内嵌视图A和B，然后将A和B通过学号关联，过滤条件就是A的分数大于B的分数，最终SQL如下：
```
SELECT A.S_ID

FROM(SELECT S_ID,S_SCORE FROM Score WHERE C_ID='001') A,

(SELECT S_ID,S_SCORE FROM Score WHERE C_ID='002')B

WHERE A.S_SCORE>B.S_SCORE

AND A.S_ID=B.S_ID;

```
#### 2、查询平均成绩大于60分的学生的学号和平均成绩
【解题思路】通过Score表即可获取，按照Score表的S_ID分组后即可求出平均成绩，最后通过HAVING子句来过滤平均分大于60的学生:
```
select S_ID, avg(s_score) from Score group by S_ID having avg(s_score)>60;
```

#### 3、查询所有学生的学号、姓名、选课数、总成绩
【解题思路】学生姓名通过STUDENT表获取，成绩通过SC表获取，考察的是COUNT和GROUPBY函数，最终SQL如下：
```
select student.s_id,student.s_name,count(score.s_id),sum(score.s_score)
from student
join score
on student.s_id=score.s_id
group by student.s_id;

```
#### 4、查询姓“猴”的老师的个数
【解题思路】考察模糊查询
```
select count(T_ID)
from teacher 
where t_name like '猴%';
```
#### 5、查询没学过“猴子”老师课的学生的学号、姓名
【解题思路】首先查询学习过“猴子”老师课的学生的学号作为子查询，而“猴子”老师涉及到TEACHER表，TEACHER表要和学生有关联必须通过课程和成绩表。
```
select Student.S_ID, Student.S_name 
from Student 
where S_ID not in (select distinct(SCORE.S_ID) from SCORE,Course,Teacher 
where Score.C_ID=Course.C_ID AND teacher.T_ID=Course.T_ID AND Teahcer.T_name ='猴子');
```
#### 6、查询学过“猴子”老师所教的所有课的同学的学号、姓名
【解题思路】题目说的是查询学过“猴子”老师所教的所有课的同学的学号、姓名，举个例子，比如“猴子”老师教过语文和数学，那么就得找出哪些同学同时学习了语文和数学这2门课程。
```
select S_ID,S_name   
from Student    
where S_ID in (select S_ID from SCORE ,Course ,Teacher 
where SCORE.C_ID=Course.C_ID and Teacher.T_ID=Course.T_ID 
and Teacher.T_name='猴子' group by S_ID 
having count(SCORE.C_ID)=(select count(C_ID) from Course,Teacher  
where Teacher.T_ID=Course.T_ID and T_name='猴子'));
```
#### 7、查询学过编号为“001”的课程并且也学过编号为“002”的课程的学生的学号、姓名.
```
select Student.S_ID,Student.S_name 
from Student,SCORE where Student.S_ID=SCORE.S_ID 
and SCORE.C_ID='001'and 
exists( Select * from SCORE as SCORE_2 where SCORE_2.S_ID=SCORE.S_ID and SCORE_2.C_ID='002');
```


#### 8、查询课程编号为“002”的总成绩
【解题思路】考查SUM 函数
```
select sum(s_score) from SCORE where C_ID='002';
```

#### 9、查询所有课程成绩小于60分的学生的学号、姓名
```
select S_ID, s_name 
from Student 
where s_id not in 
(select Student.s_id from Student, Score where s.s_id = Score.s_id and s_score>60);
```

#### 10、查询没有学全所有课的学生的学号、姓名
【解题思路】也就是学生学习的课程数小于总的课程数
```
select Student.s_id, Student.s_name 
from Student, Score
where Student.s_id=Score.s_id 
group by Student.s_id, Student.s_name 
having count(c_id)<(select count(c_id) from Course);
```

#### 11、查询至少有一门课与学号为“1001”的学生所学课程相同的学生的学号和姓名
【解题思路】首先找出学号为1001的学生学习过的课程，然后根据这些课程号就可以找到有哪些学生学习过部分1001学生学习过的课程
```
select s_id, S_name 
from Student, SCORE 
where Student.s_id = Score.s_id 
and c_id in (select c_id from SCORE where s_id='1001');
```
#### 12、查询和“1001”号同学所学课程完全相同的其他同学的学号
【解题思路】首先找出学号为1001的学生学习过的课程，然后根据这些课程号和所学课程总数就可以找到有哪些同学学习过和他一样的课程
```
select sno from Score 
where c_id in(select c_id from Score  where sno='1001')
group by sno 
having count(*)=(select count(*) from Score where sno='1001')
```

#### 13、把“SCORE”表中“猴子”老师教的课的成绩都更改为此课程的平均成绩
【解题思路】考察数据库更改操作。首先找到“猴子”老师教过哪些课程及其课程的平均成绩，然后根据课程号关联成绩表进行更新
```
Update Score Set S_score = (Select Avg(s2_S_score) From Score s2 Where s2.c_id=Score.c_id)  
Where c_id IN
(Select c_id From Score cs INNER JOIN Teacher tc ON cs.t_id = tc.t_id WHERE t_name ='猴子');
```

#### 14、查询和“1002”号的同学学习的课程完全相同的其他同学学号和姓名
```
select s_id from Score where c_id  
in (select c_id from Score where s_id='1002') 
group by s_id having count(*)=
(select count(*) from Score where s_id='1002');
```

#### 15、删除学习过“猴子”老师课的成绩表记录
【解题思路】
```
delect Score 
from Course, Teacher
where Course.c_id=Score.c_id 
and Course.t_id=teacher.t_id 
and t_name='猴子';
```

#### 16、向成绩表中插入一些记录这些记录要求符合以下条件：没有上过编号为“003”课程的学生的学号、编号为002的课程的平均成绩
```
Insert SCORE select S_ID,'002',
(Select avg(s_score) from SCORE where C_ID='002') 
from Student where S_ID not in (Select S_ID from SCORE where C_ID='003');
```

#### 17、按平均成绩从高到低显示所有学生的“数据库”（c_id='004'）、“企业管理”（c_id='001'）、“英语”（c_id='006'）三门的课程成绩，按如下形式显示：学生ID，数据库，企业管理，英语，有效课程数，有效平均分select s_id as 学生ID,
```
select s_id from Student as 学生ID,
(select s_score from Score where Score.s_id=t.s_id and c_id='004') as 数据库,
(select s_score from Score where Score.s_id=t.s_id and c_id='001') as 企业管理,
(select s_score from Score where Score.s_id=t.s_id and c_id='006') as 英语,
count(*) as 有效课程数, avg(t.s_score) as 平局成绩
from Score as t
group by s_id 
order by avg(t.s_score)
```
#### 18、查询各科成绩最高和最低的分： 以如下的形式显示：课程ID，最高分，最低分
```
select L.c_id as 课程ID, L.s_score as 最高分,
R.s_score as 最低分 from Score L, Score R 
where L.c_id = R.c_id 
and 
L.s_score = (select max(IL.s_score) from Score IL, Student as IM where L.c_id=IL.c_id and IM.s_id=IL.s_id group by IL.c_id) 
and 
R.s_score = (select min(IR.s_score) from Score as IR where R.c_id = IR.c_id group by IR.c_id);
```
#### 19、按各科平均成绩从低到高和及格率的百分数从高到低排列，以如下形式显示：课程号课程名平均成绩及格百分数
```
SELECT t.C_ID AS 课程号,
max(Course.C_name)AS 课程名,
isnull(AVG(s_score),0) AS 平均成绩,
100 * SUM(CASE WHEN  isnull(s_score,0)>=60 THEN 1 ELSE 0 END)/COUNT(*) AS 及格百分数     
FROM SCORE T,Course     
where t.C_ID=Course.C_ID     
GROUP BY t.C_ID      
ORDER BY 100 * SUM(CASE WHEN  
isnull(s_score,0)>=60 THEN 1 ELSE 0 END)/COUNT(*) DESC;
```
#### 20、查询如下课程平均成绩和及格率的百分数（用1行显示），其中企业管理为001，马克思为002，UML为003，数据库为004这个不做21、查询不同老师所教不同课程平均分从高到低显示
```
SELECT max(Z.T_ID) AS 教师ID, 
MAX(Z.T_name) AS 教师姓名, 
C.C_ID AS 课程ID, 
AVG(S_score) AS 平均成绩      
FROM SCORE AS T,Course AS C ,Teacher AS Z     
where T.C_ID=C.C_ID and C.T_ID=Z.T_ID    
GROUP BY C.C_ID     
ORDER BY AVG(S_score) DESC;
```
#### 22、查询如下课程成绩第3名到第6名的学生成绩单，其中企业管理为001，马克思为002，UML为003，数据库为004，以如下形式显示：学生ID学生姓名企业管理马克思UML数据库平均成绩
```
这个不做
```
#### 23、使用分段[100-85],[85-70],[70-60],[<60]来统计各科成绩，分别统计各分数段人数：课程ID和课程名称
```
SELECT SCORE.C_ID as 课程ID, C_name as 课程名称,
SUM(CASE WHEN s_score BETWEEN 85 AND 100 THEN 1 ELSE 0 END) AS [100 - 85]  ,
SUM(CASE WHEN s_score BETWEEN 70 AND 85 THEN 1 ELSE 0 END) AS [85 - 70],
SUM(CASE WHEN s_score BETWEEN 60 AND 70 THEN 1 ELSE 0 END) AS [70 - 60],
SUM(CASE WHEN s_score < 60 THEN 1 ELSE 0 END) AS [60 -]     
FROM SCORE,Course     
where SCORE.C_ID=Course.C_ID     
GROUP BY SCORE.C_ID,C_name;
```
#### 24、查询学生平均成绩及其名次
```
SELECT 1+(SELECT COUNT( distinct 平均成绩)                
FROM (SELECT S_ID,AVG(s_score) AS 平均成绩                       
FROM SCORE                   
GROUP BY S_ID  ) AS T1  WHERE 平均成绩 > T2.平均成绩) as 名次,       
S_ID as 学生学号,平均成绩      
FROM (SELECT S_ID,AVG(s_score) 平均成绩             
FROM SCORE         
GROUP BY S_ID ) AS T2      
ORDER BY 平均成绩 desc; 
```
#### 25、查询各科成绩前三名的记录（不考虑成绩并列情况）
```
SELECT t1.S_ID as 学生ID,t1.C_ID as 课程ID,S_score as 分数       
FROM SCORE t1        
WHERE s_score IN (SELECT TOP 3 s_score               
FROM SCORE               
WHERE t1.C_ID= C_ID             
ORDER BY s_score DESC) ; 
```
#### 26、查询每门课程被选修的学生数
```
select c_id, count(s_id) from Score group by c_id;
```
#### 27、查询出只选修了一门课程的全部学生的学号和姓名
```
select Score.s_id, Student.s_name, count(c_id) as 选课数
from Score,Student 
where Score.s_id =Student.s_id 
group by Score.s_id,Student.s_name 
having count(c_id)=1;
```
#### 28、查询男生、女生人数
```
select count(S_sex) as 男生人数 
from Student group by S_sex having S_sex='男'；
select count(S_sex) as 女生人数 
from Student group by S_sex having S_sex='女';
```
#### 29、查询姓“张”的学生名单
```
select s_name from Student where s_name like '张%';
```
#### 30、查询同名同性学生名单并统计同名人数
```
select sanme,count(*) from Student 
group by s_name 
having count(*)>1;
```
#### 31、1981年出生的学生名单（注：Student表中s_birth列的类型是datetime）
```
select s_name, convert(char(11),DATEPART(year,s_birth)) as age
from Student 
where convert(char(11),DATEPART(year,S_birth))='1981';
``` 
#### 32、查询平均成绩大于85的所有学生的学号、姓名和平均成绩
```
select S_name,SCORE.S_ID ,avg(s_score)     
from Student,SCORE      
where Student.S_ID=SCORE.S_ID 
group by SCORE.S_ID,S_name 
having avg(s_score)>85;
```
#### 33、查询每门课程的平均成绩，结果按平均成绩升序排序，平均成绩相同时，按课程号降序排列
```
select C_ID, avg(s_score) 
from Score 
group by c_id 
order by avg(s_score), c_id desc;
```
#### 34、查询课程名称为“数据库”且分数低于60的学生姓名和分数
```
select s_name, isnull(s_score,0) 
from Student, Score ,Course 
where Score.s_id=Student.s_id  
and Score.c_id=Course.c_id and Course.c_name='数据库' and s_score<60;
```
#### 35、查询所有学生的选课情况
```
select Score.s_id,Score.c_id,s_name,c_name 
from Score,Student Course 
where Score.s_id=Student.s_id and Score.c_id=Course.c_id;
```
#### 36、查询任何一门课程成绩在70分以上的姓名、课程名称和分数
```
select distinct Student.s_id,Student.s_name,Score.c_id,Score.s_score 
from Student,Score 
where Score.s_score>=70 and Score.s_id=Student.s_id;
```
#### 37、查询不及格的课程并按课程号从大到小排列
```
select c_id from Score
where s_score < 60 order by c_id;
```
#### 38、查询课程编号为003且课程成绩在80分以上的学生的学号和姓名
```
select Score.s_id,Student.s_name 
from Score,Student 
where Score.s_id=Student.s_id and s_score>80 and c_id='003';
```
#### 39、查询选了课程的学生人数
```
select count(*) from Score;
```
#### 40、查询选修“猴子”老师所授课程的学生中成绩最高的学生姓名及其成绩
```
select Student.s_name,s_score 
from Student,Score,Course c, teacher 
where Student.s_id=Score.S_ID and Score.c_id=c.c_id
and c.T_ID=teacher.T_ID
and teacher.t_name='猴子' 
and Score.s_score=(select max(s_score) from Score where c_id=c.c_id);
```
#### 41、查询各个课程及相应的选修人数
```
select count(*) from Score group by c_id;
```
#### 42、查询有2门不同课程成绩相同的学生的学号、课程号、学生成绩
```
select distinct a.s_id,b.s_score 
from Score a ,Score b 
where a.s_score=b.s_score 
and a.c_id<>b.c_id;
```
#### 43、查询每门课程成绩最好的前两名
```
select t1.s_id as 学生ID,t1.c_id  课程ID, S_score as 分数
from Score t1 
where s_score in (select top 2 s_score from Score         
where t1.c_id=c_id        
order by s_score desc)order by t1.c_id;
```
#### 44、统计每门课程的学生选修人数(超过10人的课程才统计)。要求输出课程号和选修人数，查询结果按人数降序排序，若人数相同，按课程号升序排序
```
select c_id as 课程号,count(*) as 人数
from Score group by c_id
order by count(*) desc c_id;
```
#### 45、查询至少选修两门课程的学生学号
```
select s_id 
from Score 
group by s_id having count(*)>=2;
```
#### 46、查询全部学生都选修的课程的课程号和课程名
```
select c_id ,c_name
from Course 
where c_id in (select c_id from Score group by c_id);
```
#### 47、查询没学过“猴子”老师讲授的任一门课程的学生姓名
```
select s_name 
from Student 
where s_id not in (select s_id from Course,teacher,Score 
where Course.t_id=teacher.t_id and Score.c_id=Course.c_id 
and t_name='猴子');
```
#### 48、查询两门以上不及格课程的同学的学号及其平均成绩
```
select s_id,avg(isnull(s_score,0)) 
from Score 
where s_id in (select s_id from Score 
where s_score<60 group by s_id having count(*)>2)
group by s_id;
```
#### 49、检索课程编号为“004”且分数小于60的学生学号，结果按按分数降序排列
```
select s_id 
from Score 
where c_id='004' and s_score<60 
order by s_score desc;
```
#### 50、删除学生编号为“002”的课程编号为“001”的成绩
```
delect from Score where s_id='002' and c_id='001';
```


