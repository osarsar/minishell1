/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:27 by osarsar           #+#    #+#             */
/*   Updated: 2023/05/05 21:57:52 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	*creat_string(t_mini **lst, t_mini *data)
// {
// 	int		i;

// 	i = 0;
// 	while (split[i])
// 	{
// 		data = ft_lstnew_1(split[i]);
// 		ft_lstadd_back_1(lst, data);
// 		free(split[i]);
// 		i++;
// 	}
// 	return (0);
// }

int main (int ac, char **av)
{
    t_mini  *data;
    (void)ac;
    int i = 1;

    data = malloc(sizeof(t_mini));
	write(1, "-->\n", 4);
	while (av[i])
	{
		data = ft_lstnew_1(av[i]);
        printf("data = %s\n", data->cmd);
		
		ft_lstadd_back_1(&data, data);
		//free(av[i]);
		i++;
	}
    i = 1;
    while (data)
    {
        data = data->next;
    }
}
