/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:59:22 by nfaust            #+#    #+#             */
/*   Updated: 2022/12/12 21:00:12 by nfaust           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dblstclear(t_dblist **lst, void (*del)(void*))
{
	t_dblist	*temp;

	if (lst && del && *lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			ft_dblstdelone(*lst, del);
			*lst = temp;
		}
	}
}
