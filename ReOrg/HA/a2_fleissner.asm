	#+ BITTE NICHT MODIFIZIEREN: Vorgabeabschnitt
	#+ ------------------------------------------

.data

str_text: .asciiz "Text: "
str_maske: .asciiz "\nMaske: "
str_verschluesselt: .asciiz "\nVerschluesselter Text: "
rotate_mask_buf: .space 36

buf: .space 37

.text

.eqv SYS_PUTSTR 4
.eqv SYS_PUTCHAR 11
.eqv SYS_PUTINT 1
.eqv SYS_EXIT 10

main:
	# Eingabeparameter text wird ausgegeben:
	li $v0, SYS_PUTSTR
	la $a0, str_text
	syscall

	li $v0, SYS_PUTSTR
	la $a0, test_text
	syscall

	# Eingabeparameter mask wird ausgegeben:
	li $v0, SYS_PUTSTR
	la $a0, str_maske
	syscall

	la $a0, test_mask
	jal print_mask

	move $v0, $zero
	# Aufruf der Funktion fleissner:
	la $a0, buf
	la $a1, test_text
	la $a2, test_mask
	jal fleissner

	# Verschluesselter Text wird ausgegeben:
	li $v0, SYS_PUTSTR
	la $a0, str_verschluesselt
	syscall

	li $v0, SYS_PUTSTR
	la $a0, buf
	syscall

	# Ende der Programmausfuehrung:
	li $v0, SYS_EXIT
	syscall

# void print_mask(byte* mask)
print_mask:
	li $t0, 6
	move $t2, $a0
_print_mask_outer_loop:
	li $v0, SYS_PUTCHAR
	li $a0, 10 # '\n'
	syscall

	li $t1, 6
_print_mask_inner_loop:
	li $v0, SYS_PUTINT
	lb $a0, 0($t2)
	syscall

	li $v0, SYS_PUTCHAR
	li $a0, 32 # ' '
	syscall
	
	addi $t1, $t1, -1
	addi $t2, $t2, 1
	bne $t1, $zero, _print_mask_inner_loop

	addi $t0, $t0, -1
	bne $t0, $zero, _print_mask_outer_loop

	jr $ra

	# Hilfsfunktion: void rotate_mask(byte* mask)
rotate_mask:
	# Copy mask to rotate_mask_buf
	li $t0, 36 # i
	la $t1, rotate_mask_buf
_rotate_mask_copy:
	addi $t0, $t0, -1
	
	add $t2, $a0, $t0
	lb $t2, 0($t2)

	add $t3, $t1, $t0
	sb $t2, 0($t3)

	bne $t0, $zero, _rotate_mask_copy

	# Rotate mask
	li $t0, 0
	li $t1, 5
	la $t2, rotate_mask_buf
	li $t3, 36

_rotate_mask_loop:
	add $t4, $t2, $t0
	lb $t4, 0($t4)

	add $t5, $a0, $t1
	sb $t4, 0($t5)

	addi $t0, $t0, 1
	beq $t0, $t3, _rotate_mask_loop_end
	addi $t1, $t1, 6
	blt $t1, $t3, _rotate_mask_skip_add
	addi $t1, $t1, -37

_rotate_mask_skip_add:
	j _rotate_mask_loop

_rotate_mask_loop_end:
	jr $ra

	#+ BITTE VERVOLLSTAENDIGEN: Persoenliche Angaben zur Hausaufgabe
	#+ -------------------------------------------------------------

	# Vorname:
	# Nachname:
	# Matrikelnummer:

	#+ Loesungsabschnitt
	#+ -----------------

.data

test_text:
	.asciiz "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

test_mask:
	.byte 0, 1, 0, 1, 0, 1
	.byte 0, 0, 0, 0, 1, 0
	.byte 0, 0, 1, 0, 0, 0
	.byte 0, 1, 0, 0, 1, 0
	.byte 0, 0, 0, 0, 0, 1
	.byte 0, 0, 0, 1, 0, 0

.text

fleissner:
	jr $ra