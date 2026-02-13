/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:58:41 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/13 23:45:20 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../src/libft.h"
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_va_start(const char *str, va_list ap);
int	find_arg(char c, va_list ap);
int	ft_arg_string(char *str);
int	ft_int_check(int nb);
int	ft_arg_pointer(void *p, char c);
int	ft_putnbr_base(size_t hexanum, size_t divider, char Xx);

#endif
