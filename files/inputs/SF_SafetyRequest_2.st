PROGRAM SF_SafetyRequest

	VAR_INPUT
		Activate : BOOL;
		S_OpMode : BOOL;
		S_Acknowledge : BOOL;
		MonitoringTime : INT;
		Reset : BOOL;
		ed_reset : BOOL;
	END_VAR

	VAR_OUTPUT
		Ready : BOOL;
		S_SafetyActive : BOOL;
		S_SafetyRequest : BOOL;
		Error : BOOL;
		DiagCode : INT;
	END_VAR

	VAR
		timer : INT := 0;
	END_VAR

	IF NOT Activate THEN
		DiagCode := 0;
	ELSE

		timer := timer + 10000;

		IF DiagCode = 0 THEN
			IF Activate THEN
				DiagCode := 2;
			END_IF;
		ELSIF DiagCode = 1 THEN
			IF NOT S_Acknowledge THEN
				DiagCode := 7;
			ELSIF S_OpMode THEN
				DiagCode := 6;
			END_IF;
		ELSIF DiagCode = 2 THEN
			IF ed_reset THEN
				IF NOT S_Acknowledge THEN
					DiagCode := 3;
				END_IF;
				IF S_Acknowledge THEN
					DiagCode := 6;
				END_IF;
			END_IF;
		ELSIF DiagCode = 3 THEN
			IF NOT S_OpMode THEN
				DiagCode := 4;
				timer := 0;
			ELSIF S_Acknowledge THEN
				DiagCode := 6;
			END_IF;
		ELSIF DiagCode = 4 THEN
			IF timer = MonitoringTime THEN
				DiagCode := 8;
			ELSIF S_OpMode THEN
				DiagCode := 6;
			ELSIF S_Acknowledge THEN
				DiagCode := 1;
			END_IF;
		ELSIF DiagCode = 5 THEN
			IF S_OpMode THEN
				DiagCode := 6;
			END_IF;
		ELSIF DiagCode = 6 THEN
			IF NOT S_Acknowledge THEN
				DiagCode := 3;
			ELSIF NOT S_OpMode THEN
				DiagCode := 4;
				timer := 0;
			END_IF;
		ELSIF DiagCode = 7 THEN
			IF Reset THEN
				IF NOT ed_reset THEN
					DiagCode := 9;
				END_IF;
			ELSIF ed_reset THEN
				DiagCode := 5;
			END_IF;
		ELSIF DiagCode = 8 THEN
			IF Reset THEN
				IF NOT ed_reset THEN
					DiagCode := 10;
				END_IF;
			ELSIF ed_reset THEN
				DiagCode := 5;
			END_IF;
		ELSIF DiagCode = 9 THEN
			IF NOT Reset THEN
				DiagCode := 7;
			END_IF;
		ELSIF DiagCode = 10 THEN
			IF NOT Reset THEN
				DiagCode := 8;
			END_IF;
		END_IF;
	END_IF;

	IF DiagCode = 0 THEN
		Ready := FALSE;
		S_SafetyActive := FALSE;
		S_SafetyRequest := FALSE;
		Error := FALSE;
	ELSIF DiagCode = 1 THEN
		Ready := TRUE;
		S_SafetyActive := TRUE;
		S_SafetyRequest := FALSE;
		Error := FALSE;
	ELSIF DiagCode = 2 THEN
		Ready := TRUE;
		S_SafetyActive := FALSE;
		S_SafetyRequest := FALSE;
		Error := FALSE;
	ELSIF DiagCode = 3 THEN
		Ready := TRUE;
		S_SafetyActive := FALSE;
		S_SafetyRequest := TRUE;
		Error := FALSE;
	ELSIF DiagCode = 4 THEN
		Ready := TRUE;
		S_SafetyActive := FALSE;
		S_SafetyRequest := FALSE;
		Error := FALSE;
	ELSIF DiagCode = 5 THEN
		Ready := TRUE;
		S_SafetyActive := FALSE;
		S_SafetyRequest := FALSE;
		Error := FALSE;
	ELSIF DiagCode = 6 THEN
		Ready := TRUE;
		S_SafetyActive := FALSE;
		S_SafetyRequest := TRUE;
		Error := FALSE;
	ELSIF DiagCode = 7 THEN
		Ready := TRUE;
		S_SafetyActive := FALSE;
		S_SafetyRequest := FALSE;
		Error := TRUE;
	ELSIF DiagCode = 8 THEN
		Ready := TRUE;
		S_SafetyActive := FALSE;
		S_SafetyRequest := FALSE;
		Error := TRUE;
	ELSIF DiagCode = 9 THEN
		Ready := TRUE;
		S_SafetyActive := FALSE;
		S_SafetyRequest := FALSE;
		Error := TRUE;
	ELSIF DiagCode = 10 THEN
		Ready := TRUE;
		S_SafetyActive := FALSE;
		S_SafetyRequest := FALSE;
		Error := TRUE;
	END_IF;

END_PROGRAM