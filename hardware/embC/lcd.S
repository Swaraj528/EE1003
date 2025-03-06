    .section .text
    .global PulseEnableLine
    .global SendNibble
    .global SendByte

    .equ PORTB, 0x05  ; I/O address for PORTB
    .equ DDRB,  0x04  ; I/O address for DDRB
    .equ LCD_E,  1    ; Enable pin
    .equ LCD_RS, 0    ; Register Select pin
    .equ DAT4,   2    ; Data pins
    .equ DAT5,   3
    .equ DAT6,   4
    .equ DAT7,   5

; -----------------------
; PulseEnableLine:
; Toggles the LCD_E pin to send a command to the LCD
; -----------------------
PulseEnableLine:
    sbi PORTB, LCD_E    ; Set LCD_E high
    rcall Delay_40us    ; Delay 40us
    cbi PORTB, LCD_E    ; Set LCD_E low
    ret                 ; Return

; -----------------------
; SendNibble:
; Sends the upper 4 bits of a byte to the LCD
; Arguments:
;   r24 - Data to send (upper 4 bits)
; -----------------------
SendNibble:
    push r25            ; Save registers
    push r26

    in r25, PORTB       ; Read current PORTB value
    andi r25, 0xC3      ; Clear data lines (11000011)
    mov r26, r24        ; Copy data
    swap r26            ; Swap nibbles (upper 4 bits -> lower 4)

    sbrc r26, 0         ; Check bit 0 (D4)
    sbi PORTB, DAT4
    sbrc r26, 1         ; Check bit 1 (D5)
    sbi PORTB, DAT5
    sbrc r26, 2         ; Check bit 2 (D6)
    sbi PORTB, DAT6
    sbrc r26, 3         ; Check bit 3 (D7)
    sbi PORTB, DAT7

    rcall PulseEnableLine ; Pulse enable

    pop r26             ; Restore registers
    pop r25
    ret

; -----------------------
; SendByte:
; Sends a full 8-bit byte to the LCD
; Arguments:
;   r24 - Data to send
; -----------------------
SendByte:
    push r24
    rcall SendNibble    ; Send upper 4 bits
    pop r24
    swap r24            ; Swap nibbles to send lower 4 bits
    rcall SendNibble
    ret

; -----------------------
; Delay_40us:
; Approximate 40-microsecond delay (for 16MHz clock)
; -----------------------
Delay_40us:
    ldi r24, 100        ; Approximate cycle count
DelayLoop:
    dec r24
    brne DelayLoop
    ret

