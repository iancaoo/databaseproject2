CREATE DEFINER=`root`@`localhost` PROCEDURE `coursecheck_correctinput`(in username varchar(20), in CourseNum char(20), in eSemester Char(5), in eyear char(20), out notif varchar(150), out output int)
BEGIN

declare t_error int default 0;
#declare continue handler for sqlexception set t_error=1;
START transaction;
/* satisfy pre */
IF EXISTS(
SELECT R.UoSCode
from requiredpre_enroll R, transcript T
where T.StudId = username AND R.UoSCode = CourseNum AND R.Year = eyear AND R.Semester = eSemester AND R.PrereqUoSCode = T.UoSCode AND (T.Grade = "CR" OR T. Grade = "P" OR T.Grade = "D") AND R.Enrollment < R.MaxEnrollment)
THEN
UPDATE uosoffering
SET Enrollment = Enrollment + 1
WHERE UoSCode = CourseNum;
INSERT INTO transcript
VALUES(username, CourseNum, eSemester, eyear, NULL);
SET notif = "E";
SET output = 1;


/* satisfy pre but number of enroll*/
ELSEIF EXISTS(
SELECT R.UoSCode
from requiredpre_enroll R, transcript T
where T.StudId = username AND R.UoSCode = CourseNum AND R.Year = eyear AND R.Semester = eSemester AND R.PrereqUoSCode = T.UoSCode AND (T.Grade = "CR" OR T. Grade = "P" OR T.Grade = "D") AND (R.Enrollment > R.MaxEnrollment OR R.Enrollment = R.MaxEnrollment))
THEN
SET notif = "Enroll_failed.The_course_is_beyond_maxenrollment!!!";
SET output = 0;

/* Not satisfy pre */
ELSEIF EXISTS
(
SELECT R.UoSCode
from requiredpre_enroll R, transcript T
where T.StudId = username AND (R.UoSCode = CourseNum AND R.Year = eyear AND R.Semester = eSemester AND R.PrereqUoSCode = T.UoSCode AND (T.Grade is null OR T.Grade = "F"))
)
THEN
select R.PrereqUoSCode into notif
from requiredpre_enroll R, transcript T
where T.StudId = username AND (R.UoSCode = CourseNum AND R.PrereqUoSCode = T.UoSCode AND (T.Grade is null OR T.Grade = "F"));
SET output = 0;
ELSEIF EXISTS
(
select R.UoSCode
from requiredpre_enroll R, transcript T
where T.StudId = username AND R.UoSCode = CourseNum AND R.Year = eyear AND R.Semester = eSemester AND R.PrereqUoSCode not in 
(SELECT T.UoSCode
FROM transcript T)
group by R.PrereqUoSCode 
)
THEN
select R.PrereqUoSCode into notif
from requiredpre_enroll R, transcript T
where T.StudId = username AND R.UoSCode = CourseNum AND R.PrereqUoSCode not in 
(SELECT T.UoSCode
FROM transcript T)
group by R.PrereqUoSCode;
SET output = 0;


/* No prereq */
ELSEIF EXISTS
(SELECT R.UoSCode
from requiredpre_enroll R, transcript T
where T.StudId = username AND R.UoSCode <> CourseNum AND CourseNum 
IN
(SELECT U.UoSCode
FROM uosoffering U
where U.UoSCode = CourseNum and U.Enrollment < U.MaxEnrollment 
))
THEN
UPDATE uosoffering
SET Enrollment = Enrollment + 1
WHERE UoSCode = CourseNum;
INSERT INTO transcript
VALUES(Username, CourseNum, eSemester, eyear, NULL);
SET notif = "En";
SET output = 1;
/* No prereq but beyond enrollment*/
ELSEIF EXISTS
(SELECT R.UoSCode
from requiredpre_enroll R, transcript T
where T.StudId = username AND R.UoSCode <> CourseNum AND CourseNum 
IN
(SELECT U.UoSCode
FROM uosoffering U
where U.UoSCode = CourseNum AND (U.enrollment > U.MaxEnrollment OR U.Enrollment = U.MaxEnrollment)
))
THEN
SET notif = "Enroll_failed.The_course_is_beyond_maxenrollment!!!";
SET output = 0;
ELSEIF NOT EXISTS(
SELECT L.UoSCode
from lecture L
where L.UoSCode = CourseNum
)
THEN
SET notif = "2";
SET output = 2;

END if;

if (t_error=1) 
then begin
set notif='ERROR, rollback';
rollback;
end;
else begin 
commit;
end;
end if;
 

END