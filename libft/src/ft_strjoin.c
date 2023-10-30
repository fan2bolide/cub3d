/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:40:24 by bajeanno          #+#    #+#             */
/*   Updated: 2023/10/27 20:53:06 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = ft_strnew(len);
	if (res == NULL)
		return (NULL);
	*res = 0;
	ft_strcat(res, (char *)s1);
	ft_strcat(res, (char *)s2);
	return (res);
}

char	*ft_strnjoin(char *s1, const char *s2, int n)
{
	char	*res;
	size_t	len;

	len = ft_strlen((char *)s1) + n;
	res = ft_strnew(len);
	if (res == NULL)
		return (NULL);
	*res = 0;
	ft_strcat(res, (char *)s1);
	ft_strncat(res, (char *)s2, n);
	return (res);
}

char	*ft_strjoin_secure(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = ft_strnew(len);
	if (res == NULL)
		return (NULL);
	*res = 0;
	ft_strcat(res, (char *)s1);
	ft_strcat(res, (char *)s2);
	return (res);
}

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin((const char *)s1, (const char *)s2);
	free(s1);
	return (tmp);
}

char	*ft_strnjoin_free_s1(char *s1, char *s2, int n)
{
	char	*tmp;

	tmp = ft_strnjoin(s1, (const char *)s2, n);
	free(s1);
	return (tmp);
}
