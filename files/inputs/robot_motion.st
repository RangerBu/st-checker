PROGRAM robot_motion
	VAR_INPUT
		dir : INT;
		sensorB : BOOL;
	END_VAR

	VAR_OUTPUT
		needM : INT;
		motorB : BOOL;
		pick : BOOL;
		put : BOOL;
	END_VAR

	VAR
		currP : INT;
		numB : INT := 0;
	END_VAR

	IF dir = 1 THEN
		currP := currP + 5000;
	ELSIF dir = -1 THEN
		currP := currP - 5000;
	ELSE
		needM := 10 - numB;
	END_IF;

	IF currP = 500000 THEN
		pick := TRUE;
	ELSIF currP = -500000 THEN
		put := TRUE;
	END_IF;

	IF sensorB THEN
		numB := numB + 1;
		IF numB = 10 THEN
			motorB := TRUE;
			numB := 0;
		ELSE
			motorB := FALSE;
		END_IF;
	END_IF;
END_PROGRAM