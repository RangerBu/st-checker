FUNCTION_BLOCK MaxMin
VAR_INPUT
	T_Inputs : ARRAY [1..5] OF REAL;
END_VAR
VAR
	i: INT:=1;
END_VAR
VAR_OUTPUT
	MAXnum : REAL := 0.0;
	MINnum : REAL := 2000.0;
END_VAR

WHILE i<=5 DO
	IF T_Inputs[i] > MAXNum
		THEN MAXnum := T_Inputs[i];
	END_IF;
	IF T_Inputs[i] < MinNum
		THEN Minnum := T_Inputs[i];
	END_IF;
	i := i+1;
END_WHILE;

END_FUNCTION_BLOCK

PROGRAM Main
VAR
	PP : MaxMin;
END_VAR
VAR_OUTPUT
	MAXnum : REAL;
	MINnum : REAL;
END_VAR
VAR_INPUT
	T_Inputs1 : ARRAY [1..5] OF REAL;
END_VAR

PP(T_Inputs:=T_Inputs1);
MAXnum := PP.MAXnum;
MINnum := PP.MINnum;

END_PROGRAM