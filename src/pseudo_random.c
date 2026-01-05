#include "minirt.h"

static unsigned int	hash_coords(unsigned int x, unsigned int y, unsigned int s)
{
	unsigned int	hash;

	hash = x * 374761393U;
	hash += y * 668265263U;
	hash ^= s * 1274126177U;
	hash = (hash ^ (hash >> 13)) * 1274126177U;
	return (hash ^ (hash >> 16));
}

double	pseudo_random(unsigned int x, unsigned int y, unsigned int s)
{
	return ((double)(hash_coords(x, y, s) & 0xFFFFFF) / 16777216.0);
}
