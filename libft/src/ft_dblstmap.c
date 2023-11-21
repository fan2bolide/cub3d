/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 01:16:30 by nfaust            #+#    #+#             */
/*   Updated: 2022/12/15 01:31:37 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dblist	*ft_dblstmap(t_dblist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_dblist	*new;
	t_dblist	*first_elt;

	if (!lst || !f || !del)
		return (NULL);
	first_elt = NULL;
	while (lst)
	{
		new = ft_dblstnew(f(lst->content));
		if (!new)
		{
			while (first_elt)
			{
				new = first_elt->next;
				del(first_elt->content);
				free(first_elt);
				first_elt = new;
			}
			return (NULL);
		}
		ft_dblstadd_back(&first_elt, new);
		lst = lst->next;
	}
	return (first_elt);
}
