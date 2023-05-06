/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:50:16 by osarsar           #+#    #+#             */
/*   Updated: 2023/05/06 07:55:30 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*ft_lstnew_1(void *content, t_mini *data)
{
	t_mini	*a;

	a = (t_mini *)malloc(sizeof(t_mini));
	if (a == 0)
		return (NULL);
	a->cmd = content;
    a->type = "initialised";
	a->next = NULL;
	a->env = data->env;
	return (a);
}

t_env	*ft_lstnew_2(void *content)
{
	t_env	*a;

	a = (t_env *)malloc(sizeof(t_env));
	if (a == 0)
		return (NULL);
	a->line = content;
	a->next = NULL;
	return (a);
}

void	ft_lstadd_back_1(t_mini **lst, t_mini *new)
{
	t_mini	*last;

	last = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->next = NULL;
}

void	ft_lstadd_back_2(t_env **lst, t_env *new)
{
	t_env	*last;

	last = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->next = NULL;
}

char	*find_path(t_mini *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "PATH", 4))
		{
			return (data->env[i]);
		}
			i++;
	}
	return (0);
}

void	ft_execve(t_mini *data)
{
	char	**comand;
	static int i = 0;

	comand = ft_split(data->cmd, ' ');
	data->join = ft_strjoin(data->join, comand[0]);
	if (access(data->join, F_OK) == 0)
	{
		execve(data->join, comand, data->env);
		exit(0);
	}
}

int	ft_execve_valid_path(t_mini *data)
{
	int		i;

	i = 0;
	data->path = find_path(data);
	
	while (*data->path != '/')
		data->path++;
	data->split_path = ft_split(data->path, ':');
	while (data->split_path[i])
	{
		data->join = ft_strjoin(data->split_path[i], "/");
		ft_execve(data);
		i++;
	}
	printf("comand not found\n");
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t		i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}