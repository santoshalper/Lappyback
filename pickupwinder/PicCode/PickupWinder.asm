
_PrintAString:

;PickupWinder.c,9 :: 		void PrintAString(char string[]) {
;PickupWinder.c,11 :: 		for(k=0;string[k]!=0;k++) // Recall: String is an array terminated by zero
	CLRF       PrintAString_k_L0+0
	CLRF       PrintAString_k_L0+1
L_PrintAString0:
	MOVF       PrintAString_k_L0+0, 0
	ADDWF      FARG_PrintAString_string+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      0
	BTFSC      STATUS+0, 2
	GOTO       L_PrintAString1
;PickupWinder.c,12 :: 		Uart1_Write(string[k]);
	MOVF       PrintAString_k_L0+0, 0
	ADDWF      FARG_PrintAString_string+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;PickupWinder.c,11 :: 		for(k=0;string[k]!=0;k++) // Recall: String is an array terminated by zero
	INCF       PrintAString_k_L0+0, 1
	BTFSC      STATUS+0, 2
	INCF       PrintAString_k_L0+1, 1
;PickupWinder.c,12 :: 		Uart1_Write(string[k]);
	GOTO       L_PrintAString0
L_PrintAString1:
;PickupWinder.c,13 :: 		}
L_end_PrintAString:
	RETURN
; end of _PrintAString

_main:

;PickupWinder.c,16 :: 		void main() {
;PickupWinder.c,17 :: 		TRISA = 0X14;
	MOVLW      20
	MOVWF      TRISA+0
;PickupWinder.c,18 :: 		TRISB = 0x00;
	CLRF       TRISB+0
;PickupWinder.c,19 :: 		TRISC = 0x00;
	CLRF       TRISC+0
;PickupWinder.c,20 :: 		PORTC = 0x00;
	CLRF       PORTC+0
;PickupWinder.c,21 :: 		ANSEL = 0x04;
	MOVLW      4
	MOVWF      ANSEL+0
;PickupWinder.c,22 :: 		C1ON_bit = 0;               // Disable comparators
	BCF        C1ON_bit+0, 7
;PickupWinder.c,23 :: 		C2ON_bit = 0;
	BCF        C2ON_bit+0, 7
;PickupWinder.c,24 :: 		Uart1_Init(9600);
	MOVLW      25
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;PickupWinder.c,25 :: 		PWM1_Init(5000);
	BCF        T2CON+0, 0
	BCF        T2CON+0, 1
	MOVLW      199
	MOVWF      PR2+0
	CALL       _PWM1_Init+0
;PickupWinder.c,26 :: 		INTCON |= 0x90;
	MOVLW      144
	IORWF      INTCON+0, 1
;PickupWinder.c,27 :: 		OPTION_REG |= 0x40;
	BSF        OPTION_REG+0, 6
;PickupWinder.c,28 :: 		PWM1_Start();
	CALL       _PWM1_Start+0
;PickupWinder.c,29 :: 		PWM1_Set_Duty(duty);
	MOVF       _duty+0, 0
	MOVWF      FARG_PWM1_Set_Duty_new_duty+0
	CALL       _PWM1_Set_Duty+0
;PickupWinder.c,30 :: 		while(1) {
L_main3:
;PickupWinder.c,31 :: 		foot = ADC_Read(3)/3;
	MOVLW      3
	MOVWF      FARG_ADC_Read_channel+0
	CALL       _ADC_Read+0
	MOVLW      3
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Div_16x16_U+0
	MOVF       R0+0, 0
	MOVWF      _foot+0
	MOVF       R0+1, 0
	MOVWF      _foot+1
;PickupWinder.c,32 :: 		if(counter < 50) {
	MOVLW      0
	SUBWF      _counter+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main10
	MOVLW      50
	SUBWF      _counter+0, 0
L__main10:
	BTFSC      STATUS+0, 0
	GOTO       L_main5
;PickupWinder.c,33 :: 		duty = (short)foot;
	MOVF       _foot+0, 0
	MOVWF      _duty+0
;PickupWinder.c,34 :: 		if(duty<60) duty = 0;
	MOVLW      60
	SUBWF      _foot+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_main6
	CLRF       _duty+0
L_main6:
;PickupWinder.c,35 :: 		PWM1_Set_Duty(duty);
	MOVF       _duty+0, 0
	MOVWF      FARG_PWM1_Set_Duty_new_duty+0
	CALL       _PWM1_Set_Duty+0
;PickupWinder.c,36 :: 		}
	GOTO       L_main7
L_main5:
;PickupWinder.c,37 :: 		else PWM1_Set_Duty(0);
	CLRF       FARG_PWM1_Set_Duty_new_duty+0
	CALL       _PWM1_Set_Duty+0
L_main7:
;PickupWinder.c,38 :: 		PrintAstring(script);
	MOVLW      _script+0
	MOVWF      FARG_PrintAString_string+0
	CALL       _PrintAString+0
;PickupWinder.c,39 :: 		InttoStr(foot,temp);
	MOVF       _foot+0, 0
	MOVWF      FARG_IntToStr_input+0
	MOVF       _foot+1, 0
	MOVWF      FARG_IntToStr_input+1
	MOVLW      _temp+0
	MOVWF      FARG_IntToStr_output+0
	CALL       _IntToStr+0
;PickupWinder.c,40 :: 		PrintAString(temp);
	MOVLW      _temp+0
	MOVWF      FARG_PrintAString_string+0
	CALL       _PrintAString+0
;PickupWinder.c,41 :: 		PrintAstring(script2);
	MOVLW      _script2+0
	MOVWF      FARG_PrintAString_string+0
	CALL       _PrintAString+0
;PickupWinder.c,42 :: 		InttoStr(counter,temp);
	MOVF       _counter+0, 0
	MOVWF      FARG_IntToStr_input+0
	MOVF       _counter+1, 0
	MOVWF      FARG_IntToStr_input+1
	MOVLW      _temp+0
	MOVWF      FARG_IntToStr_output+0
	CALL       _IntToStr+0
;PickupWinder.c,43 :: 		PrintAString(temp);
	MOVLW      _temp+0
	MOVWF      FARG_PrintAString_string+0
	CALL       _PrintAString+0
;PickupWinder.c,44 :: 		PrintAstring(crlf);
	MOVLW      _crlf+0
	MOVWF      FARG_PrintAString_string+0
	CALL       _PrintAString+0
;PickupWinder.c,45 :: 		}
	GOTO       L_main3
;PickupWinder.c,46 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_interrupt:
	MOVWF      R15+0
	SWAPF      STATUS+0, 0
	CLRF       STATUS+0
	MOVWF      ___saveSTATUS+0
	MOVF       PCLATH+0, 0
	MOVWF      ___savePCLATH+0
	CLRF       PCLATH+0

;PickupWinder.c,47 :: 		void interrupt() {
;PickupWinder.c,48 :: 		counter ++;
	INCF       _counter+0, 1
	BTFSC      STATUS+0, 2
	INCF       _counter+1, 1
;PickupWinder.c,49 :: 		INTCON.INTF = 0;
	BCF        INTCON+0, 1
;PickupWinder.c,50 :: 		}
L_end_interrupt:
L__interrupt12:
	MOVF       ___savePCLATH+0, 0
	MOVWF      PCLATH+0
	SWAPF      ___saveSTATUS+0, 0
	MOVWF      STATUS+0
	SWAPF      R15+0, 1
	SWAPF      R15+0, 0
	RETFIE
; end of _interrupt
