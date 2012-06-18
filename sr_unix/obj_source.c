#include "mdef.h"

#include "obj_source.h"

GBLREF char		source_file_name[];
GBLREF unsigned short	source_name_len;

struct obj_source get_obj_source(void)
{
	struct obj_source sn = {source_file_name, source_name_len};
	return sn;
}
