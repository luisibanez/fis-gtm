#################################################################
#								#
#	Copyright 2001 Sanchez Computer Associates, Inc.	#
#								#
#	This source code contains the intellectual property	#
#	of its copyright holder(s), and is made available	#
#	under a license.  If you do not know the terms of	#
#	the license, please stop and do not read further.	#
#								#
#################################################################

	.arch armv6
	.fpu vfp
	.text

	.align	2
	.global	dm_start_arm
	.type	dm_start_arm, %function
dm_start_arm:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
	.size	dm_start_arm, .-dm_start_arm

	.align	2
	.global	gtm_levl_ret_code
	.type	gtm_levl_ret_code, %function
gtm_levl_ret_code:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
	.size	gtm_levl_ret_code, .-gtm_levl_ret_code

	.align	2
	.global	gtm_ret_code
	.type	gtm_ret_code, %function
gtm_ret_code:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
	.size	gtm_ret_code, .-gtm_ret_code
