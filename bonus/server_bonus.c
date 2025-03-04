/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:51:30 by mait-you          #+#    #+#             */
/*   Updated: 2025/03/03 21:38:17 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	get_byte_str_size(unsigned char byte)
{
	if (byte >= 0b11110000)
		return (4);
	if (byte >= 0b11100000)
		return (3);
	if (byte >= 0b11000000)
		return (2);
	return (1);
}

static int	print_byte(
	unsigned char *byte, pid_t client_pid, int *byte_str_count
	)
{
	static int				byte_str_size;
	static unsigned char	byte_str[8];

	if (*byte_str_count == 0)
		byte_str_size = get_byte_str_size(*byte);
	if (*byte == 0)
		return (write(1, "\n", 1), kill(client_pid, SIGUSR1));
	byte_str[(*byte_str_count)++] = *byte;
	if (*byte_str_count == byte_str_size)
	{
		write(1, byte_str, byte_str_size);
		*byte_str_count = 0;
		byte_str_size = 0;
	}
	return ((*byte = 0));
}

static void	get_signal(int signal, siginfo_t *siginfo, void *moreinfo)
{
	static unsigned char	byte;
	static int				bit_count;
	static pid_t			client_pid;
	static int				byte_str_count;

	(void)moreinfo;
	if (client_pid == 0 || client_pid != siginfo->si_pid)
	{
		client_pid = siginfo->si_pid;
		bit_count = 0;
		byte = 0;
		byte_str_count = 0;
	}
	byte <<= 1;
	if (signal == SIGUSR1)
		byte |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		print_byte(&byte, client_pid, &byte_str_count);
		bit_count = 0;
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
