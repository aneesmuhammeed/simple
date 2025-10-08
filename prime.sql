DECLARE
    n NUMBER := &n;
    i NUMBER := 2;
    flag NUMBER := 0;
BEGIN
    IF n <= 1 THEN
        DBMS_OUTPUT.PUT_LINE(n || ' is not a prime number');
    ELSE
        WHILE i <= n / 2 LOOP
            IF MOD(n, i) = 0 THEN
                flag := 1;
                EXIT;
            END IF;
            i := i + 1;
        END LOOP;

        IF flag = 0 THEN
            DBMS_OUTPUT.PUT_LINE(n || ' is a prime number');
        ELSE
            DBMS_OUTPUT.PUT_LINE(n || ' is not a prime number');
        END IF;
    END IF;
END;
/
