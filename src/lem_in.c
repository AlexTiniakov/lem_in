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
			exit(_ERR("not enough memory", lem));
		if (!(tmp->r1 = ft_get_r(s[0], lem)) || _A)
		{
			ft_memdel((void **)&tmp);
			return (ft_del_av(s));
		}
		if (ft_check_repeat(lem, tmp))
		{
			ft_memdel((void **)&tmp);
			exit(_ERR("link already exists", lem));
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
		if (ft_check_name(s, lem))
			exit(_ERR("the room already exists", lem));
		if (!(tmp = (t_room *)malloc(sizeof(t_room))))
			exit(_ERR("not enough memory", lem));
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

	ft_tool_3(&lem, 0, &ac, &av);
	if ((fd = ac < 2 ? 0 : open(av[1], O_RDONLY)) == -1)
		return (_ERR("can't open or find the file", &lem));
	while (get_next_line(fd, &str))
	{
		ft_printf("%s%s", lem.q ? "" : str, lem.q ? "" : "\n");
		if (ft_add_to_l(str, &lem))
		{
			ft_memdel((void **)&str);
			return (_ERR(lem.nb_ant ? _W : "no lems", &lem));
		}
		ft_memdel((void **)&str);
	}
	if (ft_tool_3(&lem, 1, &ac, &av))
		return (0);
	ft_rooms_links(&lem);
	ft_ways(&lem, -1);
	ft_lem(&lem);
	return (ft_go(&lem) + lem.l ? _L : 0);
}
