CREATE DEFINER=`root`@`localhost` PROCEDURE `deletecourses`(IN username int(11), IN dropnum char(20), IN dropyear int, IN dropquarter char(20))
BEGIN
DELETE FROM transcript 
WHERE transcript.StudId=username and transcript.UoSCode=dropnum
and transcript.Grade is null and transcript.year=dropyear and transcript.Semester=dropquarter;

UPDATE uosoffering
set uosoffering.Enrollment=uosoffering.Enrollment-1
where uosoffering.Uoscode=dropnum and  uosoffering.Year=dropyear and uosoffering.Semester=dropquarter;
END