;;;-----------------------------------------

;;;  Hand coded div and mod functions.
;;;  AES 2009
;;;	 for S12X platform
;;;-----------------------------------------

; Re-coded for m68hc12 as well - James Murray October 2010
	
	.file "ldivmod.asm"

#if !defined(mc68hc11) && !defined(mc68hc12) && !defined(m9s12x)
  #error No target defined for ldivmod.asm
#endif

#if defined(mc68hc12) || defined(m9s12x)

#ifdef __HAVE_SHORT_INT__
	.mode mshort
#else
	.mode mlong
#endif

	.macro declare_near name
	.globl \name
	.type  \name,@function
	.size  \name,.Lend-\name
\name:
	.endm

#if defined(__USE_RTC__)
# define ARG(N) N+1

	.macro ret
#if defined(mc68hc12)
	rtc
#else
	jmp __return_32
#endif
	.endm

	.macro declare name
	.globl \name
	.type  \name,@function
	.size  \name,.Lend-\name
	.far   \name
\name:
	.endm

	.macro farsym name
	.far NAME
	.endm

#else
# define ARG(N) N

	.macro ret
	rts
	.endm

	.macro farsym name
	.endm

	.macro declare name
	.globl \name
	.type  \name,@function
	.size  \name,.Lend-\name
\name:
	.endm

#endif

	.sect .text
	

#define REG(NAME)			\
NAME:	.dc.w	1;			\
	.type NAME,@object ;		\
	.size NAME,2

#ifdef L_regs_min
/* Pseudo hard registers used by gcc.
   They should be located in page0.  */

	.sect .softregs
	.globl _.tmp

REG(_.tmp)
#endif



/* ok, guessing that we get called with a in D and X and B on stack */

;;; 
;;; long __divsi3 ( long num, long den )
;;;

;;; d == num_low
;;; x == num_high

;;; sp, ARG(4)  == den_high
;;; sp, ARG(6)  == den_low
;;; return result in XD

;;; calling here we have also pushed 4 extra bytes on stack
;;;  and we dont use a frame pointer


udivmodsi:
	pshy				; preserve y
	pshd				; save numerator in case ediv fails
	pshx
#ifndef m9s12x
	tst 	ARG(10), sp		; does denominator fit in uint16 ?
	bne 	go_soft_udivmodsi
	tst 	ARG(11), sp		; does denominator fit in uint16 ?
	bne 	go_soft_udivmodsi
#else
	tstw 	ARG(10), sp		; does denominator fit in uint16 ?
	bne 	go_soft_udivmodsi
#endif
	tfr 	x,y			; load num_high into y
	ldx	ARG(12), sp		; load denominator into x
	ediv
	bvs	go_soft_udivmodsi 	; overflow ??

	;; overwrite denominator on stack with modulus
	;; this is ok since c copies args onto stack  (???CHECKME)

	std	ARG(12), sp
#ifndef m9s12x
	clr 	ARG(10), sp
	clr 	ARG(11), sp
#else
	clrw 	ARG(10), sp
#endif

	;; return division  results in X:D
#ifndef m9s12x
    ldx #0
#else
	clrx
#endif
	tfr	y,d
	
	leas 	4, sp		  	; deallocate stack for numerator save
	puly				; retrieve y
	rts

go_soft_udivmodsi:
#ifndef m9s12x
    ldy #0
#else
	clry
#endif
	bra 	soft_udivmodsi
	

divmodsi:	

	pshy			; preserve y
	pshd			; save numerator in case edivs fails
	pshx
	ldy	ARG(10),sp	; denominator fits in signed int16  ??
	beq	test_pos
#ifndef m9s12x
    xgdy
    coma
    comb
    xgdy
#else
	comy
#endif
	beq	test_neg
	bra	soft_divmodsi
test_pos:	
	ldy	ARG(12),sp
	bpl	hard_divmodsi 	
	bra	soft_divmodsi

test_neg:
	ldy	ARG(12),sp
	bpl	soft_divmodsi
	
hard_divmodsi:
	
	exg 	x,y
	edivs			; attempt a divide by hardware
	bvs  	soft_divmodsi     	; an overflow happened ... do soft divide

#ifndef m9s12x
	clr 	ARG(10),sp
	clr 	ARG(11),sp
#else
	clrw 	ARG(10),sp
#endif
	std	ARG(12), sp
	bpl	skip_hdsx_mod   ; sign extend modulus
	movw	#0xFFFF, ARG(10), sp 	
skip_hdsx_mod:	


	;; returned division  results in X:D
#ifndef m9s12x
    ldx #0
    xgdy
    tsta
    xgdy
#else
	clrx
	tsty
#endif
	bpl	skip_hdsx_div   ; sign extend result
	ldx    #0xFFFF
	
skip_hdsx_div:	
	tfr	y,d	
	leas    4,sp		; deallocate stack
	puly			; retrieve y
	rts

soft_divmodsi:
	;; numerator in sp and sp+1 ; den in ARG(10) and ARG(12)
#ifndef m9s12x
    ldy #0
#else
	clry	              ; use y to evaluate sign of result
#endif
	tst	0, sp       ; was tstw
	bpl	sd_skip_neg_num

#ifndef m9s12x
    xgdy
    orab    #3
    xgdy
    com     3, sp
    com     2, sp
    com     1, sp
    com     0, sp
	inc	    3, sp
	bne	sd_skip_neg_num
	inc	    2, sp
	bne	sd_skip_neg_num
	inc	    1, sp
	bne	sd_skip_neg_num
	inc 	0, sp
#else
	ory    #3
	comw	2, sp
	comw  	0, sp
	incw	2, sp
	bne	sd_skip_neg_num
	incw	0, sp
#endif
	
sd_skip_neg_num:

	tst 	ARG(10), sp
	bpl	sd_skip_neg_den ; was tstw

#ifndef m9s12x
    xgdy
    eorb    #1
    xgdy
	com 	ARG(13), sp
	com 	ARG(12), sp
	com 	ARG(11), sp
	com 	ARG(10), sp
	inc	    ARG(13), sp
	bne	sd_skip_neg_den
	inc	    ARG(12), sp
	bne	sd_skip_neg_den
	inc	    ARG(11), sp
	bne	sd_skip_neg_den
	inc	    ARG(10), sp
#else
	eory	#1
	comw 	ARG(12), sp
	comw 	ARG(10),  sp
	incw	ARG(12), sp
	bne	sd_skip_neg_den
	incw	ARG(10),  sp
#endif	

sd_skip_neg_den:
soft_udivmodsi:	    		; if called from udivmodsi
				; make sure y=0  
	leas -8,sp		; allocate for 'bit' and 'res' 
	
	;; stack should look like this on entry if  ARG(N)=N:

	;; 
	;; 
	;; 
	;; denominator (SI)                             ---  sp+18
	;; 
	;; return address for calling function  (HI)   sp+16
	;; 
	;; return address for frontend  function (HI) sp+14
	;;
	;; preserve y	   ----  sp+12
	;; 
	;; 
	;; 
	;; numerator (SI)  ----  sp+8
	;;
	;;
	;;
	;; bit (SI)        ----  sp+4
	;;
	;; 
	;; 
	;; res (SI)        ----  sp
	
#ifndef m9s12x
	clr 	0, sp		; res = 0
	clr	    1, sp
	clr	    2, sp
	clr	    3, sp
	tst	ARG(18),sp
	bne     checked_den
	tst	ARG(19),sp
	bne     checked_den
	tst	ARG(20),sp
	bne     checked_den
	tst	ARG(21),sp
	beq	while_end
#else
	clrw 	0, sp		; res = 0
	clrw	2, sp
	tstw	ARG(18),sp
	bne     checked_den
	tstw	ARG(20),sp
	beq	while_end
#endif
	
checked_den:	

	movw	#1, 6, sp
#ifndef m9s12x
	clr	    4,sp            ; bit = 1
	clr	    5,sp            ; bit = 1
#else
	clrw	4,sp            ; bit = 1
#endif

while_den:			; while ((den < num) && !(den.bit31))
	tst 	ARG(18), sp ; was tstw
	bmi 	while_bit
	ldd	10,sp
	ldx	8,sp

	subd 	ARG(20), sp
#ifndef m9s12x
    xgdx
    sbcb    ARG(19), sp
    sbca    ARG(18), sp
    xgdx
#else
	sbex	ARG(18), sp
#endif
	bcs	while_bit

#ifndef m9s12x
	asl	    ARG(21), sp     ;  den <<= 1
	rol	    ARG(20), sp
	rol	    ARG(19), sp
	rol	    ARG(18), sp

	asl	    7,sp		; bit <<= 1
	rol	    6,sp			
	rol	    5,sp			
	rol	    4,sp			
#else
	aslw	ARG(20), sp     ;  den <<= 1
	rolw	ARG(18), sp

	aslw	6,sp		; bit <<= 1
	rolw	4,sp			
#endif

	bra	while_den


while_bit:			; while  (bit!=0)
#ifndef m9s12x
	tst	    4, sp
	bne	while_bit_ok
	tst	    5, sp
	bne	while_bit_ok
	tst	    6, sp
	bne	while_bit_ok
	tst	    7,sp
	beq	while_end
#else
	tstw	4, sp
	bne	while_bit_ok
	tstw	6,sp
	beq	while_end
#endif

while_bit_ok:
	
	ldd 	10, sp		; if (num >= den) 
	ldx	8, sp
	subd	ARG(20),sp
#ifndef m9s12x
    xgdx
    sbcb    ARG(19),sp
    sbca    ARG(18),sp
    xgdx
#else
	sbex	ARG(18),sp
#endif
	bcs	skip_restore   	; here was bmi

	std	10,sp		; num-=den
	stx	8,sp

#ifndef m9s12x
	ldd	    0,sp		; res|= bit
	oraa	4,sp
	orab	5,sp
	std	    0,sp
	ldd	    2,sp
	oraa	6,sp
	orab	7,sp
	std	    2,sp
#else
	ldx	    0,sp		; res|= bit
	orx	    4,sp
	stx	    0,sp
	ldx	    2,sp
	orx	    6,sp
	stx	    2,sp
#endif

skip_restore:
	
#ifndef m9s12x
	lsr	    4,sp 		; bit >>=1
	ror	    5,sp		
	ror	    6,sp		
	ror	    7,sp		
	
	lsr 	ARG(18),sp		; den >>=1
	ror 	ARG(19),sp
	ror 	ARG(20),sp
	ror 	ARG(21),sp
#else
	lsrw	4,sp 		; bit >>=1
	rorw	6,sp		
	
	lsrw	ARG(18),sp		; den >>=1
	rorw	ARG(20),sp
#endif
	
	bra while_bit
	
while_end:
	;; numerator contains mod
	;; overwrite denominator with it on stack for return
//	movw	8,sp,ARG(18), sp 
//	movw	10,sp, ARG(20), sp
	leax	ARG(18), sp
	movw	8,sp, 0,x
	movw	10,sp, 2,x
	
	ldx	0,sp
	ldd 	2,sp

	leas	12,sp 		; deallocate locals
#ifndef m9s12x
    xgdy			; do we need to negate result ?
    tsta
    bne no_end
	tstb
    bne no_end
    xgdy
	bra	end_division
no_end:
    xgdy
#else
	tsty			; do we need to negate result ?
	beq	end_division
#endif
					
	;; 	if y&1 then negate result
	;; 	if y&2 then negate modulus

	pshy
#ifndef m9s12x
    xgdy
    andb    #1
    xgdy
#else
	andy	#1
#endif
	puly
	beq	skip_end_res_neg
	
	coma
	comb
#ifndef m9s12x
    xgdx
    coma
    comb
    xgdx
#else
	comx
#endif
	incb
	bne	end_division
	inca	
	bne	end_division
	inx	

skip_end_res_neg:
#ifndef m9s12x
    xgdy
    andb    #2
    xgdy
#else
	andy	#2
#endif
	beq	end_division

#ifndef m9s12x
	com 	ARG(6), sp
	com 	ARG(7), sp
	com 	ARG(8), sp
	com 	ARG(9), sp
	inc	    ARG(9), sp
	bne	end_division
	inc	    ARG(8), sp
	bne	end_division
	inc	    ARG(7), sp
	bne	end_division
	inc	    ARG(6),  sp
#else
	comw 	ARG(6), sp
	comw 	ARG(8), sp
	incw	ARG(8), sp
	bne	end_division
	incw	ARG(6),  sp
#endif
	
end_division:
	puly
	rts


	
;;;  si3 frontends for divmodsi3
	
	declare __divsi3
	bsr	divmodsi
	ret
	
	declare __modsi3

	bsr 	divmodsi
	ldx	ARG(2), sp	; stack has two less on it now
	ldd	ARG(4), sp	
	ret

	declare __umodsi3
	bsr 	udivmodsi
	ldx	ARG(2), sp
	ldd	ARG(4), sp	
	ret
	
	
	declare __udivsi3
	bsr 	udivmodsi
	ret
	
#endif

.Lend:
;-----------------------------------------
; end required gcclib code
;-----------------------------------------
