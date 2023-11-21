/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblistadd_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:48:39 by nfaust            #+#    #+#             */
/*   Updated: 2022/12/07 20:05:51 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dblstadd_back(t_dblist **lst, t_dblist *new)
{
	t_dblist	*last_elt;

	if (lst)
	{
		if (*lst)
		{
			last_elt = ft_dblstlast(*lst);
			if (new)
			{
				last_elt->next = new;
				new->prev = last_elt;
				new->next = NULL;
			}
		}
		else
			*lst = new;
	}
}
