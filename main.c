/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:35:00 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/15 18:50:04 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>

int		main(int ac, char **av)
{
	t_tetri *list;
	int		map_len;
	char	*map;
	int tetri_nbr;

	list = NULL;
	tetri_nbr = 0;
	map = NULL;
	if (ac == 2)
	{
		if ((tetri_nbr = set_list_if_valid_input(av[1], &list)) <= 0)
			ft_putstr("error\n");
		else
		{
			map_len = get_min_map(tetri_nbr);
			map = create_map(map, map_len);
			while (!solver(list, map_len++, map, 0))
				map = create_map(map, map_len);
			ft_putstr(map);
			free(map);
			tetri_del(&list);
		}
	}
	//else
	//	PRINT_USAGE
	return (0);
}

int		solver(t_tetri *ptr, int map_len, char *map, int i)
{
	if (ptr != NULL)
	{
		while (i < ((map_len + 1) * map_len))
		{
			if (map[i + ptr->coord[1]] == '.')
			{
				if (!conflict(ptr, map_len, map, i))
					break;
			}
			i++;
		}
		if (i >= ((map_len + 1) * map_len))
		{
			i = 0;
			return (0);
		}
		while (solver(ptr->next, map_len, map, 0) == 0)
		{
			put_tetri(ptr, map_len, map, i);
			return (solver(ptr, map_len, map, i + 1));
		}
	}
	return (1);
}

int		get_min_map(int tetri_nbr)
{
	int map_len;

	map_len = 2;
	while (map_len * map_len < tetri_nbr * 4)
		map_len++;
	return (map_len);
}

int		conflict(t_tetri *tetri, int map_len, char *map, int pos)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (map[pos + tetri->coord[i + 1] + (tetri->coord[i] * (map_len + 1))] != '.')
			return (1);
		i += 2;
	}
	put_tetri(tetri, map_len, map, pos);
	return (0);
}

void	put_tetri(t_tetri *tetri, int map_len, char *map, int pos)
{
	char c;
	int i;

	i = 0;
	if (map[pos + tetri->coord[1] + (tetri->coord[0] * (map_len + 1))] == '.')
	{
		c = tetri->name;
		tetri->pos = pos;
	}
	else
	{
		c = '.';
		pos = tetri->pos;
		tetri->pos = 0;
	}
	map[pos + tetri->coord[1] + (tetri->coord[0] * (map_len + 1))] = c;
	map[pos + tetri->coord[3] + (tetri->coord[2] * (map_len + 1))] = c;
	map[pos + tetri->coord[5] + (tetri->coord[4] * (map_len + 1))] = c;
	map[pos + tetri->coord[7] + (tetri->coord[6] * (map_len + 1))] = c;
}
