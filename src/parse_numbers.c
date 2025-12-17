#include "minirt.h"

static double	parse_fraction(const char *str, int *len)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 10.0;
	while (ft_isdigit(str[*len]))
	{
		fraction += (str[*len] - '0') / divisor;
		divisor *= 10.0;
		(*len)++;
	}
	return (fraction);
}

double	ft_strtod(const char *str, char **endptr)
{
	double	result;
	int		sign;
	int		i;

	result = 0.0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		result += parse_fraction(str, &i);
	}
	if (endptr)
		*endptr = (char *)(str + i);
	return (result * sign);
}

bool	parse_double(char **str, double *result)
{
	char	*endptr;

	skip_whitespace(str);
	*result = ft_strtod(*str, &endptr);
	if (*str == endptr)
		return (false);
	*str = endptr;
	return (true);
}

bool	parse_int(char **str, int *result)
{
	char	*endptr;
	long	val;

	skip_whitespace(str);
	val = ft_atol(*str);
	*result = (int)val;
	endptr = *str;
	if (*endptr == '-' || *endptr == '+')
		endptr++;
	if (!ft_isdigit(*endptr))
		return (false);
	while (ft_isdigit(*endptr))
		endptr++;
	*str = endptr;
	return (true);
}
