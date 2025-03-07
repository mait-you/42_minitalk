/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:34:22 by mait-you          #+#    #+#             */
/*   Updated: 2025/03/07 09:29:03 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "../libft/libft.h"
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef SIGNAL_TIMEOUT_MS
#  define SIGNAL_TIMEOUT_MS 50
# endif

typedef struct s_receiver
{
	unsigned char		current_byte;
	pid_t				client_pid;
	int					bit1_count;
	int					bit2_count;
	int					unicode_size;
	unsigned char		unicode_ptr[8];
}						t_receiver;

typedef struct s_transmission
{
	pid_t				server_pid;
	unsigned char		*message;
}						t_transmission;

void	error_cleanup(char *error_msg);
int		put_process_id(pid_t pid);
int		ft_kill(pid_t pid, int signal);

#endif