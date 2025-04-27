/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 02:21:14 by juan-jof          #+#    #+#             */
/*   Updated: 2025/04/27 23:12:22 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	g_char = 0;
static int	g_bit_count = 0;

void	handle_signal(int signum)
{
	if (signum == SIGUSR1)
		g_char = g_char << 1;
	else if (signum == SIGUSR2)
		g_char = (g_char << 1) | 1;
	g_bit_count++;
	if (g_bit_count == 8)
	{
		write(1, &g_char, 1);
		g_char = 0;
		g_bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
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
