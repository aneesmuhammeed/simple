DECLARE
    n NUMBER := &n;       -- user input
    rem NUMBER;
    sum_of_digits NUMBER := 0;
BEGIN
    DBMS_OUTPUT.PUT_LINE('Original number: ' || n);

    WHILE n > 0 LOOP
        rem := MOD(n, 10);             -- extract last digit
        sum_of_digits := sum_of_digits + rem;
        n := TRUNC(n / 10);            -- remove last digit
    END LOOP;

    DBMS_OUTPUT.PUT_LINE('Sum of digits = ' || sum_of_digits);
END;
/
