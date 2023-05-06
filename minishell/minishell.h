/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:45:09 by osarsar           #+#    #+#             */
/*   Updated: 2023/05/06 08:15:12 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "pipex_bonus/libft/libft.h"
#include <sys/stat.h>

typedef struct s_mini
{
	int		ac;
	char	**av;
	char	**env;
	char	*cmd;
	char	*type;
	char	*input;
	char	*path;
	char	**split_path;
	char	*join;
	int		fd_in;
	int		fd_out;
	struct s_mini *next;	
}t_mini;

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}t_env;

t_mini	*ft_lstnew_1(void *content, t_mini *data);
void	ft_lstadd_back_1(t_mini **lst, t_mini *new);
t_env	*ft_lstnew_2(void *content);
void	ft_lstadd_back_2(t_env **lst, t_env *new);
char	*find_path(t_mini *data);
int		ft_execve_valid_path(t_mini *data);
void	ft_process(t_mini *data);
void	ft_execve(t_mini *data);
int		ft_strcmp(char *s1, char *s2);
void	redirection(t_mini **data);
void	ft_type(t_mini **data);
void	take_cmd(t_mini **data);
void	execution(t_mini *data, t_env *env);
void	execution_2_cmd(t_mini **data, t_mini **head);
void	execution_1_cmd(t_mini **data, t_mini **head);
t_env	*variable_environnement(t_mini *data);
#endif