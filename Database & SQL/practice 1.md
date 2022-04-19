

## In
> 단일 값(single value)이 다수 값에 속하는가를 검사

- Get names and salaries of professor who has ID with 10 or 21 or 22
  - ```sql
Select name, salary
from professor
where pID in (10, 21, 22); // 이 안에 존재하면 참```

## comparision
> 값 하나 간의 비교는 간단하나, 값 하나와 여러 값 간의 비교는 간단하지 않다. 그래서 __some, any, all__연산자를 지원한다

- example
  - (1>2) : false
  - (3 > **all** {2,3}) : false // 3>2이고, 3>3이어야 참
  - (3 > **some** {2,3}) : true // 3>2이기 때문에 참
  - (3 > **any** {2,3}) : any = some
- any = some
  - any (= some)은 “속한다” 의미의 in 연산자와 동일
  - not some 다수 개의 중의 하나와도 같이 않으면 참인데, ”not in"는 전체에 속하지 않아야 참이므로,동일하지 않다.
- 등호와 사용
  - ![](https://images.velog.io/images/yesterdaykite/post/5f91596a-d425-419a-8b8e-4168fd616019/image.png)
  - ![](https://images.velog.io/images/yesterdaykite/post/478db98b-c499-430d-9e58-90cfadc33a9b/image.png)

### set comparision EX
- Find professor names with salary greater than that of some (at least one) professor in CS department

```sql
// ver1
Select name, salary
from professor as T, professor as S
where T.salary > S.salary and S.deptName='CS'

//ver2
Select name
from professor
where salary > some (select salary
		     from professor
             where deptName = 'CS');
```

- Find the professor names whose salary is greater than the salary of all professors in CS department
```sql
Select name
from professor
where salary > all (select salary
                    from professor
                    where deptName='CS');
```

## Correlated Subqueries
> 내부 중첩질의에서 외부 테이블을 참조하면, 이를 correlated subquery라고 부른다.

- correlated subqueries 사용시
  - subquey를 외부 테이블의 각 튜플 값에 대해 evaluated되어야
  - 그래서 Time-consuming evaluation

## exists
> 인자 형태로 subquery 결과가 존재하면 참

- 정의
  - __exists r__ : r이 공집합이 아닐때 참
  - __not exists r__ : r이 공집합일때만 참
- 예시
  - Find all course numbers taught in both the Fall 2009 semester and in the Fall 2010 semester
    - ```sql
    Select s.cID
    from teaches as S
    where S.semester='Fall' and S.year=2009 and
    exists (select *
           from teaches as T
           where T.semester='Fall' and T.year=2010
           and S.cID = T.cID);```

  - not-correlated 된 subquery에 exists를 쓰는것은 무의미하다
     - ```sql
  Select distinct sID
  from student
  where exists (select cID
               from course
               whree deptName='CS');
  // 아래 문장과 동일하다
  select distinct sID from stuent;```

## for all = not exists
> __sql에서 for all은 제공하지 않으므로, not exists(...except ...) 로 표현한다__

__for all = not exists(반드시 공집합이 나오는 것)__
  - Find all student IDs and names __who have taken all courses__ offered in ‘CS’ department
    -  ```sql
    Select sID, name
    from student as S
    where not exists( (select cID
                       from course
                       where deptName='CS')
          except (select T.cID
                  from takes as T
                  where S.sID = T.sID)
   );// CS가 제공하는 강의 주 어떤건 듣고, 어떤걸 안들으면 거짓 리턴```

## unique
> 인자형식으로 표현되는 서브질의 결과에 중복성이 있는지를 검사
__unique(r)에서 만약 r이 공집합이면(즉, 질의 결과가 없으면) true__

- ⚠️ null 값을 가지는 터플은 중복으로 나와도 unique하다고 판별한다. __터플 중의 속성이 한 개라도 널 값을 가지면 동일하지 않다고 판별하므로 주의해야__
- __unique(공집합) = true__


- Find all courses that were offered __at most once__ in 2009
  - ```sql
//ver1
Select C.cID
from course as C
where unique(select T.cID
             from teaches as T
             where C.cID=T.cID and T.year=2009);
// ver2
Select C.cID
from course as C
where 1 >= (select count(T.cID)
            from teaches as T
            where C.cID=T.cID and T.year=2009);```

## from 내 subquery
- Find department name and the average salary of the professors of the department where the average salary is greater than 6900
  - ```sql
// ver 1
Select deptName, avg(salary)
from (select deptName, avg(salary) as avgSalary
      from professor
      group by deptName)
where avgSalary > 6900;
// ver 2
Select deptName, avgSalary
from (select deptName, avg(salary)
     from professor
     group by deptName) as deptAvg(deptName, avgSalary)
where avgSalary > 6900;```

- Find the maximum total salary of department across all departments
  - ```sql
// ver1
Select max(totalSalary)
from (select deptName, sum(salary)
      from professor
      group by deptName) as deptTot(deptName, totalSalary);
//ver2
Select sum(salary)
from professor
group by deptName
having sum(salary) >= all(select sum(salary)
			  from professor
              group by deptName);```

## with 절
> SQL 문장의 결과를 임시 저장

- Find the department name with the maximum budget, along with its budget
   - ```sql
//ver 1
With maxBudget(value) as
     (select max(budget)
     from department)
select deptName, budget
from department, maxBudget
where department.budget = maxBudget.value;
// ver2
Select deptName, budget
from department
where budget=(select max(budget) from department);```

- Find all departments where the total salary is greater than the average of the total salary at all departments
  - ```sql
with deptTotal(deptName, value) as
              (select deptName, sum(salary)
              from professor
              group by deptName),
    deptTotalAvg(value) as
              (select avg(value)
              from deptTotal)
select deptName
from deptTotal, deptTotalAvg
where deptTotal.value > deptTotalAvg.value;```

## scalar subquery
> __결과 테이블이 하나의 속성으로 이루어지고 동시에 하나의 튜플만을 가지면__ 서브질의가 연산 식에서 값이 반환되는 어떤 곳이라도 나타날 수 있게 한다. 이러한 서브질의를 scalar subquery라고 함

- To find department names along with the number of professors
  - ```sql
Select deptName, (select count(*)
                  from professor p1
                  where d1.deptName = p1.deptName)
from department d1;```
  - select 절 안의 deptName과 (...) 이 두 개 동등하게 scalar이기 때문에 select A, B로쓸 수 있다.
