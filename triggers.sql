--row-level-trigger
CREATE OR REPLACE TRIGGER salary_change_trigger
AFTER UPDATE OF salary ON employees
FOR EACH ROW
BEGIN
INSERT INTO salary_log (emp_id, old_salary, new_salary, change_date)
VALUES (:OLD.emp_id, :OLD.salary, :NEW.salary, SYSDATE);
END;

--statement trigger
CREATE OR REPLACE TRIGGER employees_audit_trigger
AFTER INSERT OR UPDATE OR DELETE ON employees
BEGIN
    INSERT INTO audit_log (table_name, action, action_date)
    VALUES ('employees', 'DML operation', SYSDATE);
END;
