CREATE DEFINER=`root`@`localhost` PROCEDURE `enrollment`(in username varchar(20))
BEGIN

(SELECT distinct l.UoSCode, l.Semester, l.Year
FROM lecture l
WHERE 
NOT EXISTS
(SELECT t.UoSCode, t.Semester, t.Year 
FROM transcript t 
WHERE t.Studid = username and l.UoSCode = t.UoSCode and  l.Semester = t.Semester and l.Year = t.Year));

END