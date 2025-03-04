/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:51:30 by mait-you          #+#    #+#             */
/*   Updated: 2025/03/04 13:12:30 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	send_byte(unsigned char message_byte, int process_id)
{
	int	i;

	i = 8;
	while (i-- > 0)
	{
		if (((message_byte >> i) & 1) == 1)
		{
			if (kill(process_id, SIGUSR1) == -1)
				error_cleanup("Failed to send signal");
		}
		else
		{
			if (kill(process_id, SIGUSR2) == -1)
				error_cleanup("Failed to send signal");
		}
		usleep(200);
		usleep(200);
	}
	return (0);
}

static int	get_and_check_args(
	int ac, char **av, char **message, int *process_id
	)
{
	int	error;

	if (ac != 3)
		error_cleanup("Usage: ./client <server_pid> <message>");
	error = 1;
	*process_id = ft_atoi(av[1], &error);
	if (error == 1 || *process_id <= 0)
		error_cleanup("Invalid server PID");
	*message = av[2];
	if (*message == NULL || **message == '\0')
		error_cleanup("Message cannot be empty");
	return (0);
}

int	main(int ac, char **av)
{
	int		process_id;
	char	*message;

	get_and_check_args(ac, av, &message, &process_id);
	write(1, "Sending message to server with PID: ", 37);
	put_process_id(process_id);
	write(1, "\n", 1);
	while (*message)
		send_byte(*message++, process_id);
	send_byte('\0', process_id);
	return (0);
}
