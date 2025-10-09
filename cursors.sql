DECLARE
    -- Step 1: Declare the cursor
    CURSOR c_employee IS
        SELECT first_name, job_id
        FROM employees;
    
    v_first_name employees.first_name%TYPE;
    v_job_id employees.job_id%TYPE;
BEGIN
    -- Step 2: Open the cursor
    OPEN c_employee;
    
    LOOP
        -- Step 3: Fetch from the cursor
        FETCH c_employee INTO v_first_name, v_job_id;
        
        -- Exit the loop when no more rows are fetched
        EXIT WHEN c_employee%NOTFOUND;
        
        -- Process the fetched row (in this case, display the data)
        DBMS_OUTPUT.PUT_LINE('Employee Name: ' || v_first_name || ', Job ID: ' || v_job_id);
    END LOOP;
    
    -- Step 4: Close the cursor
    CLOSE c_employee;
END;
