#include "gtm_stdlib.h"
#include "gtm_string.h"
#include "mdef.h"

#include "obj_source.h"

GBLREF char		source_file_name[];
GBLREF unsigned short	source_name_len;

struct obj_source get_obj_source(void)
{
	struct obj_source sn = {source_file_name, source_name_len};
	char* gtm_destdir = getenv("gtm_destdir");
	if(gtm_destdir)
	{
		/* Strip the destdir prefix from sources inside it.  */
		size_t const ddlen = strlen(gtm_destdir);
		if(strncmp(sn.name, gtm_destdir, ddlen) == 0)
		{
			sn.name += ddlen;
			sn.len -= ddlen;
		}
	}
	return sn;
}
