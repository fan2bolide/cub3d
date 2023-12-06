/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:19:47 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/01 13:21:09 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

#define NULL							(void *)0
#define NB_OF_USECONDS_IN_A_SECOND		1000000
#define NB_OF_USECONDS_IN_A_MILLISECOND	1000

struct timeval	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (current_time.tv_usec >= NB_OF_USECONDS_IN_A_SECOND)
	{
		current_time.tv_sec += current_time.tv_usec \
								/ NB_OF_USECONDS_IN_A_SECOND;
		current_time.tv_usec %= NB_OF_USECONDS_IN_A_SECOND;
	}
	return (current_time);
}

long long	get_timestamp(const struct timeval start_time, \
							const struct timeval current_time)
{
	return ((current_time.tv_sec - start_time.tv_sec)
		* (long long)NB_OF_USECONDS_IN_A_MILLISECOND
		+ (current_time.tv_usec - start_time.tv_usec)
		/ NB_OF_USECONDS_IN_A_MILLISECOND);
}
