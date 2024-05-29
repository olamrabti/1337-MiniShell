/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:31:30 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/29 15:08:23 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 1;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	ft_exit_status(int status)
{
	static int	exit_status;

	if (status < 0)
		return (exit_status);
	else
		exit_status = status;
	return (status);
}

void	ft_free_env(t_env **envp)
{
	t_env	*current;
	t_env	*next;

	if (envp == NULL || *envp == NULL)
		return ;
	current = *envp;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*envp = NULL;
}

void	init_data(int ac, char **av, t_data **data, char **envp)
{
	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	g_signal = 0;
	(*data) = malloc(sizeof(t_data));
	if (!(*data))
		exit(1);
	(*data)->cmd = NULL;
	(*data)->fds = NULL;
	(*data)->is_hiden = 0;
	(*data)->oldpwd = 1;
	(*data)->save = -1;
	(*data)->addr = NULL;
	(*data)->addr_env = NULL;
	(*data)->term = NULL;
	(*data)->env = ft_parce_env(envp, &(*data)->addr_env);
	ft_no_env(&(*data));
}

void	ft_clean_parsing(t_data **data, char *line)
{
	ft_lstclear(&(*data)->addr, free);
	free(line);
	ft_close_descriptors(*data);
	free((*data)->fds);
	(*data)->fds = NULL;
	g_signal = 0;
}
