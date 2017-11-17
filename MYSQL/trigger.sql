set @status = 'done';
DROP TRIGGER IF EXISTS dropdone;
delimiter //
CREATE TRIGGER dropdone AFTER UPDATE ON uosoffering
FOR EACH ROW
BEGIN
 SET @status = 'done';
 IF (NEW.Enrollment<(0.5*NEW.MAXEnrollment)) THEN
 SET @status = 'below';
    end if;
end;
//