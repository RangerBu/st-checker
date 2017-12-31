PROGRAM Example
VAR_INPUT
	in0 : INT;
	flag : BOOL;
END_VAR
VAR
	x : INT;
END_VAR
VAR_OUTPUT
	y : INT;
END_VAR

IF flag THEN
	IF in0 < 100 THEN
		x := in0;
	ELSE
		x := 0;
	END_IF;
ELSE
	y := x;
END_IF;

END_PROGRAM
