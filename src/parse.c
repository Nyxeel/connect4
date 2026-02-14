
#include "../inc/connect4.h"

static bool	digit_check(const char *str)
{
	ft_skip_zeros(&str);
	ft_skip_signs(&str);
	int j = 0;
	while (str[j])
	{
		if (!ft_isdigit(str[j++]))
			return (false);
	}
	return true;
}


bool	parse(t_data *data, char **argv)
{
	if (!digit_check(argv[1]) || !digit_check(argv[2]))
	{
		print_error("Only numbers are valid!");
		return (false);
	}
	if (int_overflow_check(argv[1]) || int_overflow_check(argv[2]))
	{
		print_error("Number overflowed");
		return (false);
	}
	if (((data->rows = atoi(argv[1])) < 6) || ((data->columns = atoi(argv[2])) < 7))
	{
		printf("rows: %i, columns: %i\n", data->rows, data->columns);

		if (data->rows >= 0 && data->columns >= 0)
			print_error("Minimum grid size is 6 lines & 7 columns");
		else
			print_error("Negative numbers are not allowed");
		return (false);
	}
	return (true);
}
