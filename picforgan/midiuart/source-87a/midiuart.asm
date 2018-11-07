
_midi_write:

;midiuart.c,33 :: 		void midi_write(char type, char chnl, char data1, char data2) {
;midiuart.c,34 :: 		Uart1_Write(type+chnl);
	MOVF       FARG_midi_write_chnl+0, 0
	ADDWF      FARG_midi_write_type+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;midiuart.c,35 :: 		Uart1_Write(data1&DATA_MSK);
	MOVLW      127
	ANDWF      FARG_midi_write_data1+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;midiuart.c,36 :: 		Uart1_Write(data2&DATA_MSK);
	MOVLW      127
	ANDWF      FARG_midi_write_data2+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;midiuart.c,37 :: 		}
L_end_midi_write:
	RETURN
; end of _midi_write

_main:

;midiuart.c,38 :: 		void main() {
;midiuart.c,39 :: 		TRISA = 0x00;
	CLRF       TRISA+0
;midiuart.c,40 :: 		TRISB = 0xFF;
	MOVLW      255
	MOVWF      TRISB+0
;midiuart.c,41 :: 		TRISC = 0x03;
	MOVLW      3
	MOVWF      TRISC+0
;midiuart.c,42 :: 		PORTA = 0x00;
	CLRF       PORTA+0
;midiuart.c,43 :: 		PORTC = 0x00;
	CLRF       PORTC+0
;midiuart.c,44 :: 		ANSEL = 0x00;
	CLRF       ANSEL+0
;midiuart.c,45 :: 		ANSELH = 0x00;
	CLRF       ANSELH+0
;midiuart.c,46 :: 		C1ON_bit = 0;
	BCF        C1ON_bit+0, BitPos(C1ON_bit+0)
;midiuart.c,47 :: 		C2ON_bit = 0;
	BCF        C2ON_bit+0, BitPos(C2ON_bit+0)
;midiuart.c,48 :: 		WPUB = 0x00;
	CLRF       WPUB+0
;midiuart.c,49 :: 		Uart1_Init(31250);
	MOVLW      7
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;midiuart.c,50 :: 		IOCB = 0xC0;
	MOVLW      192
	MOVWF      IOCB+0
;midiuart.c,51 :: 		INTCON |= 0x88;
	MOVLW      136
	IORWF      INTCON+0, 1
;midiuart.c,52 :: 		while(1){
L_main0:
;midiuart.c,53 :: 		col--;
	MOVLW      1
	SUBWF      _col+0, 1
	BTFSS      STATUS+0, 0
	DECF       _col+1, 1
;midiuart.c,54 :: 		PORTA = 1<<(col);
	MOVF       _col+0, 0
	MOVWF      R1+0
	MOVLW      1
	MOVWF      R0+0
	MOVF       R1+0, 0
L__main39:
	BTFSC      STATUS+0, 2
	GOTO       L__main40
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__main39
L__main40:
	MOVF       R0+0, 0
	MOVWF      PORTA+0
;midiuart.c,55 :: 		Delay_us(200);
	MOVLW      66
	MOVWF      R13+0
L_main2:
	DECFSZ     R13+0, 1
	GOTO       L_main2
	NOP
;midiuart.c,56 :: 		if(col == 0) col = COLN;
	MOVLW      0
	XORWF      _col+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main41
	MOVLW      0
	XORWF      _col+0, 0
L__main41:
	BTFSS      STATUS+0, 2
	GOTO       L_main3
	MOVLW      8
	MOVWF      _col+0
	MOVLW      0
	MOVWF      _col+1
L_main3:
;midiuart.c,57 :: 		}
	GOTO       L_main0
;midiuart.c,58 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_Interrupt:
	MOVWF      R15+0
	SWAPF      STATUS+0, 0
	CLRF       STATUS+0
	MOVWF      ___saveSTATUS+0
	MOVF       PCLATH+0, 0
	MOVWF      ___savePCLATH+0
	CLRF       PCLATH+0

;midiuart.c,59 :: 		void Interrupt() {
;midiuart.c,60 :: 		int ext,set = 0;
;midiuart.c,61 :: 		if(PORTB.b7) row = 0;
	BTFSS      PORTB+0, 7
	GOTO       L_Interrupt4
	CLRF       _row+0
	CLRF       _row+1
	GOTO       L_Interrupt5
L_Interrupt4:
;midiuart.c,62 :: 		else row = 1;
	MOVLW      1
	MOVWF      _row+0
	MOVLW      0
	MOVWF      _row+1
L_Interrupt5:
;midiuart.c,63 :: 		key = (8*row+col+1);
	MOVLW      3
	MOVWF      R2+0
	MOVF       _row+0, 0
	MOVWF      R0+0
	MOVF       _row+1, 0
	MOVWF      R0+1
	MOVF       R2+0, 0
L__Interrupt44:
	BTFSC      STATUS+0, 2
	GOTO       L__Interrupt45
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__Interrupt44
L__Interrupt45:
	MOVF       _col+0, 0
	ADDWF      R0+0, 1
	MOVF       _col+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	INCF       R0+0, 1
	BTFSC      STATUS+0, 2
	INCF       R0+1, 1
	MOVF       R0+0, 0
	MOVWF      _key+0
	MOVF       R0+1, 0
	MOVWF      _key+1
;midiuart.c,64 :: 		note = ((key-1)%12);
	MOVLW      1
	SUBWF      R0+0, 0
	MOVWF      FLOC__Interrupt+0
	MOVLW      0
	BTFSS      STATUS+0, 0
	ADDLW      1
	SUBWF      R0+1, 0
	MOVWF      FLOC__Interrupt+1
	MOVLW      12
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	MOVF       FLOC__Interrupt+0, 0
	MOVWF      R0+0
	MOVF       FLOC__Interrupt+1, 0
	MOVWF      R0+1
	CALL       _Div_16x16_S+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	MOVWF      _note+0
;midiuart.c,65 :: 		oct = ((key-1)/12 + octu);
	MOVLW      12
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	MOVF       FLOC__Interrupt+0, 0
	MOVWF      R0+0
	MOVF       FLOC__Interrupt+1, 0
	MOVWF      R0+1
	CALL       _Div_16x16_S+0
	MOVF       _octu+0, 0
	ADDWF      R0+0, 0
	MOVWF      _oct+0
;midiuart.c,66 :: 		chordtype = MAJ;
	CLRF       _chordtype+0
	CLRF       _chordtype+1
;midiuart.c,67 :: 		vel =0x60;
	MOVLW      96
	MOVWF      _vel+0
;midiuart.c,68 :: 		inv = 0;
	CLRF       _inv+0
	CLRF       _inv+1
;midiuart.c,69 :: 		if(PORTB.b0) chordtype = MIN;
	BTFSS      PORTB+0, 0
	GOTO       L_Interrupt6
	MOVLW      1
	MOVWF      _chordtype+0
	MOVLW      0
	MOVWF      _chordtype+1
	GOTO       L_Interrupt7
L_Interrupt6:
;midiuart.c,70 :: 		else if(PORTB.b1 || PORTB.b2) {
	BTFSC      PORTB+0, 1
	GOTO       L__Interrupt36
	BTFSC      PORTB+0, 2
	GOTO       L__Interrupt36
	GOTO       L_Interrupt10
L__Interrupt36:
;midiuart.c,71 :: 		inv = 1;
	MOVLW      1
	MOVWF      _inv+0
	MOVLW      0
	MOVWF      _inv+1
;midiuart.c,72 :: 		if(PORTB.b2) chordtype = MIN;
	BTFSS      PORTB+0, 2
	GOTO       L_Interrupt11
	MOVLW      1
	MOVWF      _chordtype+0
	MOVLW      0
	MOVWF      _chordtype+1
L_Interrupt11:
;midiuart.c,73 :: 		}
	GOTO       L_Interrupt12
L_Interrupt10:
;midiuart.c,74 :: 		else if(PORTB.b3 || PORTB.B4) {
	BTFSC      PORTB+0, 3
	GOTO       L__Interrupt35
	BTFSC      PORTB+0, 4
	GOTO       L__Interrupt35
	GOTO       L_Interrupt15
L__Interrupt35:
;midiuart.c,75 :: 		inv = 2;
	MOVLW      2
	MOVWF      _inv+0
	MOVLW      0
	MOVWF      _inv+1
;midiuart.c,76 :: 		if(PORTB.b4) chordtype = MIN;
	BTFSS      PORTB+0, 4
	GOTO       L_Interrupt16
	MOVLW      1
	MOVWF      _chordtype+0
	MOVLW      0
	MOVWF      _chordtype+1
L_Interrupt16:
;midiuart.c,77 :: 		}
	GOTO       L_Interrupt17
L_Interrupt15:
;midiuart.c,78 :: 		else if(PORTB.b5) chordtype = DIM;
	BTFSS      PORTB+0, 5
	GOTO       L_Interrupt18
	MOVLW      2
	MOVWF      _chordtype+0
	MOVLW      0
	MOVWF      _chordtype+1
	GOTO       L_Interrupt19
L_Interrupt18:
;midiuart.c,79 :: 		else if(PORTC.b0) chordtype = AUG;
	BTFSS      PORTC+0, 0
	GOTO       L_Interrupt20
	MOVLW      3
	MOVWF      _chordtype+0
	MOVLW      0
	MOVWF      _chordtype+1
	GOTO       L_Interrupt21
L_Interrupt20:
;midiuart.c,80 :: 		else if(PORTC.b1) chordtype = PWR;
	BTFSS      PORTC+0, 1
	GOTO       L_Interrupt22
	MOVLW      4
	MOVWF      _chordtype+0
	MOVLW      0
	MOVWF      _chordtype+1
L_Interrupt22:
L_Interrupt21:
L_Interrupt19:
L_Interrupt17:
L_Interrupt12:
L_Interrupt7:
;midiuart.c,81 :: 		triad[0] = NOTE(note,oct);
	MOVF       _oct+0, 0
	MOVWF      R0+0
	MOVLW      12
	MOVWF      R4+0
	CALL       _Mul_8X8_U+0
	MOVF       _note+0, 0
	ADDWF      R0+0, 1
	MOVLW      127
	ANDWF      R0+0, 1
	MOVF       R0+0, 0
	MOVWF      _triad+0
;midiuart.c,82 :: 		triad[1] = triad[0]+4;
	MOVLW      4
	ADDWF      R0+0, 1
	MOVF       R0+0, 0
	MOVWF      _triad+1
;midiuart.c,83 :: 		triad[2] = triad[1]+3;
	MOVLW      3
	ADDWF      R0+0, 0
	MOVWF      _triad+2
;midiuart.c,84 :: 		if(inv>0) {
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      _inv+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__Interrupt46
	MOVF       _inv+0, 0
	SUBLW      0
L__Interrupt46:
	BTFSC      STATUS+0, 0
	GOTO       L_Interrupt23
;midiuart.c,85 :: 		triad[0] += 0x0C;
	MOVLW      12
	ADDWF      _triad+0, 1
;midiuart.c,86 :: 		if(inv>1) triad[1] += 0x0C;
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      _inv+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__Interrupt47
	MOVF       _inv+0, 0
	SUBLW      1
L__Interrupt47:
	BTFSC      STATUS+0, 0
	GOTO       L_Interrupt24
	MOVLW      12
	ADDWF      _triad+1, 1
L_Interrupt24:
;midiuart.c,87 :: 		}
L_Interrupt23:
;midiuart.c,88 :: 		if (chordtype>MAJ) {
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      _chordtype+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__Interrupt48
	MOVF       _chordtype+0, 0
	SUBLW      0
L__Interrupt48:
	BTFSC      STATUS+0, 0
	GOTO       L_Interrupt25
;midiuart.c,89 :: 		if(chordtype< AUG) {
	MOVLW      128
	XORWF      _chordtype+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__Interrupt49
	MOVLW      3
	SUBWF      _chordtype+0, 0
L__Interrupt49:
	BTFSC      STATUS+0, 0
	GOTO       L_Interrupt26
;midiuart.c,90 :: 		triad[1] -= 1;
	DECF       _triad+1, 1
;midiuart.c,91 :: 		if(chordtype > MIN) triad[2] -=1;
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      _chordtype+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__Interrupt50
	MOVF       _chordtype+0, 0
	SUBLW      1
L__Interrupt50:
	BTFSC      STATUS+0, 0
	GOTO       L_Interrupt27
	DECF       _triad+2, 1
L_Interrupt27:
;midiuart.c,92 :: 		}
L_Interrupt26:
;midiuart.c,93 :: 		if(chordtype == AUG) triad[2] += 1;
	MOVLW      0
	XORWF      _chordtype+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__Interrupt51
	MOVLW      3
	XORWF      _chordtype+0, 0
L__Interrupt51:
	BTFSS      STATUS+0, 2
	GOTO       L_Interrupt28
	INCF       _triad+2, 1
L_Interrupt28:
;midiuart.c,94 :: 		if(chordtype == PWR) triad[1] -= 2;
	MOVLW      0
	XORWF      _chordtype+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__Interrupt52
	MOVLW      4
	XORWF      _chordtype+0, 0
L__Interrupt52:
	BTFSS      STATUS+0, 2
	GOTO       L_Interrupt29
	MOVLW      2
	SUBWF      _triad+1, 1
L_Interrupt29:
;midiuart.c,95 :: 		}
L_Interrupt25:
;midiuart.c,97 :: 		midi_write(NOTE_ON,chan,triad[0], vel);
	MOVLW      144
	MOVWF      FARG_midi_write_type+0
	MOVF       _chan+0, 0
	MOVWF      FARG_midi_write_chnl+0
	MOVF       _triad+0, 0
	MOVWF      FARG_midi_write_data1+0
	MOVF       _vel+0, 0
	MOVWF      FARG_midi_write_data2+0
	CALL       _midi_write+0
;midiuart.c,98 :: 		midi_write(NOTE_ON,chan,triad[1], vel);
	MOVLW      144
	MOVWF      FARG_midi_write_type+0
	MOVF       _chan+0, 0
	MOVWF      FARG_midi_write_chnl+0
	MOVF       _triad+1, 0
	MOVWF      FARG_midi_write_data1+0
	MOVF       _vel+0, 0
	MOVWF      FARG_midi_write_data2+0
	CALL       _midi_write+0
;midiuart.c,99 :: 		midi_write(NOTE_ON,chan,triad[2], vel);
	MOVLW      144
	MOVWF      FARG_midi_write_type+0
	MOVF       _chan+0, 0
	MOVWF      FARG_midi_write_chnl+0
	MOVF       _triad+2, 0
	MOVWF      FARG_midi_write_data1+0
	MOVF       _vel+0, 0
	MOVWF      FARG_midi_write_data2+0
	CALL       _midi_write+0
;midiuart.c,100 :: 		while(PORTB.b6 || PORTB.b7);
L_Interrupt30:
	BTFSC      PORTB+0, 6
	GOTO       L__Interrupt34
	BTFSC      PORTB+0, 7
	GOTO       L__Interrupt34
	GOTO       L_Interrupt31
L__Interrupt34:
	GOTO       L_Interrupt30
L_Interrupt31:
;midiuart.c,101 :: 		midi_write(NOTE_OFF,chan,triad[0], vel);
	MOVLW      128
	MOVWF      FARG_midi_write_type+0
	MOVF       _chan+0, 0
	MOVWF      FARG_midi_write_chnl+0
	MOVF       _triad+0, 0
	MOVWF      FARG_midi_write_data1+0
	MOVF       _vel+0, 0
	MOVWF      FARG_midi_write_data2+0
	CALL       _midi_write+0
;midiuart.c,102 :: 		midi_write(NOTE_OFF,chan,triad[1], vel);
	MOVLW      128
	MOVWF      FARG_midi_write_type+0
	MOVF       _chan+0, 0
	MOVWF      FARG_midi_write_chnl+0
	MOVF       _triad+1, 0
	MOVWF      FARG_midi_write_data1+0
	MOVF       _vel+0, 0
	MOVWF      FARG_midi_write_data2+0
	CALL       _midi_write+0
;midiuart.c,103 :: 		midi_write(NOTE_OFF,chan,triad[2], vel);
	MOVLW      128
	MOVWF      FARG_midi_write_type+0
	MOVF       _chan+0, 0
	MOVWF      FARG_midi_write_chnl+0
	MOVF       _triad+2, 0
	MOVWF      FARG_midi_write_data1+0
	MOVF       _vel+0, 0
	MOVWF      FARG_midi_write_data2+0
	CALL       _midi_write+0
;midiuart.c,104 :: 		INTCON &= 0xFE;
	MOVLW      254
	ANDWF      INTCON+0, 1
;midiuart.c,105 :: 		}
L_end_Interrupt:
L__Interrupt43:
	MOVF       ___savePCLATH+0, 0
	MOVWF      PCLATH+0
	SWAPF      ___saveSTATUS+0, 0
	MOVWF      STATUS+0
	SWAPF      R15+0, 1
	SWAPF      R15+0, 0
	RETFIE
; end of _Interrupt
