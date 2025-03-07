/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:51:30 by mait-you          #+#    #+#             */
/*   Updated: 2025/03/07 09:23:56 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_receiver	g_receiver;

static void	handle_client_signal(int signal, siginfo_t *siginfo, void *moreinfo)
{
	(void)moreinfo;
	if (g_receiver.client_pid == 0 || g_receiver.client_pid != siginfo->si_pid)
	{
		ft_memset(&g_receiver, 0, sizeof(g_receiver));
		g_receiver.client_pid = siginfo->si_pid;
	}
	g_receiver.current_byte <<= 1;
	if (signal == SIGUSR1)
		g_receiver.current_byte |= 1;
	g_receiver.bit_count++;
	if (g_receiver.bit_count == 8)
	{
		if (g_receiver.current_byte == 0)
			write(1, "\n", 1);
		else
			write(1, &g_receiver.current_byte, 1);
		g_receiver.bit_count = 0;
		g_receiver.current_byte = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_memset(&g_receiver, 0, sizeof(g_receiver));
	write(1, "Server PID: ", 13);
	put_process_id(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = handle_client_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		error_cleanup("Failed to set up signal handlers");
	while (1)
		pause();
	return (0);
}
