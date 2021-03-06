/****************************************************************
 *								*
 *	Copyright 2001, 2011 Fidelity Information Services, Inc	*
 *								*
 *	This source code contains the intellectual property	*
 *	of its copyright holder(s), and is made available	*
 *	under a license.  If you do not know the terms of	*
 *	the license, please stop and do not read further.	*
 *								*
 ****************************************************************/

#include "mdef.h"
#include "compiler.h"
#include "opcode.h"
#include "toktyp.h"
#include "advancewindow.h"

error_def(ERR_COMMA);

int f_fnzbitfind(oprtype *a, opctype op)
{
	triple *r, *parm;
	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
	r = maketriple(op);
	if (EXPR_FAIL == expr(&(r->operand[0]), MUMPS_EXPR))      /* bitstring */
		return FALSE;
	if (TK_COMMA != TREF(window_token))
	{
		stx_error(ERR_COMMA);
		return FALSE;
	}
	parm = newtriple(OC_PARAMETER);
	r->operand[1] = put_tref(parm);
	advancewindow();
	if (EXPR_FAIL == expr(&(parm->operand[0]), MUMPS_INT))    /* truthval  */
		return FALSE;
	if (TK_COMMA != TREF(window_token))
		parm->operand[1] = put_ilit(1);
	else
	{
		advancewindow();
		if (EXPR_FAIL == expr(&(parm->operand[1]), MUMPS_INT))    /* position  */
			return FALSE;
	}
	ins_triple(r);
	*a = put_tref(r);
	return TRUE;
}
