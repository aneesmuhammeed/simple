CREATE OR REPLACE FUNCTION reverse_number(n IN NUMBER)
RETURN NUMBER
IS
    rev NUMBER := 0;
    digit NUMBER;
    temp NUMBER := n;
BEGIN
    IF n < 0 THEN
        RETURN NULL;  -- Invalid input for negative numbers
    END IF;

    WHILE temp > 0 LOOP
        digit := MOD(temp, 10);
        rev := rev * 10 + digit;
        temp := TRUNC(temp / 10);
    END LOOP;

    RETURN rev;
END;
/


--exec
DECLARE
    num NUMBER := 12345;
    reversed NUMBER;
BEGIN
    reversed := reverse_number(num);
    DBMS_OUTPUT.PUT_LINE('The reverse of ' || num || ' is ' || reversed);
END;
/