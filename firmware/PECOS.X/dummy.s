.arch armv7e-m
	.fpu fpv4-sp-d16
	.eabi_attribute 27, 1
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.text
	.section    .secAnduin, code
	.align	1
	.global	AnduinTheSecond
	.syntax unified
	.thumb
	.thumb_func
	.type	AnduinTheSecond, %function
AnduinTheSecond:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, [r7, #4]
	ldr	r3, [r3]
	adds	r2, r3, #1
	ldr	r3, [r7, #4]
	str	r2, [r3]
	nop
	adds	r7, r7, #12
	mov	sp, r7
	@ sp needed
	ldr	r7, [sp], #4
	bx	lr
	.size	AnduinTheSecond, .-AnduinTheSecond
	.section	.secVarian, code
	.align	1
	.global	VarianTheFirst
	.syntax unified
	.thumb
	.thumb_func
	.type	VarianTheFirst, %function
VarianTheFirst:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #16
	add	r7, sp, #0
	str	r0, [r7, #4]
	str	r1, [r7]
	movs	r3, #0
	str	r3, [r7, #12]
@Begin PECOS Block.
@T4 Branch Encoding.
@Symbolic Operands
@Step A: Save context.
	push	{r0-r4}		@(A1): Save used registers.
@Step 1: Load original CFI.
	ldr	r0, =.CFI1	@(1): Load runtime CFI's VMA (addrCFI).
	ldr	r1, [r0]	@(2): (2)-(4) Format register to big endian.
	rev16	r1, r1		@(3)
	rev	r1, r1		@(4)
@Step 2: Build valid CFI.
	ldr 	r2, =.L3	@(5): Load CFI target address (addrTarget).
	add	r0, r0, #4	@(6): Add PC relative offset to CFI's VMA.
	sub	r2, r2, r0	@(7): imm32 = addrTarget - (addrCFI + 4)
	mov	r3, #0		@(8): Clean register to store valid CFI.
	mov	r4, r2, lsr #1	@(9): (9)-(11) Take imm11 from imm32.
	mov	r0, #0x7FF	@(10)
	and 	r4, r4, r0	@(11)
	orr	r3, r3, r4	@(12): Load imm11.
	mov	r4, r2, lsr #12	@(13): (13)-(15) Take imm10 from imm32.
	mov	r0, #0x3FF	@(14)
	and 	r4, r4, r0	@(15)
	mov	r4, r4, lsl #16 @(16): (16)-(17) Place and load imm10.
	orr	r3, r3, r4	@(17)
	mov	r0, r2, lsr #24	@(18): (18)-(19) Take S from imm32.
	and 	r0, r0, #0x1	@(19)
	mov	r4, r0, lsl #26 @(20): (20)-(21) Place and load S.
	orr	r3, r3, r4	@(21)
	mov	r4, r2, lsr #22	@(22): (22)-(23) Take I2 from imm32.
	and 	r4, r4, #0x1	@(23)
	eor	r4, r4, r0	@(24): (24)-(26) J2 = not (I2 xor S)
	mvn	r4, r4		@(25)
	and 	r4, r4, #0x1	@(26)
	mov	r4, r4, lsl #11 @(27): (27)-(28) Place and load J2
	orr	r3, r3, r4	@(28)
	mov	r4, r2, lsr #23	@(29): (29)-(30) Take I1 from imm32.
	and 	r4, r4, #0x1	@(30)
	eor	r4, r4, r0	@(31): (31)-(33) J1 = not (I1 xor S)
	mvn	r4, r4		@(32)
	and 	r4, r4, #0x1	@(33)
	mov	r4, r4, lsl #13 @(34): (34)-(35) Place and load J1
	orr	r3, r3, r4	@(35)
	ldr	r4, =#0xF0009000@(36): (36)-(37) Load CFI's nemonic opcode.
	orr	r3, r3, r4	@(37)
@Step 3: Compare Step 1 and Step 2.
	sub	r3, r3, r1	@(38): Should store zero for correct execution.
	cmp	r3, #0		@(39): (39)-(43) rx = !rx
	ite	eq		@(40)
	moveq	r3, #1		@(41)
	movne	r3, #0		@(42)
	uxtb	r3, r3		@(43)
	sdiv	r3, r1, r3	@(44): Raises exception if rx was not zero.
@Step B: Restore context.
	pop	{r0-r4}		@(B1): Restore used registers.
@End PECOS Block.
.CFI1:	b.w	.L3
.L6:
	ldr	r3, [r7, #12]
	lsls	r3, r3, #2
	ldr	r2, [r7, #4]
	add	r3, r3, r2
	ldr	r3, [r3]
@Begin PECOS Block.
@T4 Branch Encoding.
@Symbolic Operands
@Step A: Save context.
	push	{r0-r4}		@(A1): Save used registers.
@Step 1: Load original CFI.
	ldr	r0, =.CFI2	@(1): Load runtime CFI's VMA.
	ldr	r1, [r0]	@(2): (2)-(4) Load and reorder runtime CFI.
	rev16	r1, r1		@(3)
	rev	r1, r1		@(4)
@Step 2: Build valid CFI.
	ldr 	r2, =.L4	@(6): Load labelDest.
	add	r0, r0, #4	@(7): Load labelCFI. Add PC relative offset.
	sub	r2, r2, r0	@(8): imm32 = labelDest - (labelCFI + 4)
	mov	r3, #0

	mov	r4, r2, lsr #1	@(9): (9)-(11) Take imm11 from imm32.
	mov	r0, #0x7FF	@(10) optimizar con bit clear field en lugar de and.
	and 	r4, r4, r0	@(11)
	orr	r3, r3, r4	@(36): Load imm11

	mov	r4, r2, lsr #12	@(12): (12)-(14) Take imm10 from imm32.
	mov	r0, #0x3F	@(13)
	and 	r4, r4, r0	@(14)
	mov	r4, r4, lsl #16 @(30): (30)-(31) Place and load imm10 into CFI.
	orr	r3, r3, r4	@(31)

	mov	r0, r2, lsr #24	@(19): (19)-(20) Take S from imm32.
	and 	r0, r0, #0x1	@(20)
	mov	r4, r0, lsl #26 @(28): (28)-(29) Place and load S
	orr	r3, r3, r4	@(29)

	mov	r4, r2, lsr #22	@(15): (15)-(16) Take I2 from imm32.
	and 	r4, r4, #0x1	@(16)
	eor	r4, r4, r0	@(24): (24)-(26) J2 = not (I2 xor S)
	mvn	r4, r4		@(25)
	and 	r4, r4, #0x1	@(26)
	mov	r4, r4, lsl #11 @(34): (34)-(35) Place and load J2
	orr	r3, r3, r4	@(35)

	mov	r4, r2, lsr #23	@(17): (17)-(18) Take I1 from imm32.
	and 	r4, r4, #0x1	@(18)
	eor	r4, r4, r0	@(24): (24)-(26) J1 = not (I1 xor S)
	mvn	r4, r4		@(25)
	and 	r4, r4, #0x1	@(26)
	mov	r4, r4, lsl #13 @(32): (32)-(33) Place and load J1
	orr	r3, r3, r4	@(33)

	@ldr	r4, =#0xF2408000	@(37): Load CFI's nemonic opcode.
	orr	r3, r3, r4		@(38)

@Step 3: Compare Step 1 and Step 2.
	ldr	r3, =#0xF2408057
	sub	r3, r3, r1	@(39): Should be zero for correct execution.
	cmp	r3, #0		@(40): (40)-(44) does rx = !rx
	ite	eq		@(41)
	moveq	r3, #1		@(42)
	movne	r3, #0		@(43)
	uxtb	r3, r3		@(44)
@	mov		r3, #0
	sdiv	r3, r1, r3	@(45): Raises exception if rx was not 0.
@Step B: Restore context.
	pop	{r0-r4}		@(B1): Restore used registers.
@End PECOS Block.
	cmp	r3, #2
.CFI2:	bls.w	.L4
	ldr	r3, [r7, #12]
	lsls	r3, r3, #2
	ldr	r2, [r7, #4]
	add	r3, r3, r2
	movs	r2, #0
	str	r2, [r3]
@Begin PECOS Block.
@T4 Branch Encoding.
@Symbolic Operands
@Step A: Save context.
	push	{r0-r4}		@(A1): Save used registers.
@Step 1: Load original CFI.
	ldr	r0, =.CFI3	@(1): Load runtime CFI's VMA.
	ldr	r1, [r0]	@(2): (2)-(4) Load and reorder runtime CFI.
	rev16	r1, r1		@(3)
	rev	r1, r1		@(4)
@Step 2: Build valid CFI.
	ldr 	r2, =.L5	@(6): Load labelDest.
	add	r0, r0, #4	@(7): Load labelCFI. Add PC relative offset.
	sub	r2, r2, r0	@(8): imm32 = labelDest - (labelCFI + 4)
	mov	r3, #0

	mov	r4, r2, lsr #1	@(9): (9)-(11) Take imm11 from imm32.
	mov	r0, #0x7FF	@(10) optimizar con bit clear field en lugar de and.
	and 	r4, r4, r0	@(11)
	orr	r3, r3, r4	@(36): Load imm11

	mov	r4, r2, lsr #12	@(12): (12)-(14) Take imm10 from imm32.
	mov	r0, #0x3FF	@(13)
	and 	r4, r4, r0	@(14)
	mov	r4, r4, lsl #16 @(30): (30)-(31) Place and load imm10 into CFI.
	orr	r3, r3, r4	@(31)

	mov	r0, r2, lsr #24	@(19): (19)-(20) Take S from imm32.
	and 	r0, r0, #0x1	@(20)
	mov	r4, r0, lsl #26 @(28): (28)-(29) Place and load S
	orr	r3, r3, r4	@(29)

	mov	r4, r2, lsr #22	@(15): (15)-(16) Take I2 from imm32.
	and 	r4, r4, #0x1	@(16)
	eor	r4, r4, r0	@(24): (24)-(26) J2 = not (I2 xor S)
	mvn	r4, r4		@(25)
	and 	r4, r4, #0x1	@(26)
	mov	r4, r4, lsl #11 @(34): (34)-(35) Place and load J2
	orr	r3, r3, r4	@(35)

	mov	r4, r2, lsr #23	@(17): (17)-(18) Take I1 from imm32.
	and 	r4, r4, #0x1	@(18)
	eor	r4, r4, r0	@(24): (24)-(26) J1 = not (I1 xor S)
	mvn	r4, r4		@(25)
	and 	r4, r4, #0x1	@(26)
	mov	r4, r4, lsl #13 @(32): (32)-(33) Place and load J1
	orr	r3, r3, r4	@(33)

	ldr	r4, =#0xF0009000	@(37): Load CFI's nemonic opcode.
	orr	r3, r3, r4		@(38)

@Step 3: Compare Step 1 and Step 2.
	sub	r3, r3, r1	@(39): Should be zero for correct execution.
	cmp	r3, #0		@(40): (40)-(44) does rx = !rx
	ite	eq		@(41)
	moveq	r3, #1		@(42)
	movne	r3, #0		@(43)
	uxtb	r3, r3		@(44)
	@mov		r3, #0
	sdiv	r3, r1, r3	@(45): Raises exception if rx was not 0.
@Step B: Restore context.
	pop	{r0-r4}		@(B1): Restore used registers.
@End PECOS Block.
.CFI3:	b.w	.L5
.L4:
	ldr	r3, [r7, #12]
	lsls	r3, r3, #2
	ldr	r2, [r7, #4]
	add	r3, r3, r2
	mov	r0, r3
@Begin PECOS Block.
@T4 Branch Encoding.
@Symbolic Operands
@Step A: Save context.
	push	{r0-r4}		@(A1): Save used registers.
@Step 1: Load original CFI.
	ldr	r0, =.CFI4	@(1): Load runtime CFI's VMA.
	ldr	r1, [r0]	@(2): (2)-(4) Load and reorder runtime CFI.
	rev16	r1, r1		@(3)
	rev	r1, r1		@(4)
@Step 2: Build valid CFI.
	ldr 	r2, =AnduinTheSecond	@(6): Load labelDest.
	add	r0, r0, #4	@(7): Load labelCFI. Add PC relative offset.
	sub	r2, r2, r0	@(8): imm32 = labelDest - (labelCFI + 4)
	mov	r3, #0

	mov	r4, r2, lsr #1	@(9): (9)-(11) Take imm11 from imm32.
	mov	r0, #0x7FF	@(10) optimizar con bit clear field en lugar de and.
	and 	r4, r4, r0	@(11)
	orr	r3, r3, r4	@(36): Load imm11

	mov	r4, r2, lsr #12	@(12): (12)-(14) Take imm10 from imm32.
	mov	r0, #0x3FF	@(13)
	and 	r4, r4, r0	@(14)
	mov	r4, r4, lsl #16 @(30): (30)-(31) Place and load imm10 into CFI.
	orr	r3, r3, r4	@(31)

	mov	r0, r2, lsr #24	@(19): (19)-(20) Take S from imm32.
	and 	r0, r0, #0x1	@(20)
	mov	r4, r0, lsl #26 @(28): (28)-(29) Place and load S
	orr	r3, r3, r4	@(29)

	mov	r4, r2, lsr #22	@(15): (15)-(16) Take I2 from imm32.
	and 	r4, r4, #0x1	@(16)
	eor	r4, r4, r0	@(24): (24)-(26) J2 = not (I2 xor S)
	mvn	r4, r4		@(25)
	and 	r4, r4, #0x1	@(26)
	mov	r4, r4, lsl #11 @(34): (34)-(35) Place and load J2
	orr	r3, r3, r4	@(35)

	mov	r4, r2, lsr #23	@(17): (17)-(18) Take I1 from imm32.
	and 	r4, r4, #0x1	@(18)
	eor	r4, r4, r0	@(24): (24)-(26) J1 = not (I1 xor S)
	mvn	r4, r4		@(25)
	and 	r4, r4, #0x1	@(26)
	mov	r4, r4, lsl #13 @(32): (32)-(33) Place and load J1
	orr	r3, r3, r4	@(33)

	ldr	r4, =#0xF000D000	@(37): Load CFI's nemonic opcode.
	orr	r3, r3, r4		@(38)

@Step 3: Compare Step 1 and Step 2.
	sub	r3, r3, r1	@(39): Should be zero for correct execution.
	cmp	r3, #0		@(40): (40)-(44) does rx = !rx
	ite	eq		@(41)
	moveq	r3, #1		@(42)
	movne	r3, #0		@(43)
	uxtb	r3, r3		@(44)
	@mov		r3, #0
	sdiv	r3, r1, r3	@(45): Raises exception if rx was not 0.
@Step B: Restore context.
	pop	{r0-r4}		@(B1): Restore used registers.
@End PECOS Block.
.CFI4:	bl	AnduinTheSecond
.L5:
	ldr	r3, [r7, #12]
	adds	r3, r3, #1
	str	r3, [r7, #12]
.L3:
	ldr	r3, [r7, #12]
	ldr	r2, [r7]
@Begin PECOS Block.
@T4 Branch Encoding.
@Symbolic Operands
@Step A: Save context.
	push	{r0-r4}		@(A1): Save used registers.
@Step 1: Load original CFI.
	ldr	r0, =.CFI5	@(1): Load runtime CFI's VMA.
	ldr	r1, [r0]	@(2): (2)-(4) Load and reorder runtime CFI.
	rev16	r1, r1		@(3)
	rev	r1, r1		@(4)
@Step 2: Build valid CFI.
	ldr 	r2, =.L6	@(6): Load labelDest.
	add	r0, r0, #4	@(7): Load labelCFI. Add PC relative offset.
	sub	r2, r2, r0	@(8): imm32 = labelDest - (labelCFI + 4)
	mov	r3, #0

	mov	r4, r2, lsr #1	@(9): (9)-(11) Take imm11 from imm32.
	mov	r0, #0x7FF	@(10) optimizar con bit clear field en lugar de and.
	and 	r4, r4, r0	@(11)
	orr	r3, r3, r4	@(36): Load imm11

	mov	r4, r2, lsr #12	@(12): (12)-(14) Take imm10 from imm32.
	mov	r0, #0x3F	@(13)
	and 	r4, r4, r0	@(14)
	mov	r4, r4, lsl #16 @(30): (30)-(31) Place and load imm10 into CFI.
	orr	r3, r3, r4	@(31)

	mov	r0, r2, lsr #24	@(19): (19)-(20) Take S from imm32.
	and 	r0, r0, #0x1	@(20)
	mov	r4, r0, lsl #26 @(28): (28)-(29) Place and load S
	orr	r3, r3, r4	@(29)

	mov	r4, r2, lsr #22	@(15): (15)-(16) Take I2 from imm32.
	and 	r4, r4, #0x1	@(16)
	eor	r4, r4, r0	@(24): (24)-(26) J2 = not (I2 xor S)
	mvn	r4, r4		@(25)
	and 	r4, r4, #0x1	@(26)
	mov	r4, r4, lsl #11 @(34): (34)-(35) Place and load J2
	orr	r3, r3, r4	@(35)

	mov	r4, r2, lsr #23	@(17): (17)-(18) Take I1 from imm32.
	and 	r4, r4, #0x1	@(18)
	eor	r4, r4, r0	@(24): (24)-(26) J1 = not (I1 xor S)
	mvn	r4, r4		@(25)
	and 	r4, r4, #0x1	@(26)
	mov	r4, r4, lsl #13 @(32): (32)-(33) Place and load J1
	orr	r3, r3, r4	@(33)

	ldr	r4, =#0xF2008000	@(37): Load CFI's nemonic opcode.
	orr	r3, r3, r4		@(38)

@Step 3: Compare Step 1 and Step 2.
	sub	r3, r3, r1	@(39): Should be zero for correct execution.
	cmp	r3, #0		@(40): (40)-(44) does rx = !rx
	ite	eq		@(41)
	moveq	r3, #1		@(42)
	movne	r3, #0		@(43)
	uxtb	r3, r3		@(44)
	@mov		r3, #0
	sdiv	r3, r1, r3	@(45): Raises exception if rx was not 0.
@Step B: Restore context.
	pop	{r0-r4}		@(B1): Restore used registers.
@End PECOS Block.
	cmp	r2, r3
.CFI5:	bhi.w	.L6
	nop
	nop
	adds	r7, r7, #16
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	VarianTheFirst, .-VarianTheFirst




