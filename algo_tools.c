/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:31:07 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/10 15:23:51 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	get_next_x_position(t_tetri *tetri)
{
	int i;

	i = 0;
	reset_y_pos(tetri);
	tetri->smallest_x = tetri->coord[i] + 1;
	tetri->length = tetri->coord[i + 1];
	while (i < 8)
	{
		tetri->coord[i]++;
		if (tetri->smallest_x > tetri->coord[i])
			tetri->smallest_x = tetri->coord[i];
		if (tetri->coord[i + 1] > tetri->length)
			tetri->length = tetri->coord[i + 1];
		i += 2;
	}
	//tetri->length = get_tetri_len(tetri);
	tetri->length++;
	tetri->height++;
}

void	get_next_y_position(t_tetri *tetri)
{
	int i;

	i = 1;
	tetri->smallest_y = tetri->coord[i] + 1;
	while (i < 8)
	{
		tetri->coord[i]++;
		if (tetri->smallest_y > tetri->coord[i])
			tetri->smallest_y = tetri->coord[i];
		i += 2;
	}
	tetri->length++;
}
