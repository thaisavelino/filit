/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:35:00 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/09 17:12:43 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>

int		main(int ac, char **av)
{
	t_tetri *test;
	int		map_size;

	test = NULL;
	map_size = 2;
	if (ac == 2)
	{
		if (set_list_if_valid_input(av[1], &test) <= 0)
			ft_putstr("error\n");
		else
			ft_putstr("Success\n");
	}
	while (try_next(test, test, 4) != -1)
		ts_print_tetri(test, 4);
	tetri_del(&test);
	//else
	//	PRINT_USAGE
	//ft_strdel(&tmp);
	return (0);
}

int		solver(t_tetri *begin, t_tetri *ptr, int map_size)
{
	if (ptr != NULL)
	{
		if (!conflict(begin, ptr, map_size))
		{
			if (solver(begin, ptr->next, map_size) == 0)
				try_next(begin, ptr, map_size);
		}
		else if (try_next(begin, ptr, map_size))
		{
			solver(begin, ptr, map_size);
		}
		return (0);
	}
	return (1);
}

int		conflict(t_tetri *begin, t_tetri *current, int map_size)
{
	t_tetri *ptr;
	int i;
	int j;

	ptr = begin;
	i = 0;
	j = 0;
	while (i < 8)
	{
		if (current->coord[i] == map_size)
			return (1);
		i++;
	}
	i = 0;
	if (begin == current)
		return (0);
	else
	{
		while (ptr != current)
		{
			while (i < 8)
			{
				while (j < 8)
				{
					if (ptr->coord[j] == current->coord[i] && ptr->coord[j + 1] == current->coord[i + 1])
						return (1);
					j += 2;
				}
				j = 0;
				i += 2;
			}
			ptr = ptr->next;
			i = 0;
			j = 0;
		}
	}
	return (0);
}

int		try_next(t_tetri *begin, t_tetri *current, int map_size)
{
	int i;

	(void)begin;

	i = 0;
	if (current->length >= map_size && current->height < map_size)
	{
		reset_y_pos(current);
		while (i < 8)
		{
			current->coord[i] += 1;
			i += 2;
		}
		current->length = 2;
		current->height++;
		return (1);
	}
	else if (current->length < map_size)
	{
		while (i < 8)
		{
			current->coord[i + 1]++;
			i += 2;
		}
		current->length++;
		return (1);
	}
	return (-1);
}

void	reset_y_pos(t_tetri *tetri)
{
	int i;
	int tmp;

	i = 1;
	tmp = tetri->coord[1];
	while (i < 8)
	{
		if (tetri->coord[i] < tmp)
			tmp = tetri->coord[i];
		i += 2;
	}
	i = 1;
	while (i < 8)
	{
		tetri->coord[i] -= tmp;
		i += 2;
	}
}
