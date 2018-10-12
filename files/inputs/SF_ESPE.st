FUNCTION_BLOCK SF_ESPE
	VAR_INPUT
		Activate           : BOOL;
		S_ESPE_In		   : SAFEBOOL;
		S_StartReset	   : SAFEBOOL;
		S_AutoReset		   : SAFEBOOL;
		Reset 		   	   : BOOL;
	END_VAR

	VAR_OUTPUT
		Ready 			   : BOOL;
		S_ESPE_Out		   : SAFEBOOL;
		Error			   : BOOL;
		DiagCode		   : WORD;
	END_VAR

	Var 
		tmp : R_TRIG;
	END_VAR

	tmp(CLK := Reset);

	IF NOT Activate THEN
		DiagCode := 16#0000;
	ELSE
		IF DiagCode = 16#0000 THEN

			IF Activate THEN
				DiagCode := 16#8001;
			END_IF;

		ELSIF DiagCode = 16#8001 THEN

			IF NOT S_StartReset THEN
				DiagCode := 16#8002;
			ELSIF S_StartReset AND NOT S_ESPE_In THEN
				DiagCode := 16#8004;
			ELSIF S_ESPE_In AND S_StartReset THEN
				DiagCode := 16#8000;
			END_IF;

		ELSIF DiagCode = 16#8002 THEN

			IF S_ESPE_In THEN
				DiagCode := 16#8003;
			END_IF;

		ELSIF DiagCode = 16#8003 THEN
			
			IF Reset AND NOT tmp.Q THEN
				DiagCode := 16#C001;
			ELSIF NOT S_ESPE_In THEN
				DiagCode := 16#8002;
			ELSIF tmp.Q THEN
				DiagCode := 16#8000;
			END_IF;

		ELSIF DiagCode = 16#8004 THEN

			IF S_ESPE_In AND NOT S_AutoReset THEN
				DiagCode := 16#8005;
			ELSIF S_ESPE_In AND S_AutoReset THEN
				DiagCode := 16#8000;
			END_IF;

		ELSIF DiagCode = 16#8005 THEN

			IF NOT S_ESPE_In THEN
				DiagCode := 16#C002;
			ELSIF NOT S_ESPE_In THEN
				DiagCode := 16#8004;
			ELSIF tmp.Q OR S_AutoReset THEN
				DiagCode := 16#8000;
			END_IF;

		ELSIF DiagCode = 16#C001 THEN

			IF NOT Reset THEN
				DiagCode := 16#8003;
			END_IF;

		ELSIF DiagCode = 16#C002 THEN
			
			IF NOT Reset THEN
				DiagCode := 16#8005;
			END_IF;

		ELSIF DiagCode = 16#8000 THEN

			IF NOT S_ESPE_In THEN
				DiagCode := 16#8004;
			END_IF;

		END_IF;

	END_IF;

	IF DiagCode = 16#0000 THEN

		Ready := FALSE;
		S_ESPE_Out := FALSE;
		Error := FALSE;

	ELSIF DiagCode = 16#8001 THEN

		Ready := TRUE;
		S_ESPE_Out := FALSE;
		Error := FALSE;

	ELSIF DiagCode = 16#8002 THEN

		Ready := TRUE;
		S_ESPE_Out := FALSE;
		Error := FALSE;

	ELSIF DiagCode = 16#8003 THEN

		Ready := TRUE;
		S_ESPE_Out := FALSE;
		Error := FALSE;

	ELSIF DiagCode = 16#8004 THEN

		Ready := TRUE;
		S_ESPE_Out := FALSE;
		Error := FALSE;

	ELSIF DiagCode = 16#8005 THEN

		Ready := TRUE;
		S_ESPE_Out := FALSE;
		Error := FALSE;

	ELSIF DiagCode = 16#C001 THEN

		Ready := TRUE;
		S_ESPE_Out := FALSE;
		Error := TRUE;

	ELSIF DiagCode = 16#C002 THEN

		Ready := TRUE;
		S_ESPE_Out := FALSE;
		Error := TRUE;

	ELSIF DiagCode = 16#8000 THEN

		Ready := TRUE;
		S_ESPE_Out := TRUE;
		Error := FALSE;

	END_IF;

END_FUNCTION_BLOCK

(* los 113 *)