PROGRAM Example
VAR_INPUT
	in0, in1, in2: INT;
	flag: BOOL;
END_VAR
VAR_OUTPUT
	out: INT;
END_VAR
VAR RETAIN
	y: INT;
END_VAR

IF flag THEN
	IF(in0+in1+in2 < 100) THEN
		y := in0;
	ELSE
		y := 0;
	END_IF;
ELSE
	out := y;
END_IF;

END_PROGRAM
