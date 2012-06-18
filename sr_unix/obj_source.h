#ifndef __OBJ_SOURCE_H__
#define __OBJ_SOURCE_H__

struct obj_source
{
	char* name;
	unsigned short len;
};

struct obj_source get_obj_source(void);

#endif
