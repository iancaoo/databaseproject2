CREATE 
    ALGORITHM = UNDEFINED 
    DEFINER = `root`@`localhost` 
    SQL SECURITY DEFINER
VIEW `requiredpre_enroll` AS
    SELECT 
        `U`.`UoSCode` AS `UoSCode`,
        `U`.`Year` AS `Year`,
        `U`.`Semester` AS `Semester`,
        `R`.`PrereqUoSCode` AS `PrereqUoSCode`,
        `U`.`Enrollment` AS `Enrollment`,
        `U`.`MaxEnrollment` AS `MaxEnrollment`
    FROM
        (`uosoffering` `U`
        JOIN `requires` `R` ON ((`U`.`UoSCode` = `R`.`UoSCode`)))