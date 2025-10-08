CREATE TABLE Bill (
    cust_no NUMBER PRIMARY KEY,
    units_consumed NUMBER,
    Amount NUMBER
);



--new file a.sql
CREATE OR REPLACE FUNCTION calc_bill (
    p_cust_no IN NUMBER,
    p_units IN NUMBER
) RETURN NUMBER IS
    v_amount NUMBER;
BEGIN
    IF p_units <= 100 THEN
        v_amount := p_units * 1.5;
    ELSIF p_units <= 300 THEN
        v_amount := 100 * 1.5 + (p_units - 100) * 2.5;
    ELSE
        v_amount := 100 * 1.5 + 200 * 2.5 + (p_units - 300) * 4;
    END IF;

    INSERT INTO Bill (cust_no, units_consumed, Amount)
    VALUES (p_cust_no, p_units, v_amount);

    RETURN v_amount;
END;
/


--testing
SET SERVEROUTPUT ON;

BEGIN
    DBMS_OUTPUT.PUT_LINE('Bill Amount: ' || calc_bill(1001, 350));
END;
/



