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

#include "gtm_string.h"

#include "compiler.h"
#include "opcode.h"
#include "toktyp.h"
#include "nametabtyp.h"
#include "job.h"
#include "advancewindow.h"
#include "namelook.h"
#include "mvalconv.h"

/* JOB Parameter tables */
#define JPSDEF(a,b,c) {a, b}
const static readonly nametabent job_param_names[] =
{
#include "jobparamstrs.h"
};

#undef JPSDEF
#define JPSDEF(a,b,c) c
const static readonly jp_type job_param_data[] =
{
#include "jobparamstrs.h"	/* BYPASSOK */
};

const static readonly unsigned char job_param_index[27] =
{
	 0,  2,  2,  2,  6,  8,  8, 10, 10, 14, 14, 14, 16,
	16, 22, 24, 28, 28, 28, 34, 34, 34, 34, 34, 34, 34,
	34
};

#undef JPDEF
#define JPDEF(a,b) b
LITDEF jp_datatype	job_param_datatypes[] =
{
#include "jobparams.h"
};

error_def(ERR_JOBPARNOVAL);
error_def(ERR_JOBPARNUM);
error_def(ERR_JOBPARSTR);
error_def(ERR_JOBPARUNK);
error_def(ERR_JOBPARVALREQ);

int one_job_param (char **parptr)
{
	boolean_t	neg;
	int		x, num;
	int		len;
	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
	if ((TK_IDENT != TREF(window_token))
	     || (0 > (x = (namelook(job_param_index, job_param_names, (TREF(window_ident)).addr, (TREF(window_ident)).len)))))
	{	/* NOTE assigment above */
		stx_error (ERR_JOBPARUNK);
		return FALSE;
	}
	advancewindow();
	*(*parptr)++ = job_param_data[x];
	if (job_param_datatypes[job_param_data[x]] != jpdt_nul)
	{
		if (TK_EQUAL != TREF(window_token))
		{
			stx_error (ERR_JOBPARVALREQ);
			return FALSE;
		}
		advancewindow ();
		switch (job_param_datatypes[job_param_data[x]])
		{
		case jpdt_num:
			neg = FALSE;
			if ((TK_MINUS == TREF(window_token)) && (TK_INTLIT == TREF(director_token)))
			{
				advancewindow();
				neg = TRUE;
			}
			if (TK_INTLIT != TREF(window_token))
			{
				stx_error (ERR_JOBPARNUM);
				return FALSE;
			}
			num = MV_FORCE_INTD(&(TREF(window_mval)));
			*((int4 *)(*parptr)) = (neg ? -num : num);
			*parptr += SIZEOF(int4);
			break;
		case jpdt_str:
			if (TK_STRLIT != TREF(window_token))
			{
				stx_error (ERR_JOBPARSTR);
				return FALSE;
			}
			len = (TREF(window_mval)).str.len;
			*(*parptr)++ = len;
			memcpy(*parptr, (TREF(window_mval)).str.addr, len);
			*parptr += len;
			break;
		default:
			GTMASSERT;
		}
		advancewindow ();
	} else if (TK_EQUAL == TREF(window_token))
	{
		stx_error (ERR_JOBPARNOVAL);
		return FALSE;
	}
	return TRUE;
}
