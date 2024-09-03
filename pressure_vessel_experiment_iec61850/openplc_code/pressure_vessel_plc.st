PROGRAM boiler
  VAR
    raw_pressure AT %MW0 : INT := 3100;
    setpoint AT %MW1 : INT := 3000;
    efflux AT %QX0.0 : BOOL;
  END_VAR
  VAR
    _TMP_GT1_OUT : BOOL;
  END_VAR

  _TMP_GT1_OUT := GT(raw_pressure, setpoint);
  efflux := _TMP_GT1_OUT;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : boiler;
  END_RESOURCE
END_CONFIGURATION

