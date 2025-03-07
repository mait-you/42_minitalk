/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:22:05 by mait-you          #+#    #+#             */
/*   Updated: 2025/03/05 12:18:55 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H 
# define LIBFT_H

# include <unistd.h>
# include <limits.h>

void	*ft_memset(void *b, int c, size_t len);
int		ft_atoi(const char *str, int *error);
void	ft_putendl_fd(char *s, int fd);

#endif
