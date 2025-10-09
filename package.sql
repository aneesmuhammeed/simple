CREATE OR REPLACE PACKAGE simple_pkg IS
  -- Public procedure declaration
  PROCEDURE greet_user(p_name IN VARCHAR2);

  -- Public function declaration
  FUNCTION square_number(p_number IN NUMBER) RETURN NUMBER;
END simple_pkg;
/
***************************
CREATE OR REPLACE PACKAGE BODY simple_pkg IS
  -- Implement the greet_user procedure
  PROCEDURE greet_user(p_name IN VARCHAR2) IS
  BEGIN
    DBMS_OUTPUT.PUT_LINE('Hello, ' || p_name || '!');
  END greet_user;

  -- Implement the square_number function
  FUNCTION square_number(p_number IN NUMBER) RETURN NUMBER IS
  BEGIN
    RETURN p_number * p_number;
  END square_number;
END simple_pkg;
/
***************************
BEGIN
  -- Call the greet_user procedure
  simple_pkg.greet_user('Alice');

  -- Call the square_number function
  DECLARE
    v_number NUMBER := 5;
    v_square NUMBER;
  BEGIN
    v_square := simple_pkg.square_number(v_number);
    DBMS_OUTPUT.PUT_LINE('The square of ' || v_number || ' is ' || v_square);
  END;
END;
/
