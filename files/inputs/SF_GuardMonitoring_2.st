PROGRAM SF_GuardMonitoring

	VAR_INPUT
		Activate : BOOL;
		S_GuardSwitch1 : BOOL;
		S_GuardSwitch2 : BOOL;
		DiscrepancyTime : INT;
		S_StartReset : BOOL;
		S_AutoReset : BOOL;
		Reset : BOOL;
		ed_reset : BOOL;
	END_VAR

	VAR_OUTPUT
		Ready : BOOL;
		S_GuardMonitoring : BOOL;
		Error : BOOL;
		Diagcode : INT;
	END_VAR

	VAR
		timer : INT;
	END_VAR

	IF NOT Activate THEN
		Diagcode := 0;
	ELSE

		timer := timer + 10000;

		IF Diagcode = 0 THEN
			IF Activate THEN
				Diagcode := 1;
			END_IF;
		ELSIF Diagcode = 8 THEN
			IF NOT S_GuardSwitch1 THEN
				Diagcode := 2;
			ELSIF NOT S_GuardSwitch2 THEN
				Diagcode := 2;
			END_IF;
		ELSIF Diagcode = 1 THEN
			IF NOT S_GuardSwitch1 THEN
				Diagcode := 2;
			ELSIF NOT S_GuardSwitch2 THEN
				Diagcode := 2;
			ELSIF S_GuardSwitch1 THEN
				IF S_GuardSwitch2 THEN
					IF NOT S_StartReset THEN
						Diagcode := 3;
					END_IF;
				END_IF;
			ELSIF S_GuardSwitch1 THEN
				IF S_GuardSwitch2 THEN
					IF S_StartReset THEN
						Diagcode := 8;
					END_IF;
				END_IF;
			END_IF;
		ELSIF Diagcode = 2 THEN
			IF NOT S_GuardSwitch1 THEN
				IF NOT S_GuardSwitch2 THEN
					Diagcode := 6;
				END_IF;
			END_IF;
		ELSIF Diagcode = 3 THEN
			IF Reset THEN
				IF NOT ed_reset THEN
					Diagcode := 9;
				END_IF;
			ELSIF NOT S_GuardSwitch1 THEN
				Diagcode := 2;
			ELSIF NOT S_GuardSwitch2 THEN
				Diagcode := 2;
			ELSIF ed_reset THEN
				Diagcode := 8;
			END_IF;
		ELSIF Diagcode = 4 THEN
			IF timer = DiscrepancyTime THEN
				Diagcode := 11;
			ELSIF NOT S_GuardSwitch1 THEN
				Diagcode := 2;
			ELSIF S_GuardSwitch2 THEN
				Diagcode := 5;
			END_IF;
		ELSIF Diagcode = 5 THEN
			IF NOT S_GuardSwitch1 THEN
				Diagcode := 2;
			ELSIF NOT S_GuardSwitch2 THEN
				Diagcode := 2;
			ELSIF NOT S_AutoReset THEN
				Diagcode := 3;
			ELSIF S_AutoReset THEN
				Diagcode := 8;
			END_IF;
		ELSIF Diagcode = 6 THEN
			IF S_GuardSwitch1 THEN
				Diagcode := 4;
				timer := 0;
			ELSIF S_GuardSwitch2 THEN
				Diagcode := 7;
				timer := 0;
			END_IF;
		ELSIF Diagcode = 7 THEN
			IF timer = DiscrepancyTime THEN
				Diagcode := 11;
			ELSIF NOT S_GuardSwitch2 THEN
				Diagcode := 2;
			ELSIF S_GuardSwitch1 THEN
				Diagcode := 8;
			END_IF;
		ELSIF Diagcode = 9 THEN
			IF NOT Reset THEN
				Diagcode := 3;
			END_IF;
		ELSIF Diagcode = 11 THEN
			IF NOT S_GuardSwitch1 THEN
				IF NOT S_GuardSwitch2 THEN
					Diagcode := 6;
				END_IF;
			END_IF;
		ELSIF Diagcode = 11 THEN
			IF NOT S_GuardSwitch1 THEN
				IF NOT S_GuardSwitch2 THEN
					Diagcode := 6;
				END_IF;
			END_IF;
		END_IF;
	END_IF;

	IF Diagcode = 0 THEN
		Ready := FALSE;
		S_GuardMonitoring := FALSE;
		Error := FALSE;
	ELSIF Diagcode = 8 THEN
		Ready := TRUE;
		S_GuardMonitoring := TRUE;
		Error := FALSE;
	ELSIF Diagcode = 1 THEN
		Ready := TRUE;
		S_GuardMonitoring := FALSE;
		Error := FALSE;
	ELSIF Diagcode = 2 THEN
		Ready := TRUE;
		S_GuardMonitoring := FALSE;
		Error := FALSE;
	ELSIF Diagcode = 3 THEN
		Ready := TRUE;
		S_GuardMonitoring := FALSE;
		Error := FALSE;
	ELSIF Diagcode = 4 THEN
		Ready := TRUE;
		S_GuardMonitoring := FALSE;
		Error := FALSE;
	ELSIF Diagcode = 5 THEN
		Ready := TRUE;
		S_GuardMonitoring := FALSE;
		Error := FALSE;
	ELSIF Diagcode = 6 THEN
		Ready := TRUE;
		S_GuardMonitoring := FALSE;
		Error := FALSE;
	ELSIF Diagcode = 7 THEN
		Ready := TRUE;
		S_GuardMonitoring := FALSE;
		Error := FALSE;
	ELSIF Diagcode = 9 THEN
		Ready := TRUE;
		S_GuardMonitoring := FALSE;
		Error := TRUE;
	ELSIF Diagcode = 11 THEN
		Ready := TRUE;
		S_GuardMonitoring := FALSE;
		Error := TRUE;
	ELSIF Diagcode = 11 THEN
		Ready := TRUE;
		S_GuardMonitoring := FALSE;
		Error := TRUE;
	END_IF;

END_PROGRAM