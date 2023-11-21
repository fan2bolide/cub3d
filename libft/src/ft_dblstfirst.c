/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblstfirst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:11:53 by nfaust            #+#    #+#             */
/*   Updated: 2023/01/05 22:13:44 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dblist	*ft_dblstfirst(t_dblist *list)
{
	if (list)
		while (list->prev)
			list = list->prev;
	return (list);
}
