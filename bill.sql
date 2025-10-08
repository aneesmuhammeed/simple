CREATE TABLE Bill (
    cust_no INT PRIMARY KEY,
    units_consumed INT,
    amount FLOAT
);

--next file
CREATE OR REPLACE FUNCTION calc_bill (
    p_cust_no IN INT,
    p_units IN INT
) RETURN FLOAT IS
    v_amount FLOAT;
BEGIN
    IF p_units <= 100 THEN
        v_amount := p_units * 1.5;
    ELSIF p_units <= 300 THEN
        v_amount := (100 * 1.5) + ((p_units - 100) * 2.5);
    ELSE
        v_amount := (100 * 1.5) + (200 * 2.5) + ((p_units - 300) * 4);
    END IF;

    INSERT INTO Bill (cust_no, units_consumed, amount)
    VALUES (p_cust_no, p_units, v_amount);

    RETURN v_amount;
END;
/


--next  file
BEGIN
    DBMS_OUTPUT.PUT_LINE('Bill Amount: ' || calc_bill(101, 350));
END;
/


