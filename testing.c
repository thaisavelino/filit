/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 17:14:50 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/10 20:27:28 by bopopovi         ###   ########.fr       */
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
	ft_putnbr(tetri->height);
	ft_putchar(' ');
	ft_putnbr(tetri->length);
	ft_putchar('\n');
	ft_putnbr(tetri->smallest_x);
	ft_putchar(' ');
	ft_putnbr(tetri->smallest_y);
	ft_putchar('\n');
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
