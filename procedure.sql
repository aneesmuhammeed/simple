
CREATE OR REPLACE PROCEDURE add_employee (
    p_emp_id IN employees.emp_id%TYPE,
    p_first_name IN employees.first_name%TYPE,
    p_last_name IN employees.last_name%TYPE,
    p_email IN employees.email%TYPE
)
IS
BEGIN
    INSERT INTO employees (emp_id, first_name, last_name, email)
    VALUES (p_emp_id, p_first_name, p_last_name, p_email);
    
    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
        RAISE;
END add_employee;
