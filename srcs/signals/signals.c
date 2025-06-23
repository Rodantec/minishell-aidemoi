/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkiloul <lkiloul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:00:00 by lkiloul           #+#    #+#             */
/*   Updated: 2025/05/21 12:00:00 by lkiloul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	g_global.signal_received = SIGINT;
	if (g_global.shell_status == 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.signal_received = 0;
	}
	else if (g_global.child_pid > 0)
	{
		kill(g_global.child_pid, SIGINT);
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	sigquit_handler(int sig)
{
	(void)sig;
	g_global.signal_received = SIGQUIT;
	if (g_global.shell_status == 0)
		return ;
	else if (g_global.child_pid > 0)
	{
		kill(g_global.child_pid, SIGQUIT);
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	}
}

void	sigtstp_handler(int sig)
{
	(void)sig;
	if (g_global.shell_status == 0)
		return ;
	else if (g_global.child_pid > 0)
		kill(g_global.child_pid, SIGTSTP);
}

void	setup_interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_tstp;

	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sa_tstp.sa_handler = SIG_IGN;
	sa_tstp.sa_flags = 0;
	sigemptyset(&sa_tstp.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
	sigaction(SIGTSTP, &sa_tstp, NULL);
}

void	setup_child_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_tstp;

	sa_int.sa_handler = SIG_DFL;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sa_quit.sa_handler = SIG_DFL;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sa_tstp.sa_handler = SIG_DFL;
	sa_tstp.sa_flags = 0;
	sigemptyset(&sa_tstp.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
	sigaction(SIGTSTP, &sa_tstp, NULL);
}

void	setup_execution_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_tstp;

	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sa_quit.sa_handler = sigquit_handler;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	sa_tstp.sa_handler = sigtstp_handler;
	sa_tstp.sa_flags = SA_RESTART;
	sigemptyset(&sa_tstp.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
	sigaction(SIGTSTP, &sa_tstp, NULL);
}
