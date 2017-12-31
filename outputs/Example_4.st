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
	ELSIF z < 100 THEN
		x := x - 2;
		IF x < 20 THEN
			x := 20;
		ELSIF x < 10 THEN
			x := 10;
		END_IF;
	ELSIF z < 200 THEN
		x := x - 3;
	ELSE
		x := 50;
	END_IF;

	IF x <= y THEN
		x := x + 1;
	END_IF;

	y := x - 1;
	flag := TRUE;

END_PROGRAM
