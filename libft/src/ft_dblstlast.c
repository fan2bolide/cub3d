/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstlast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 20:01:53 by nfaust            #+#    #+#             */
/*   Updated: 2022/12/07 20:02:45 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dblist	*ft_dblstlast(t_dblist *lst)
{
	t_dblist	*last_elt;

	last_elt = lst;
	while (last_elt)
	{
		if (!last_elt->next)
			return (last_elt);
		last_elt = last_elt->next;
	}
	return (last_elt);
}
