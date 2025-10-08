DECLARE
    num1 NUMBER := &num1;
    num2 NUMBER := &num2;
    num3 NUMBER := &num3;
    largest NUMBER;
BEGIN
    IF num1 >= num2 AND num1 >= num3 THEN
        largest := num1;
    ELSIF num2 >= num1 AND num2 >= num3 THEN
        largest := num2;
    ELSE
        largest := num3;
    END IF;

    DBMS_OUTPUT.PUT_LINE('The largest number is: ' || largest);
END;
/
