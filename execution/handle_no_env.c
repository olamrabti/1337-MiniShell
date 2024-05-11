/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_no_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:16:03 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/10 17:38:20 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int ft_check_path(t_env **envp)
{
    t_env *env;

    env = *envp;
    while (env)
    {
        if (ft_strcmp(env->key, "PATH") == 0)
            return (SUCCESS);
        env = env->next;
    }

    return (ERROR);
}

int ft_no_env(t_data **data)
{
    char *curr_dir;

    if (ft_check_path(&(*data)->env) == ERROR)
    {
        (*data)->is_hiden = 1;
        printf("data->is_hiden == %d\n", (*data)->is_hiden);
        curr_dir = getcwd(NULL, 0);
        if (!curr_dir)
            perror("getcwd");
        ft_add_to_env(&(*data)->env, gc_strdup("PWD", &(*data)->addr), gc_strdup(curr_dir, &(*data)->addr));
        ft_add_to_env(&(*data)->env, gc_strdup("SHLVL", &(*data)->addr), gc_strdup("1", &(*data)->addr));
        ft_add_to_env(&(*data)->env, gc_strdup("_", &(*data)->addr), gc_strdup("/usr/bin/env", &(*data)->addr));
        ft_add_to_env(&(*data)->env, gc_strdup("PATH", &(*data)->addr), gc_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin", &(*data)->addr));
    }
    
    return (SUCCESS);
}
