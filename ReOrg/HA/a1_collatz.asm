	#+ BITTE NICHT MODIFIZIEREN: Vorgabeabschnitt
	#+ ------------------------------------------

.data

str_eingabe: .asciiz "Eingabe: "
str_rueckgabewert: .asciiz "\nDie Laenge der Sequenz ist: "
str_sequenz: .asciiz "\nDie Sequenz ist: "

.align 4
buf_out: .space 4000

.text

.eqv SYS_PUTSTR 4
.eqv SYS_PUTCHAR 11
.eqv SYS_PUTINT 1
.eqv SYS_EXIT 10

main:
	# Eingabe wird ausgegeben:
	li $v0, SYS_PUTSTR
	la $a0, str_eingabe
	syscall

	li $v0, SYS_PUTINT
	la $a0, test_n
	lw $a0, 0($a0)
	syscall

	li $v0, SYS_PUTSTR
	la $a0, str_rueckgabewert
	syscall

	move $v0, $zero
	# Aufruf der Funktion collatz:
	la $a0, buf_out
	la $a1, test_n
	lw $a1, 0($a1)
	jal collatz
	move $t0, $v0

	# Rueckgabewert wird ausgegeben:
	move $a0, $t0
	li $v0, SYS_PUTINT
	syscall

	# Buffer wird ausgegeben:
	li $v0, SYS_PUTSTR
	la $a0, str_sequenz
	syscall

    add $t1, $zero, $zero
	la $t2, buf_out
_main_buffer_loop:
	beq $t1, $t0, _main_buffer_loop_end

	li $v0, SYS_PUTINT
	lw $a0, 0($t2)
	syscall

	li $v0, SYS_PUTCHAR
	addi $a0, $zero, 32 # $a0 = ' '
	syscall

	addi $t1, $t1, 1
	addi $t2, $t2, 4
	j _main_buffer_loop

_main_buffer_loop_end:

	# Ende der Programmausfuehrung:
	li $v0, SYS_EXIT
	syscall

	#+ BITTE VERVOLLSTAENDIGEN: Persoenliche Angaben zur Hausaufgabe
	#+ -------------------------------------------------------------

	# Vorname:
	# Nachname:
	# Matrikelnummer:

	#+ Loesungsabschnitt
	#+ -----------------

.data

test_n: .word 13

.text

collatz:
	jr $ra
