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

int		ft_tool_3(t_lem_in *lem, int i, int *ac, char ***av)
{
	if (i == 0)
	{
		ft_init_lem(lem);
		i = ft_flags(lem, *ac - 1, *av + 1, 0);
		*ac -= i;
		*av += i;
		if (lem->u)
		{
			ft_printf(_U);
			if (lem->l)
				_L;
			exit(0);
		}
		return (0);
	}
	if (!lem->nb_ant)
		return (_ERR("no lems", lem));
	else if (!lem->rooms)
		return (_ERR("no rooms", lem));
	else if (!lem->begin || !lem->end)
		return (_ERR(lem->begin ? "no end room" : "no start room", lem));
	return (0);
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

int		ft_error(char *str, t_lem_in *lem)
{
	write(1, "ERROR", 5);
	if (lem->r)
		ft_printf(": %s", str);
	write(1, "\n", 1);
	if (lem->l)
		_L;
	return (1);
}