/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:41:23 by mait-you          #+#    #+#             */
/*   Updated: 2025/03/06 17:35:52 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	error_cleanup(char *error_msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error_msg, 2);
	exit(1);
}

int	put_process_id(pid_t pid)
{
	char	*base;
	char	nb;

	base = "0123456789";
	if (pid >= 10)
		put_process_id(pid / 10);
	nb = base[pid % 10];
	write(1, &nb, 1);
	return (0);
}

int	ft_kill(pid_t pid, int signal)
{
	if (kill(pid, signal) == -1)
		error_cleanup("Failed to send signal");
	return (0);
}
