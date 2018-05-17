/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 17:14:50 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/17 14:51:09 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <unistd.h>

void	ts_print_tetri_map(char *buff)
{
	write(1, buff, BUFF_SIZE);
	//ft_putstr_npr(buff);
}

void	ts_print_tetri(t_tetri *tetri, int map_size)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (i < map_size)
	{
		while (j < map_size)
		{
			while (k < 8)
			{
				if (tetri->coord[k] == i && tetri->coord[k + 1] == j)
				{
					ft_putchar(tetri->name);
					k = 15;
				}
				k += 2;
			}
			if (k == 8)
				ft_putchar('.');
			k = 0;
			j++;
		}
		ft_putchar('\n');
		i++;
		j = 0;
	}
	i = 0;
	while (i < 8)
	{
		ft_putnbr(tetri->coord[i]);
		ft_putnbr(tetri->coord[i + 1]);
		ft_putchar('\n');
		i += 2;
	}
}


void	print_tetri_color(char *map, t_tetri *tetri, int size, int pos, char *color)
{
	int i;
	char *tmp;

	i = 0;
	while (i < 8)
	{
		if (map[pos + tetri->coord[i] * (size + 1) + tetri->coord[i + 1]] == '\n')
			return;
		i += 2;
	}
	i = 0;
	tmp = ft_strdup(map);
	if ((pos + tetri->coord[6] * (size + 1) + tetri->coord[7]) < (size * (size + 1)) - 1)
	{
		if (map[pos] != tetri->name)
			put_tetri_tmp(tetri, tmp, size, pos);
		while (tmp[i])
		{
			if (tmp[i] == tetri->name)
			{
				ft_putstr(color);
				if (map[i] != '.' && map[i] != tetri->name)
					ft_putchar('#');
				else
					ft_putchar(tmp[i]);
				ft_putstr(KNRM);
			}
			else
				ft_putchar(tmp[i]);
			i++;
		}
		if (!ft_strcmp(color, KRED))
			usleep(100000);
		else
			usleep(300000);
	}
	//ft_putchar('\n');
	while (size > 0)
	{
		ft_putstr("\033[2J");
		size--;
	}
	ft_strdel(&tmp);
}

void	print_solution(char *map)
{
	ft_putstr("\033[5;32m");
	ft_putstr(map);
	ft_putstr(KNRM);
	sleep(2);
}

void	put_tetri_tmp(t_tetri *tetri, char *map, int map_len, int pos)
{
	int		i;
	int		*coord;
	char	c;

	i = 0;
	coord = tetri->coord;
	c = tetri->name;
	map[pos + coord[1] + (coord[0] * (map_len + 1))] = c;
	map[pos + coord[3] + (coord[2] * (map_len + 1))] = c;
	map[pos + coord[5] + (coord[4] * (map_len + 1))] = c;
	map[pos + coord[7] + (coord[6] * (map_len + 1))] = c;
}
