PROGRAM Example1
	VAR_INPUT
 		Activate : BOOL;
	END_VAR
	VAR_OUTPUT
		Output : BYTE;
	END_VAR
	VAR
		Variable : INT := 10;
	END_VAR
	VAR
		Temp : INT;
	END_VAR

	Temp := 10;

	IF Activate THEN
		Output := Variable;
	ELSE
		Output := 7;
	END_IF;

	Variable := Temp;

END_PROGRAM

