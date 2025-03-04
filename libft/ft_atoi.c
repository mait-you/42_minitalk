/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:12:59 by mait-you          #+#    #+#             */
/*   Updated: 2025/03/02 17:08:18 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str, int *error)
{
	int		i;
	long	r;

	i = 0;
	r = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (*error = 1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		*error = 0;
		r = r * 10 + (str[i] - '0');
		if ((r > INT_MAX))
			return (*error = 1);
		i++;
	}
	if ((str[i] && (str[i] < '0' || str[i] > '9')))
		return (*error = 1);
	return ((int)r);
}
