/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:50:18 by nfaust            #+#    #+#             */
/*   Updated: 2022/12/16 00:02:41 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dblstadd_front(t_dblist **lst, t_dblist *new)
{
	if (lst && new)
	{
		if (*lst)
		{
			new->prev = NULL;
			new->next = *lst;
			(*lst)->prev = new;
		}
		*lst = new;
	}
}
