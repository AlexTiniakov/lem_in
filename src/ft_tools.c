/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 22:50:51 by otiniako          #+#    #+#             */
/*   Updated: 2018/08/29 22:50:52 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void	ft_tool_1(t_room *tmp, t_lem_in *lem, char **s)
{
	tmp->name = ft_strcpy(ft_strnew(ft_strlen(s[0])), s[0]);
	tmp->x = ft_atoi(s[1]);
	tmp->y = ft_atoi(s[2]);
	tmp->next = lem->rooms;
	tmp->deep = 0;
	tmp->nb_ant = 0;
	tmp->is_ant = 0;
	tmp->checked = 0;
	lem->rooms = tmp;
	lem->begin = lem->s ? tmp : lem->begin;
	lem->end = lem->e ? tmp : lem->end;
	lem->s = 0;
	lem->e = 0;
}

void	ft_tool_2(t_way *tab, t_ways *ways, t_room *tmp)
{
	ways->way = (t_way *)malloc(sizeof(t_way));
	ways->way->room = tmp;
	tmp->is_in_way = 1;
	ways->way->next = tab;
	ways->lenght++;
}

int		ft_check_name(char **s, t_lem_in *lem)
{
	t_room *tmp;

	tmp = lem->rooms;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, s[0]) ||
		(ft_atoi(s[1]) == tmp->x && ft_atoi(s[2]) == tmp->y))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
