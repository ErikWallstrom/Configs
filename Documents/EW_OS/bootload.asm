bits 16
org 0x7C00

jmp short main
nop

; Fat12 description table
OEM_LABEL 			db "EWOSBOOT"
BYTES_PER_SECTOR 	dw 512
SECTORS_PER_CLUSTER db 1
RESERVED_FOR_BOOT 	dw 1
NUMBER_OF_FATS		db 2
ROOT_DIR_ENTRIES	dw 224
LOGICAL_SECTORS		dw 2880
MEDIUM_BYTE			db 0xF0
SECTORS_PER_FAT		dw 9
SECTORS_PER_TRACK	dw 18
SIDES				dw 2
HIDDEN_SECTORS		dd 0
LARGE_SECTORS		dd 0
DRIVE_NUMBER		dw 0
SIGNATURE			db 41
VOLUME_ID			dd 0x00000000
VOLUME_LABEL		db "EW_OS-0.1  "
FILE_SYSTEM			db "FAT12   "

main:
	xor ax, ax
	mov ds, ax

	mov si, NAME
	call addstr

	mov si, DESCRIPTION
	call addstr

	.loop:
		; getch
		mov ah, 0x00
		int 0x16 

		add al, 1

		; putch
		mov ah, 0x0E
		int 0x10
	jmp .loop

addch: ; al = character to print
	mov ah, 0x0E
	int 0x10
ret

_addch:
	call addch
addstr: ; si = string to print
	lodsb
	cmp al, 0
	jne _addch
ret

NAME 		db "EW_OS - Version 0.1", 0
DESCRIPTION db `\r\n\r\nThis operating system writes the letter after the one you entered.\r\nVery useful, I know :))))\r\n\r\n`, 0

times 510 - ($ - $$) db 0
db 0x55
db 0xAA
