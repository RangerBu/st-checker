PROGRAM SF_EmergencyStop

	VAR_INPUT
		Activate : BOOL;
		S_EStopIn : BOOL;
		S_StartReset : BOOL;
		S_AutoReset : BOOL;
		Reset : BOOL;
		ed : BOOL;
	END_VAR

	VAR_OUTPUT
		Reday : BOOL;
		S_EStopOut : BOOL;
		Error : BOOL;
		DiagCode : INT;
	END_VAR

	IF NOT Activate THEN
		DiagCode := 1;
	END_IF;

	IF DiagCode = 1 THEN
		IF Activate THEN
			DiagCode := 2;
		END_IF;
	ELSIF DiagCode = 2 THEN
		IF NOT S_StartReset THEN
			DiagCode := 3;
		ELSIF S_StartReset THEN
		    IF NOT S_EStopIn THEN
				DiagCode := 7;
			END_IF;
		ELSIF S_EStopIn THEN
			IF S_StartReset THEN
				DiagCode := 5;
			END_IF;
		END_IF;
	ELSIF DiagCode = 3 THEN
		IF S_EStopIn THEN
			DiagCode := 4;
		END_IF;
	ELSIF DiagCode = 4 THEN
		IF Reset THEN
			IF NOT ed THEN
				DiagCode := 6;
			END_IF;
		END_IF;
	ELSIF DiagCode = 5 THEN
		IF NOT S_EStopIn THEN
			DiagCode := 7;
		END_IF;
	ELSIF DiagCode = 6 THEN
		IF NOT Reset THEN
			DiagCode := 4;
		END_IF;
	ELSIF DiagCode = 7 THEN
		IF S_EStopIn THEN
			IF NOT S_AutoReset THEN
				DiagCode := 8;
			END_IF;
		ELSIF S_EStopIn THEN
			IF S_AutoReset THEN
				DiagCode := 5;
			END_IF;
		END_IF;
	ELSIF DiagCode = 8 THEN
		IF Reset THEN
			IF NOT ed THEN
				DiagCode := 9;
			END_IF;
		ELSIF NOT S_EStopIn THEN
			DiagCode := 7;
		ELSIF ed THEN
			DiagCode := 5;
		ELSIF S_AutoReset THEN
			DiagCode := 5;
		END_IF;
	ELSIF DiagCode = 9 THEN
		IF NOT Reset THEN
			DiagCode := 8;
		END_IF;
	END_IF;

	IF DiagCode = 1 THEN
		Reday := FALSE;
		S_EStopOut := FALSE;
		Error := FALSE;
	ELSIF DiagCode = 2 THEN
		Reday := TRUE;
		S_EStopOut := FALSE;
		Error := FALSE;
	ELSIF DiagCode = 3 THEN
		Reday := TRUE;
		S_EStopOut := FALSE;
		Error := FALSE;
	ELSIF DiagCode = 4 THEN
		Reday := TRUE;
		S_EStopOut := FALSE;
		Error := FALSE;
	ELSIF DiagCode = 5 THEN
		Reday := TRUE;
		S_EStopOut := TRUE;
		Error := FALSE;
	ELSIF DiagCode = 6 THEN
		Reday := TRUE;
		S_EStopOut := FALSE;
		Error := TRUE;
	ELSIF DiagCode = 7 THEN
		Reday := TRUE;
		S_EStopOut := FALSE;
		Error := FALSE;
	ELSIF DiagCode = 8 THEN
		Reday := TRUE;
		S_EStopOut := FALSE;
		Error := FALSE;
	ELSIF DiagCode = 9 THEN
		Reday := TRUE;
		S_EStopOut := FALSE;
		Error := TRUE;
	END_IF;

END_PROGRAM