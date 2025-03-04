/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:51:30 by mait-you          #+#    #+#             */
/*   Updated: 2025/03/03 21:17:28 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	get_signal(int signal, siginfo_t *siginfo, void *moreinfo)
{
	static unsigned char	byte;
	static int				bit_count;
	static pid_t			client_pid;

	(void)moreinfo;
	if (client_pid == 0 || client_pid != siginfo->si_pid)
	{
		client_pid = siginfo->si_pid;
		bit_count = 0;
		byte = 0;
	}
	byte <<= 1;
	if (signal == SIGUSR1)
		byte |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		if (byte == 0)
			write(1, "\n", 1);
		else
			write(1, &byte, 1);
		bit_count = 0;
		byte = 0;
	}
}

int	main(void)
{
	struct sigaction	signal;

	write(1, "Server PID: ", 13);
	put_process_id(getpid());
	write(1, "\n", 1);
	signal.sa_sigaction = get_signal;
	signal.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &signal, NULL) == -1
		|| sigaction(SIGUSR2, &signal, NULL) == -1)
		error_cleanup("Failed to set up signal handlers");
	while (1)
		pause();
	return (0);
}
