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

double	ft_strtod(const char *str, char **endptr, int *i)
{
	double	result;
	int		sign;

	result = 0.0;
	sign = 1;
	while (ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[(*i)++] == '-')
			sign = -1;
	}
	while (ft_isdigit(str[*i]))
	{
		result = result * 10.0 + (str[*i] - '0');
		(*i)++;
	}
	if (str[*i] == '.')
	{
		(*i)++;
		result += parse_fraction(str, i);
	}
	if (endptr)
		*endptr = (char *)(str + *i);
	return (result * sign);
}

bool	parse_double(char **str, double *result)
{
	char	*endptr;
	int		i;

	skip_whitespace(str);
	i = 0;
	*result = ft_strtod(*str, &endptr, &i);
	if (*str == endptr)
		return (false);
	*str = endptr;
	return (true);
}

bool	parse_int(char **str, int *result)
{
	long	val;
	int		error;

	skip_whitespace(str);
	if (**str != '-' && **str != '+' && !ft_isdigit(**str))
		return (false);
	error = 0;
	val = ft_atol_safe(*str, &error);
	if (error || val > INT_MAX || val < INT_MIN)
		return (false);
	*result = (int)val;
	if (**str == '-' || **str == '+')
		(*str)++;
	while (ft_isdigit(**str))
		(*str)++;
	return (true);
}
