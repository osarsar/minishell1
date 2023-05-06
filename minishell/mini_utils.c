/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:20 by osarsar           #+#    #+#             */
/*   Updated: 2023/05/05 22:51:45 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*ft_lstnew_1(void *content)
{
	t_mini	*a;

	a = (t_mini *)malloc(sizeof(t_mini));
	if (a == 0)
		return (NULL);
	a->cmd = content;
    a->type = "initialised";
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