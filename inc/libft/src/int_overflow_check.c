/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_overflow_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 05:49:41 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/15 17:51:43 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "string.h"
#include "stdio.h"



bool	int_overflow_check(const char *str)
{
	const char	*p;
	bool		negative;
	size_t			len;

	p = str;
	ft_skip_whitespaces(&p);
	negative = ft_skip_signs(&p);
	ft_skip_zeros(&p);
	ft_printf("STR: %s", p);
	len = strlen(p);
	printf("LEN: %zu", len);

	if (len < 10)
		return (ft_printf("1\n"), false);
	if (len > 10)
		return (ft_printf("2\n"),true);
	if (len == 10 && !negative && ft_strncmp(p, "2147483647", 10) <= 0)
		return (ft_printf("3\n"), false);
	if (len == 10 && negative && ft_strncmp(p, "2147483648", 10) <= 0)
		return (ft_printf("4\n"), false);
	return (true);
}
