#include "minirt.h"

// FIXME: Old function. Left here so that previous tests don't fail.
t_computations	prepare_computations_old(t_intersection x, t_ray r)
{
	t_computations	comps;

	comps.t = x.t;
	comps.object = x.object;
	comps.point = ray_position(r, comps.t);
	comps.eyev = tuple_negate(r.direction);
	comps.normalv = normal_at(comps.object, comps.point);
	comps.reflectv = reflect(r.direction, comps.normalv);
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = tuple_negate(comps.normalv);
	}
	else
		comps.inside = false;
	comps.over_point = tuple_sum(
			comps.point, tuple_scale_multiply(comps.normalv, EPSILON));
	comps.shadowed = false;
	return (comps);
}
