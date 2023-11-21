/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 20:02:49 by nfaust            #+#    #+#             */
/*   Updated: 2022/12/07 20:03:35 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dblist	*ft_dblstnew(void *content)
{
	t_dblist	*lst;

	lst = malloc(sizeof(t_dblist));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}
