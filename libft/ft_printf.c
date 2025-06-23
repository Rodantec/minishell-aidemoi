/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:16:55 by rodantec          #+#    #+#             */
/*   Updated: 2025/04/11 11:29:23 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar_fd(char c, int fd);
int	ft_printstr_fd(char *s, int fd);
int	ft_voidpointer(void *ptr);
int	ft_iitoa(int n);
int	ft_unsignedi(unsigned int n);
int	ft_hexamin(int n);
int	ft_hexamaj(int n);
int	ft_percent(void);
int	ft_size_n_hexa(unsigned long n);
int	ft_size_n_deci(long n);

int	ft_idformat(va_list arg, char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_printchar_fd(va_arg(arg, int), 1);
	else if (c == 's')
		len += ft_printstr_fd(va_arg(arg, char *), 1);
	else if (c == 'p')
		len += ft_voidpointer(va_arg(arg, void *));
	if (c == 'd' || c == 'i')
		len += ft_iitoa(va_arg(arg, int));
	else if (c == 'u')
		len += ft_unsignedi(va_arg(arg, unsigned int));
	else if (c == 'x')
		len += ft_hexamin(va_arg(arg, unsigned int));
	else if (c == 'X')
		len += ft_hexamaj(va_arg(arg, unsigned int));
	else if (c == '%')
		len += ft_percent();
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list	arg;

	va_start(arg, str);
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_idformat(arg, str[i + 1]);
			i++;
		}
		else
			len += ft_printchar_fd(str[i], 1);
		i++;
	}
	return (len);
}
/*
int	main(void)
{
	char	*str;
	int		str2;
	void	*ptr;

	//int		i;
	str = NULL ;
	str2 = 0;
	ptr = NULL;
	printf("%d",ft_printf("%p\n", ""));
	printf("%d",printf("%p\n", ""));
}
*/
