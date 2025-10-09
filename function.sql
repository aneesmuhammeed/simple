CREATE OR REPLACE FUNCTION calculate_square (number IN NUMBER)
RETURN NUMBER
IS
   result NUMBER;
BEGIN
   result := number * number;
   RETURN result;
END;
/

--executing
DECLARE
   num NUMBER := 5;
   square NUMBER;
BEGIN
   square := calculate_square(num);
   DBMS_OUTPUT.PUT_LINE('The square of ' || num || ' is ' || square);
END;
/
