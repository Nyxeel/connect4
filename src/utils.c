
#include "../inc/connect4.h"

void print_error(char *str)
{
	ft_printf("%s\n%s\n", ERROR_MSG, str);
}

void	ft_sleep(int sek)
{
	int start = time(NULL);
	while (time(NULL) - start < sek)
	    ;
	return ;
}


