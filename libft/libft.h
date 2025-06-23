/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:23:16 by rodantec          #+#    #+#             */
/*   Updated: 2025/05/18 10:19:58 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_lst
{
	int				content;
	struct s_lst	*next;
}	t_lst;

void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(void *s1, const void *s2, size_t n);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *str, const char *find, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

int		ft_printchar_fd(char c, int fd);
int		ft_printstr_fd(char *s, int fd);
int		ft_voidpointer(void *ptr);
int		ft_iitoa(int n);
int		ft_unsignedi(unsigned int n);
int		ft_hexamin(int n);
int		ft_hexamaj(int n);
int		ft_percent(void);
int		ft_idformat(va_list arg, char c);
int		ft_printf(const char *str, ...);
int		ft_size_n_hexa(unsigned long n);
int		ft_size_n_deci(long n);

int		print_array(char **array);
void	free_array(char **array);

t_lst	*ft_lstnew(int content);
void	ft_lstadd_front(t_lst **lst, t_lst *new);
int		ft_lstsize(t_lst *lst);
t_lst	*ft_lstlast(t_lst *lst);
void	ft_lstadd_back(t_lst **lst, t_lst *new);
void	ft_lstdelone(t_lst *lst, void (*del)(void *));
void	ft_lstclear(t_lst **lst);
t_lst	*ft_lstmap(t_lst *lst, void *(*f)(void *), void (*del)(void *));

#endif
