/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:42:47 by bajeanno          #+#    #+#             */
/*   Updated: 2023/10/27 16:06:10 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_strisset(char *str, char const *set)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isset(str[i], set))
			return (0);
		i++;
	}
	return (1);
}
