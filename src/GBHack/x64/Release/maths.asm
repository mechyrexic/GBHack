; Listing generated by Microsoft (R) Optimizing Compiler Version 19.00.24245.0 

include listing.inc

INCLUDELIB OLDNAMES

PUBLIC	?VectorNormalize@@YAXAEAUVector@@@Z		; VectorNormalize
PUBLIC	?Rad2Vec@@YA?AUVector@@MM@Z			; Rad2Vec
;	COMDAT pdata
pdata	SEGMENT
$pdata$?VectorNormalize@@YAXAEAUVector@@@Z DD imagerel $LN4
	DD	imagerel $LN4+146
	DD	imagerel $unwind$?VectorNormalize@@YAXAEAUVector@@@Z
pdata	ENDS
;	COMDAT pdata
pdata	SEGMENT
$pdata$?Rad2Vec@@YA?AUVector@@MM@Z DD imagerel $LN4@Rad2Vec
	DD	imagerel $LN4@Rad2Vec+122
	DD	imagerel $unwind$?Rad2Vec@@YA?AUVector@@MM@Z
pdata	ENDS
;	COMDAT xdata
xdata	SEGMENT
$unwind$?Rad2Vec@@YA?AUVector@@MM@Z DD 081c01H
	DD	02881cH
	DD	037813H
	DD	04680bH
	DD	030029206H
xdata	ENDS
;	COMDAT xdata
xdata	SEGMENT
$unwind$?VectorNormalize@@YAXAEAUVector@@@Z DD 083001H
	DD	028830H
	DD	037817H
	DD	04680bH
	DD	030029206H
; Function compile flags: /Ogtpy
; File d:\repositories\github\gbhack\src\gbhack\maths.cpp
;	COMDAT ?VectorNormalize@@YAXAEAUVector@@@Z
_TEXT	SEGMENT
vec$ = 96
?VectorNormalize@@YAXAEAUVector@@@Z PROC		; VectorNormalize, COMDAT

; 26   : {

$LN4:
	push	rbx
	sub	rsp, 80					; 00000050H
	movaps	XMMWORD PTR [rsp+64], xmm6
	mov	rbx, rcx

; 27   : 	float radius = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

	movss	xmm6, DWORD PTR [rcx]
	movaps	XMMWORD PTR [rsp+48], xmm7
	movaps	xmm0, xmm6
	movss	xmm7, DWORD PTR [rcx+4]
	mulss	xmm0, xmm6
	movaps	xmm1, xmm7
	mulss	xmm1, xmm7
	movaps	XMMWORD PTR [rsp+32], xmm8
	movss	xmm8, DWORD PTR [rcx+8]
	movaps	xmm2, xmm8
	addss	xmm0, xmm1
	mulss	xmm2, xmm8
	addss	xmm0, xmm2
	call	sqrtf

; 28   : 
; 29   : 	// FL_EPSILON is added to the radius to eliminate the possibility of divide by zero.
; 30   : 	float iradius = 1.f / (radius + FL_EPSILON);

	addss	xmm0, DWORD PTR __real@34000000
	movss	xmm1, DWORD PTR __real@3f800000
	divss	xmm1, xmm0

; 31   : 
; 32   : 	vec.x *= iradius;

	mulss	xmm6, xmm1

; 33   : 	vec.y *= iradius;

	mulss	xmm7, xmm1

; 34   : 	vec.z *= iradius;

	mulss	xmm8, xmm1
	movss	DWORD PTR [rbx], xmm6

; 35   : }

	movaps	xmm6, XMMWORD PTR [rsp+64]
	movss	DWORD PTR [rbx+4], xmm7
	movaps	xmm7, XMMWORD PTR [rsp+48]
	movss	DWORD PTR [rbx+8], xmm8
	movaps	xmm8, XMMWORD PTR [rsp+32]
	add	rsp, 80					; 00000050H
	pop	rbx
	ret	0
?VectorNormalize@@YAXAEAUVector@@@Z ENDP		; VectorNormalize
_TEXT	ENDS
END