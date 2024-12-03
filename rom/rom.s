	.org $8000
	lda #$10

loop
	sbc #$1
	jmp loop

	.org $FFFC
	.word $8000
	.word $0000
