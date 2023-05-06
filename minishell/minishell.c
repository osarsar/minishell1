/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:11:58 by osarsar           #+#    #+#             */
/*   Updated: 2023/05/06 08:20:26 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_mini *data)
{
	int	pid;
	pid = fork();
	if (pid == 0)
		ft_execve_valid_path(data);
	wait(0);
}

void	init_struct_1(t_mini *data, int ac, char **av, char**env)
{
	data->ac = ac;
	data->av = av;
	data->env = env;
}

void take_cmd(t_mini **data)
{
	t_mini *tab;
	char **split;
	int i;
	i = 1;

	split = ft_split((*data)->input, ' ');
	(*data) = ft_lstnew_1(split[0], *data);
	while (split[i])
	{
		tab = ft_lstnew_1(split[i], *data);
		ft_lstadd_back_1(data, tab);
		// free(tab);
		i++;
	}
}

void ft_type(t_mini **data)
{
	t_mini *head;

	head = *data;
	while (head)
	{
		if (!ft_strcmp(head->cmd, "<"))
			head->type = "INPUT";
		else if (!ft_strcmp(head->cmd, ">"))
			head->type = "OUTPUT";
		else if (!ft_strcmp(head->cmd, "|"))
			head->type = "PIPE";
		else
			head->type = "COMAND";		
	  	head = head->next;
	}
}

void redirection(t_mini **data)
{
	t_mini *head;
	int		fd_in;
	int		fd_out;
	struct stat buff;

	head = *data;
	while (head)
	{
		if (!ft_strcmp(head->cmd, "<") && head->next)
		{
			if (!stat(head->next->cmd, &buff))
			{
				head->next->type = "IN";
				fd_in = open(head->next->cmd, O_RDWR | O_APPEND);
				dup2(fd_in, 0);
			}
			else
			printf("%s: No such file or directory\n", head->next->cmd);
		}
		else if (!ft_strcmp(head->cmd, ">") && head->next)
		{
			head->next->type = "OUT";
			fd_out = open(head->next->cmd, O_CREAT | O_RDWR | O_TRUNC, 0777);
			dup2(fd_out, 1);
		}
		head = head->next;
	}
}

void	ft_process(t_mini *data)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		ft_execve_valid_path(data);
	}
	wait(0);
	close(fd[1]);
	dup2(fd[0], 0);
}

void	execution_2_cmd(t_mini **data, t_mini **head)
{
	(*head)->cmd = ft_strjoin((*head)->cmd, " ");
	(*data)->cmd = ft_strjoin((*head)->cmd, (*head)->next->cmd);
	(*head) = (*head)->next;
	if ((*head)->next)
	{
		if (!ft_strcmp((*head)->next->type, "PIPE"))
		{
			(*head) = (*head)->next;
			ft_process(*data);
		}
		else
		exec_cmd(*data);
	}
	else
		exec_cmd(*data);

}

void	execution_1_cmd(t_mini **data, t_mini **head)
{
	if ((*head)->next)
	{
		if (!ft_strcmp((*head)->next->type, "PIPE"))
		{
			(*head) = (*head)->next;
			ft_process(*data);
		}
		else
			exec_cmd(*data);
	}
	else
		exec_cmd(*data);
}

void	execution(t_mini *data, t_env *env)
{
	t_mini	*head;
	t_mini	*trace;
	t_env	*head_env;
	t_env	*tab;

	head = data;
	while (head)
	{	
		if (head->next)
		{
			if (!ft_strcmp(head->type, "COMAND") && !ft_strcmp(head->next->type, "COMAND"))
			{
				// if ((!ft_strcmp(head->cmd, "export")))
				// {
				// 	tab = ft_lstnew_2(head->next->cmd);
				// 	ft_lstadd_back_2(&env, tab);
				// }
				// else
					execution_2_cmd(&data, &head);
			}
			else if (!ft_strcmp(head->type, "COMAND"))
				execution_1_cmd(&data, &head);
		}
		else
		{
			if (!ft_strcmp(head->cmd, "env"))
			{
				head_env = env;
				while (head_env)
				{
					printf("%s\n", head_env->line);
					head_env = head_env->next;
				}	
			}
			else
			{
				data->cmd = head->cmd;
				exec_cmd(data);
			}
		}
		head = head->next;
	}
}

t_env *variable_environnement(t_mini *data)
{
	t_env	*env;
	t_env	*tab;
	int i;

	i = 1;
	env = ft_lstnew_2(data->env[0]);
	while (data->env[i])
	{
		tab = ft_lstnew_2(data->env[i]);
		ft_lstadd_back_2(&env, tab);
		// free(tab);
		i++;
	}
	return(env);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	t_mini *data;
	t_mini *head;
	t_env	*env;
	int		in;
	int		out;

	data = malloc(sizeof(t_mini));
	init_struct_1(data, ac, av, envp);
	env = variable_environnement(data);
	while (1)
	{
		in = dup(0);
		out = dup(1);
		data->input = readline("minishell$");
		if (ft_strcmp(data->input, ""))
		{
			take_cmd(&data);
			ft_type(&data);
			redirection(&data);
			execution(data, env);
			// head = data;
			// while (head)
			// {
			// 	printf("%s -> %s\n", head->cmd, head->type);
			// 	head = head->next;
			// }
			dup2(in, 0);
			dup2(out, 1);
		}
	}
}
