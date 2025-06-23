/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:14:41 by rodantec          #+#    #+#             */
/*   Updated: 2025/03/19 13:27:58 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstnew(int content)
{
	t_lst	*new;

	new = malloc(sizeof(t_lst));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
