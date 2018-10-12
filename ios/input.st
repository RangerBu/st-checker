FUNCTION increment : int
    VAR_INPUT
        in0, in1 : INT;
    END_VAR
    VAR
        test : INT := 10;
        ba : BOOL;
    END_VAR
    VAR_OUTPUT
        out : INT;
    END_VAR

    out := in0 + in1;
    increment := out;

END_FUNCTION

PROGRAM Main
VAR_INPUT
    IN, IN1 : INT;
    IN2 : INT := 10;
END_VAR
VAR_TEMP
    CNT : INT;
    F1, F2 : INT;
END_VAR
VAR_OUTPUT
    OUT : INT;
END_VAR

IF IN < 3 THEN
    OUT := 1;
ELSE
    WHILE CNT < IN DO
        OUT := increment(in0 := F1, in1 := F2, out => OUT) + 1;
        F1 := F2;
        F2 := OUT;
        CNT := CNT + 1;
    END_WHILE;
END_IF;

END_PROGRAM