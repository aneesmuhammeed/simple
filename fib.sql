
CREATE OR REPLACE FUNCTION factorial (n IN NUMBER)
RETURN NUMBER
IS
   result NUMBER := 1;  
BEGIN
   IF n < 0 THEN
      RETURN NULL;  
   ELSIF n = 0 OR n = 1 THEN
      RETURN 1;  
   ELSE
      FOR i IN 1..n LOOP
         result := result * i;  
      END LOOP;
      RETURN result;  
   END IF;
END;
/


   --executing
DECLARE
   num NUMBER := 5;
   fact NUMBER;
BEGIN
   fact := factorial(num);
   DBMS_OUTPUT.PUT_LINE('The factorial of ' || num || ' is ' || fact);
END;
/

--exe
DECLARE
   num NUMBER := 7;  -- Change this to get different Fibonacci numbers
   fib NUMBER;
BEGIN
   fib := fibonacci(num);
   DBMS_OUTPUT.PUT_LINE('The Fibonacci number at position ' || num || ' is ' || fib);
END;
/
