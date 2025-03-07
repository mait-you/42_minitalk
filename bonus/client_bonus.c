/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:51:30 by mait-you          #+#    #+#             */
/*   Updated: 2025/03/07 09:32:05 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static t_transmission	g_transmission;

static void	get_signal(int signal)
{
	if (signal == SIGUSR1)
		write(1, "Message sent successfully.\n", 27);
}

static int	send_byte(unsigned char message_byte)
{
	int	i;

	i = 8;
	while (i-- > 0)
	{
		if (((message_byte >> i) & 1) == 1)
			ft_kill(g_transmission.server_pid, SIGUSR1);
		else
			ft_kill(g_transmission.server_pid, SIGUSR2);
		usleep(SIGNAL_TIMEOUT_MS / 2);
		usleep(SIGNAL_TIMEOUT_MS / 2);
	}
	return (0);
}

static int	get_and_check_args(int ac, char **av)
{
	int	error;

	if (ac != 3)
		error_cleanup("Usage: ./client <server_pid> <message>");
	error = 1;
	g_transmission.server_pid = ft_atoi(av[1], &error);
	if (error == 1 || g_transmission.server_pid <= 0)
		error_cleanup("Invalid server PID");
	g_transmission.message = (unsigned char *)av[2];
	if (g_transmission.message == NULL || g_transmission.message[0] == '\0')
		error_cleanup("Message can't be empty");
	return (0);
}

int	main(int ac, char **av)
{
	int	i;

	ft_memset(&g_transmission, 0, sizeof(g_transmission));
	get_and_check_args(ac, av);
	write(1, "Sending message to server with PID: ", 37);
	put_process_id(g_transmission.server_pid);
	write(1, "\n", 1);
	i = 0;
	signal(SIGUSR1, get_signal);
	while (g_transmission.message[i])
		send_byte((unsigned char)g_transmission.message[i++]);
	send_byte('\0');
	return (0);
}
