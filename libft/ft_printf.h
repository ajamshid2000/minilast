/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:28:45 by famana            #+#    #+#             */
/*   Updated: 2024/03/26 07:23:01 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdint.h>

int		ft_printf(const char *f, ...);
int		ft_handle_format(const char *f, int *i, va_list args);
int		ft_write_to_hex(va_list args);
int		ft_write_int(va_list args);
int		ft_write_lower_hex(va_list args);
int		ft_write_upper_hex(va_list args);
int		ft_write_char(va_list args);
int		ft_rec_hex_upper(unsigned long x);
int		ft_write_unsigned_int(va_list args);
int		ft_rec_hex(unsigned long x);
void	ft_write_num(unsigned int n, int fd);
int		ft_write_percent(void);
int		ft_write_string(va_list args);
#endif
