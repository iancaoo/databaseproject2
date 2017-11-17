CREATE DEFINER=`root`@`localhost` PROCEDURE `rightwithdraw`(IN username char(10), IN dropnum char(20), IN dropyear char(10), IN dropquarter char(20))
BEGIN
(SELECT T.UoSCode
FROM transcript t
WHERE  t.Studid = username and t.UoSCode = dropnum and t.Year = dropyear and t.Semester = dropquarter and t.Grade is Null);
END