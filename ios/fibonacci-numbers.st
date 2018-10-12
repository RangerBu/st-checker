FUNCTION AddTwo : INT
  VAR_INPUT
    In0 : INT;
    In1 : INT;
  END_VAR


  AddTwo := In0 + In1;
END_FUNCTION

PROGRAM program0
  VAR_INPUT
    N : INT := 5;
  END_VAR
  VAR_OUTPUT
    O : INT := 1;
  END_VAR
  VAR
    F1 : INT := 1;
    F2 : INT := 1;
    CNT : INT := 2;
  END_VAR

  IF N <= CNT THEN
    O := 1;
  ELSE
    WHILE CNT < N DO
      O := AddTwo(In0:=F1, In1:=F2);
      F1 := F2;
      F2 := O;
      CNT := CNT + 1;
    END_WHILE;
  END_IF;
END_PROGRAM