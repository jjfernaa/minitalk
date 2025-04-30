/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 02:21:14 by juan-jof          #+#    #+#             */
/*   Updated: 2025/04/30 02:07:47 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	process_char(char g_char, char *buffer, int *bufeer_index)
{
	if (g_char == '\0')
	{
		if (*bufeer_index > 0)
		{
			write (1, buffer, *bufeer_index);
			write (1, "\n", 1);
			*bufeer_index = 0;
		}
	}
	else
	{
		buffer[(*bufeer_index)++] = g_char;
		if (*bufeer_index >= 1023 || g_char == '\n')
		{
			write (1, buffer, *bufeer_index);
			*bufeer_index = 0;
		}
	}
}

void	handle_signal(int signum)
{
	static char	g_char = 0;
	static int	g_bit_count = 0;
	static char	buffer[1024] = {0};
	static int	buffer_index = 0;

	if (signum == SIGUSR1)
		g_char = g_char << 1;
	else if (signum == SIGUSR2)
		g_char = (g_char << 1) | 1;
	g_bit_count++;
	if (g_bit_count == 8)
	{
		process_char(g_char, buffer, &buffer_index);
		g_char = 0;
		g_bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error: No se pudo configurar manejador de señales\n", 2);
		return (1);
	}
	ft_putstr_fd("Servidor iniciado con PID:", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	while (1)
		pause();
	return (0);
}
