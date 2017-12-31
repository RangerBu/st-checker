PROGRAM Example4
	VAR_INPUT
		z : INT;
	END_VAR
	VAR_OUTPUT
		y : INT;
	END_VAR
	VAR RETAIN
		x : INT := 0;
		flag : BOOL := FALSE;
	END_VAR

	IF z < 50 THEN
		x := x - 1;
	ELSE
		x := 50;
	END_IF;

	IF x <= y THEN
		x := x + 1;
	END_IF;

	y := x - 1;
	flag := TRUE;

END_PROGRAM
