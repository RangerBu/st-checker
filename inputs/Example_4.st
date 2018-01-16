PROGRAM Example4
	VAR_INPUT
		z : INT;
	END_VAR
	VAR_OUTPUT
		y : INT;
	END_VAR
	VAR RETAIN
		x : INT := 0;
	END_VAR

	IF z < 50 THEN
		x := f(x, 1) ;
	ELSE
		x := 50;
	END_IF;

	y := x;
	
END_PROGRAM

FUNCTION f : INT
	VAR_INPUT
		in0, in1 : INT;
	END_VAR

	f := in0 + in1;

END_FUNCTION
