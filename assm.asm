;ADD 16 BIT NUMBERS
;MVI C,00H
;LHLD 2000H
;XCHG 
;LHLD 2002H
;DAD D
;JNC SKIP
;INR C
;MOV A,C
;STA 2009H
;SKIP: SHLD 2006H
;HLT

;USING 8 BIT OPERATION
;MVI D,00H
;LHLD 2000H
;MOV B,H
;MOV C,L
;LHLD 2002H
;MOV A,C
;ADD L
;STA 2006H
;MOV A,B
;ADC H
;STA 2007H
;JNC SKIP
;INR D
;MOV A,D
;STA 2009H
;SKIP: HLT 

;SUBTRACT TWO 16 BIT NUMBERS
;LDA 2000H
;MOV B,A
;LDA 2002H
;SUB B
;STA 2008H
;LDA 2001H
;MOV B,A
;LDA 2003H
;SBB B
;STA 2009H
;HLT

;SEPERATE ODD NUMBERS AND EVEN NUMBERS
;LXI H,2000H
;LXI D,2200H
;MVI B,10
;BACK: MOV A,M
;INX H
;RAR
;JNC SKIP
;RAL
;STAX D
;INX D
;SKIP: DCR B
;JNZ BACK

;EVEN NUMBER
;LXI H,2000H
;LXI D,2100H
;MVI B,10
;BACKE: MOV A,M
;INX H
;RAR
;JC SKIPE
;RAL
;STAX D
;INX D
;SKIPE: DCR B
;JNZ BACKE
;HLT

;max and min in 10 numbers
;LXI H,2000H
;MOV B,M ; FOR STORING MAXIMUM VALUE
;MOV C,M ;FOR STORING MINIMUM VALUE
;MVI D,09H
;INX H
;BACK: MOV A,M
;INX H
;CMP B
;JC SKIP
;MOV B,A
;SKIP: CMP C
;JNC SKIP2
;MOV C,A
;SKIP2: DCR D
;JNZ BACK
;INX H
;INX H
;MOV M,B
;INX H
;MOV M,C
;HLT

;MULTIPLY 8-BIT NUMBERS

;USING DAD
;LDA 2000H
;MOV B,A
;LDA 2001H
;MOV C,A
;LXI H,0000H
;LXI D,0000H
;BACK: MOV L,B
;DAD D
;XCHG
;MVI H,00H
;DCR C
;JNZ BACK
;MOV A,E
;STA 2004H
;MOV A,D
;STA 2005H
;HLT

;WITHOUT USING DAD
;LDA 2000H
;MOV B,A
;LDA 2001H
;MOV C,A
;LXI D,0000H
;BACK: MOV A,B
;ADD E
;MOV E,A
;JNC SKIP
;INR D
;SKIP: DCR C
;JNZ BACK
;MOV A,E
;STA 2004H
;MOV A,D
;STA 2005H
;HLT


;CHECK THAT NUMBER IS PRIME OR NOT
;MVI B,0H
;MVI C,01H
;MOV A,B
;CPI 02H
;JC EXIT
;BACK: MOV D,B
;INR C
;MOV A,C
;CMP B
;JZ SET
;DIV: MOV A,D
;CMP C
;JC BACK
;JZ EXIT
;SUB C
;MOV D,A
;JMP DIV
;SET: MVI A,01H
;STA 2000H
;EXIT: HLT

;FIBONACCI NUMBER FROM 1 TO 100
;MVI B,00H
;MVI C,01H
;LXI H,2000H
;BACK: MOV A,B
;ADD C
;MOV B,C
;MOV C,A
;CPI 100
;JNC EXIT
;MOV M,C
;INX H
;JMP BACK
;EXIT: HLT

;FACTORIAL OF A GIVEN NUMBER
;MVI B,08H
;LXI D,01H
;LOOP: CALL MUL
;DCR B
;JNZ LOOP
;XCHG
;MOV A,E
;STA 2000H
;MOV A,D
;STA 2001H
;HLT
;MUL: MOV C,B
;LXI H,0000H
;LOOP2: DAD D
;DCR C
;JNZ LOOP2
;XCHG
;RET

;BUBBLE SORT
;BACK: LXI H,2000H
;MVI B,04H
;MVI C,00H
;INNER: MOV A,M
;INX H
;CMP M
;JC NEXT // FOR DESCENDING ORDER JNC NEXT
;MOV D,M
;MOV M,A
;DCX H
;MOV M,D
;INX H
;MVI C,01H
;NEXT: DCR B
;JNZ INNER
; MOV A,C
;RRC 
;JC BACK
;HLT

;INSERTION SORT
;LXI H,2000H
;LXI D,2000H
;MVI B,05H
;BACK: INX H
;DCR B
;JZ EXIT
;INX D
;LOOP: MOV A,M
;DCX H
;CMP M
;JNC NEXT
;MOV C,M
;MOV M,A
;INX H
;MOV M,C
;DCX H
;DCX H
;MOV A,M
;INX H
;CMP M
;JNC LOOP
;MOV L,E
;MOV H,D
;JMP BACK
;NEXT: INX H
;JMP BACK
;EXIT: HLT 

;seperate positive and negative and frequency
;LXI H,2000H
;LXI D,2020H
;MVI B,0AH
;MVI C,00H
;LOOP: MOV A,M
;RAL 
;JNC NEXT
;RAR
;STAX D
;ADD C
;MOV C,A
;INX D
;NEXT: DCR B
;INX H
;JNZ LOOP
;INX D
;MOV A,C
;STAX D

;FOR STORING POSITIVE NUMBER
;LXI H,2000H
;LXI D,2040H
;MVI B,0AH
;MVI C,00H
;LOOP2: MOV A,M
;RAL 
;JC NEXT2
;RAR
;STAX D
;ADD C
;MOV C,A
;INX D
;NEXT2: DCR B
;INX H
;JNZ LOOP2
;INX D
;MOV A,C
;STAX D


;HLT

;COMPIMENT THE LOWER NIBBLE
;LXI H,2000H
;MOV A,M
;XRI 0FH
;STA 2001H
;HLT

;OVERLAPING BLOCK PROBLEM
;LXI H,2009H
;LXI D,200EH
;MVI B,0AH
;LOOP: MOV A,M
;STAX D
;DCX D
;DCX H
;DCR B
;JNZ LOOP
;HLT

;BLOCK TRANSFER
;LXI H,2000H
;LXI D,200BH
;MVI B,0AH
;LOOP: MOV C,M
;LDAX D
;MOV M,A
;MOV A,C
;STAX D
;INX D
;INX H
;DCR B
;JNZ LOOP
;HLT

;BINARY SEARCH
;LXI H,2000H
;MVI B,02H
;MVI C,00H
;MVI D,0AH
;DCR D
;LOOP: MOV A,D
;CMP C
;JC NOTFOUND
;CALL MID
;PUSH H
;MOV A,L
;ADD E
;MOV L,A
;MOV A,M
;POP H
;CMP B
;JZ FOUND
;JC SMALLMID
;MOV D,E
;DCR D
;JMP LOOP

;SMALLMID: MOV C,E
;INR C
;JMP LOOP;
;
;FOUND: MVI A,01H
;STA 0000H
;HLT

;NOTFOUND: MVI A,02H
;STA 0000H
;HLT

;MID: MOV A,C
;ADD D
;MOV E,A
;RRC
;JNC SKIP
;DCR E
;SKIP: MOV A,E
;RRC
;MOV E,A
;RET

;SELECTION SORT
;LXI H,2000H
;MVI C,03H
;BACK: DCR C
;JZ EXIT
;MOV A,M
;CALL FINDMIN
;CMP M
;JZ NEXT
;MOV B,M
;MOV M,A
;MOV A,B
;STAX D
;NEXT: INX H
;JMP BACK

;FINDMIN: PUSH H
;PUSH B
;LOOP: INX H
;CMP M
;JC SKIP
;MOV A,M
;MOV D,H
;MOV E,L
;SKIP: DCR C
;JNZ LOOP
;POP B
;POP H
;RET
;EXIT: HLT
























