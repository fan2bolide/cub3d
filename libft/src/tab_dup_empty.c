/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_dup_empty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:47:17 by nfaust            #+#    #+#             */
/*   Updated: 2023/11/06 03:23:35 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	set_zeros(char *src, size_t len)
{
	src[len] = 0;
	len--;
	while (len > 0)
	{
		src[len] = '0';
		len--;
	}
	src[len] = '0';
}

char	**tab_dup_empty(char **src)
{
	size_t	i;
	size_t	j;
	char	**dst;

	i = 0;
	while (src[i])
		i++;
	dst = malloc(sizeof(char *) * (i + 1));
	if (!dst)
		return (NULL);
	j = 0;
	while (j < i)
	{
		dst[j] = malloc((ft_strlen(src[j]) + 1) * sizeof(char));
		if (!dst[j])
			return (ft_old_split_destroy(dst), NULL);
		set_zeros(dst[j], ft_strlen((src[j])));
		j++;
	}
	dst[j] = NULL;
	return (dst);
}