/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:24:13 by oumimoun          #+#    #+#             */
/*   Updated: 2024/05/29 18:03:50 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 0
# define ERROR 1

int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		execute_commands(t_data **data, char **envp);
int		ft_execute_builtin(t_list *cmd, t_data *data);
int		ft_pipex(t_data *data, char **envp, int *tab, int total);
int		ft_is_builtin(char *value);
int		ft_cd(t_list *cmd, t_env **env, t_data *data);
int		ft_pwd(t_list *cmd);
int		ft_echo(t_list *cmd);
int		ft_change_env(char *str, t_env *envp, int concat, t_data *data);
int		ft_unset(t_list *cmd, t_env **envp);
int		ft_isdigit(int d);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_close_descriptors(t_data *data);
int		ft_no_env(t_data **data);
int		ft_env(t_list *cmd, t_env **envp, t_data *data);
int		ft_export(t_list *cmd, t_env **envp, t_data *data);
int		ft_execute(t_list *cmd, t_data *data, char **envp);
int		ft_parent_wait(t_data *data, int *tab, int total);
int		ft_is_a_dir(char *str);
int		ft_atoi(char *str);
int		handle_export_argument(char *arg, t_env **env, t_data *data);
int		ft_add_to_export(char *str, t_env **env, int concat, t_addr **addr_env);
int		ft_double_check(char *str);
int		ft_export_is_valid(char *str);
int		ft_is_concat(char *str);
int		ft_is_exist_concat(char *str, t_env *envp);
int		ft_is_exist(char *str, t_env *envp, int concat);
int		ft_exit(t_list *cmd);
int		ft_is_point(char *str);
int		ft_lstsize(t_env *lst);

void	ft_handle_dir(t_list *temp, t_data *data);
void	ft_putstr_fd(char *str, int fd);
void	handle_file_descriptors(t_list *temp);
void	execute_command(t_list *temp, t_data *data, char **envp);
void	ft_handle_childs(t_list *temp, t_data *data, char **envp);
void	handle_parent_pipes(t_data *data, t_list *temp);
void	handle_pipes(t_data *data, t_list *temp);
void	free_env_node(t_env *node);
void	ft_middle_proccess(t_list *temp, t_data *data, char **envp);
void	ft_concat_export(char *str, t_env **env, t_addr **addr_env);
void	ft_create_pipe(t_list *temp, t_data *data);
void	ft_print_export(t_env **envp, int flag);
void	ft_add_to_env(t_env **env, char *key, char *value, t_addr **addr);
void	ft_print_error_execute_command(char *str);
void	ft_not_a_dir(t_list *temp, t_data *data);

int		*ft_alloc_tab(t_data *data, int *total);

void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_get_path(t_list *cmd, t_env *env, t_data *data);
char	*ft_get_cwd(char *new_path, int mode);
char	*gc_substr(char *s, unsigned int start, size_t len, t_addr **addr_env);
char	*gc_strjoin(char *s1, char *s2, t_addr **addr);
char	*ft_strjoin_export(char *s1, char *s2, t_data *data);

char	**ft_get_paths(t_env *env, t_data *data);
char	**ft_split(char const *s, char c, t_data *data);
char	**ft_join_for_execve(t_list *cmd, t_addr *addr);

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, char *src, size_t size);

t_env	*ft_sort_export(t_env **envp);

char	**convert_envp(t_env *envp, t_addr **addr_env);
char	*gc_itoa(int n, t_addr **addr);

#endif
