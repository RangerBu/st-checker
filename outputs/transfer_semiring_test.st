PROGRAM Example

VAR_INPUT
	in0, in1 : BOOL;
END_VAR
VAR RETAIN
	x : INT;
END_VAR
VAR_OUTPUT
	y : INT;
END_VAR

IF in0 THEN
	x := 1;
ELSE
	x := 2;
END_IF;

y := x;

IF in1 THEN
	x := 3;
	x := x + 1;
END_IF;

y := x;


END_PROGRAM
