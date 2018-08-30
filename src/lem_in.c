/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 16:01:53 by otiniako          #+#    #+#             */
/*   Updated: 2018/07/30 16:01:55 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		ft_links(char *str, t_lem_in *lem, int *i, char **s)
{
	t_link	*tmp;

	if (ft_comment(str, lem))
		return (1);
	s = ft_strsplit(str, '-');
	if (s && s[0] && s[1] && !s[2])
	{
		if (!(tmp = (t_link *)malloc(sizeof(t_link))))
			return (ft_del_av(s));
		if (!(tmp->r1 = ft_get_r(s[0], lem)) || _A)
		{
			ft_memdel((void **)&tmp);
			return (ft_del_av(s));
		}
		if (ft_check_repeat(lem, tmp))
		{
			ft_memdel((void **)&tmp);
			return (ft_del_av(s) + 1);
		}
		tmp->next = lem->links;
		lem->links = tmp;
		*i = 2;
		return (ft_del_av(s) + 1);
	}
	return (ft_del_av(s));
}

int		ft_rooms(char *str, t_lem_in *lem, int *i)
{
	char	**s;
	t_room	*tmp;

	if (ft_comment(str, lem))
		return (1);
	s = ft_strsplit(str, ' ');
	if (s && s[0] && s[0][0] != 'L' && s[1] && ft_strisdigit(s[1]) && s[2] &&
	ft_strisdigit(s[2]) && !s[3])
	{
		if (!(tmp = (t_room *)malloc(sizeof(t_room))))
			return (0);
		ft_tool_1(tmp, lem, s);
		return (ft_del_av(s) + 1);
	}
	else
		return (ft_links(str, lem, i, NULL) + ft_del_av(s));
}

int		ft_nb_ant(char *str, t_lem_in *lem, int *i)
{
	int		j;

	j = -1;
	while (str && str[++j])
		if (!ft_isdigit((int)str[j]))
			return (ft_comment(str, lem));
	if ((lem->nb_ant = ft_atoi(str)) > 0)
		return (++(*i));
	return (0);
}

int		ft_add_to_l(char *str, t_lem_in *lem)
{
	static int	i = 0;

	if (i == 0)
		return (ft_nb_ant(str, lem, &i) ? 0 : 1);
	else if (i == 1)
		return (ft_rooms(str, lem, &i) ? 0 : 1);
	else
		return (ft_links(str, lem, &i, NULL) ? 0 : 1);
}

int		main(int ac, char **av)
{
	int			fd;
	char		*str;
	t_lem_in	lem;
	t_ways		*tmp1;
	t_way		*w;

	lem.rooms = NULL;
	if ((fd = ac < 2 ? 0 : open(av[1], O_RDONLY)) == -1)
		return (_ERR);
	while (get_next_line(fd, &str))
	{
		ft_printf("%s\n", str);
		if (ft_add_to_l(str, &lem))
		{
			ft_memdel((void **)&str);
			return (_ERR);
		}
		ft_memdel((void **)&str);
	}
	ft_rooms_links(&lem);
	ft_ways(&lem, -1);
	ft_printf("\n");
	ft_lem(&lem);
	ft_go(&lem);
	return (0);
}
