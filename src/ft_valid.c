/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 18:51:39 by otiniako          #+#    #+#             */
/*   Updated: 2018/07/30 18:51:40 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		ft_count_links(t_room *tmp, t_link *links, int j, int i)
{
	t_link *tab;

	tab = links;
	while (tab)
	{
		if (!ft_strcmp(tmp->name, tab->r1->name) ||
		!ft_strcmp(tmp->name, tab->r2->name))
		{
			if (j == 1)
				tmp->linked_to[i] = ft_strcmp(tmp->name, tab->r1->name) ?
												tab->r1 : tab->r2;
			i++;
		}
		tab = tab->next;
	}
	return (i);
}

void	ft_rooms_links(t_lem_in *lem)
{
	t_room	*tmp;

	tmp = lem->rooms;
	while (tmp)
	{
		tmp->nb_links = ft_count_links(tmp, lem->links, 0, 0);
		tmp->linked_to = (t_room **)malloc(sizeof(t_room *) * tmp->nb_links);
		ft_count_links(tmp, lem->links, 1, 0);
		tmp = tmp->next;
	}
}

int		ft_comment(char *str, t_lem_in *lem)
{
	if (str[0] == '#')
	{
		if (!ft_strcmp(str, "##start"))
			lem->s = 1;
		else if (!ft_strcmp(str, "##end"))
			lem->e = 1;
		return (1);
	}
	return (0);
}

int		ft_strisdigit(char *str)
{
	int j;

	j = -1;
	while(str && str[++j])
		if (!ft_isdigit((int)str[j]))
			return (0);
	return (1);
}

int		ft_del_av(char **s)
{
	int j;

	j = 0;
	while (s && s[j])
		ft_strdel(&s[j++]);
	free(s);
	return (0);
}

t_room		*ft_get_r(char *str, t_lem_in *lem)
{
	t_room	*tmp;

	tmp = lem->rooms;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, str)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}