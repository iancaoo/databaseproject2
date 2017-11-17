CREATE DEFINER=`root`@`localhost` PROCEDURE `dropcourses`(in username int(11))
BEGIN
START transaction;
(SELECT distinct t.UosCode, t.Semester, t.Year 
FROM transcript t
WHERE t.Studid = username and t.Grade is NULL);
END