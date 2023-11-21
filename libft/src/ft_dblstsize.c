/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblistsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 20:07:19 by nfaust            #+#    #+#             */
/*   Updated: 2022/12/07 20:23:35 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_dblstsize(t_dblist *lst)
{
	size_t		i;
	t_dblist	*lst_temp;

	lst_temp = lst;
	i = 0;
	while (lst_temp)
	{
		i++;
		lst_temp = lst_temp->next;
	}
	return (i);
}
