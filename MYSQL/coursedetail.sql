CREATE 
    ALGORITHM = UNDEFINED 
    DEFINER = `root`@`localhost` 
    SQL SECURITY DEFINER
VIEW `coursedetail` AS
    SELECT 
        `lecture`.`UoSCode` AS `UoSCode`,
        `lecture`.`Semester` AS `Semester`,
        `lecture`.`Year` AS `Year`,
        `lecture`.`ClassTime` AS `ClassTime`,
        `lecture`.`ClassroomId` AS `ClassroomId`,
        `uosoffering`.`Textbook` AS `Textbook`,
        `uosoffering`.`Enrollment` AS `Enrollment`,
        `uosoffering`.`MaxEnrollment` AS `MaxEnrollment`,
        `uosoffering`.`InstructorId` AS `InstructorId`,
        `unitofstudy`.`DeptId` AS `DeptId`,
        `unitofstudy`.`UoSName` AS `UoSName`,
        `unitofstudy`.`Credits` AS `Credits`
    FROM
        ((`lecture`
        JOIN `uosoffering` ON (((`lecture`.`UoSCode` = `uosoffering`.`UoSCode`)
            AND (`lecture`.`Semester` = `uosoffering`.`Semester`)
            AND (`lecture`.`Year` = `uosoffering`.`Year`))))
        JOIN `unitofstudy` ON ((`lecture`.`UoSCode` = `unitofstudy`.`UoSCode`)))