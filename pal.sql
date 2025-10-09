-- Palindrome Function
CREATE OR REPLACE FUNCTION is_palindrome(n IN NUMBER)
RETURN VARCHAR2
IS
    original NUMBER := n;
    reversed NUMBER := 0;
    digit NUMBER;
BEGIN
    IF n < 0 THEN
        RETURN 'INVALID INPUT';
    END IF;

    WHILE n > 0 LOOP
        digit := MOD(n, 10);
        reversed := reversed * 10 + digit;
        n := TRUNC(n / 10);
    END LOOP;

    IF reversed = original THEN
        RETURN 'PALINDROME';
    ELSE
        RETURN 'NOT PALINDROME';
    END IF;
END;
/


--exec
DECLARE
    num NUMBER := 121;
    result VARCHAR2(20);
BEGIN
    result := is_palindrome(num);
    DBMS_OUTPUT.PUT_LINE('The number ' || num || ' is ' || result);
END;
/