/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:31:58 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/31 18:01:10 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	char	*line;

	init_data(ac, av, &data, envp);
	while (1)
	{
		signal(SIGINT, ctrl_c_handler);
		signal(SIGQUIT, ctrl_c_handler);
		line = readline("MINISHELL$ ");
		if (g_signal)
			ft_exit_status(1);
		if (line == NULL)
			return (printf("exit\n"), exit(ft_exit_status(-1)), (0));
		if (*line)
			add_history(line);
		if (ms_parse(&data, line) != 1)
			if (data && data->cmd)
				execute_commands(&data);
		ft_clean_parsing(&data, line);
	}
	ft_lstclear(&data->addr_env, free);
	ft_free_env(&data->env);
	return (free(data), data = NULL, (0));
}
