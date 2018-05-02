/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:05:31 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/02 20:19:33 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

t_tetri		*parse_input(char *file)
{
	char		buff[BUFF_SIZE];
	int			fd;
	int			tetri_count;
	t_tetri		*list;
	t_tetri		*tetri;

	tetri_count = 0;
	fd = open(file, O_RDONLY);
	list = NULL;
	while (get_input(fd, buff))
	{
		if (tetri_count >= 27)
			return (NULL);
		if (!(tetri = get_tetri(buff, tetri_count++)))
			return (NULL);
		tetri_push(&list, tetri);
	}
	close(fd);
	return (list);
}

t_tetri		*get_tetri(char buff[BUFF_SIZE], int tetri_count)
{
	t_tetri	*tetri;
	int		coord[8];
	int		blocks;
	int		i;

	i = 0;
	blocks = 0;
	tetri = NULL;
	while (i < 21)
	{
		if (((i && (i + 1) % 5 == 0) || i == 20))
		{
			if (buff[i] != '\n')
				return (NULL);
		}
		else if ((buff[i] && buff[i] != '.' && buff[i] != '#'))
		{
			return (NULL);
		}
		if (buff[i] == '#')
			set_coord(coord, blocks++, i);
		i++;
	}
	if (blocks != 4)
		return (NULL);
	tetri = new_tetri(coord, 'A' + tetri_count);
	return (tetri);
}

int		*set_coord(int *coord, int blocks, int pos)
{
	coord[blocks * 2] = pos / 5;
	coord[(blocks * 2) + 1] = pos % 5;
	return (coord);
}

/*
**
*/
int		get_input(int fd, char buff[BUFF_SIZE])
{
	int		bytes;

	bytes = read(fd, &(*buff), BUFF_SIZE - 1);
	buff[bytes] = '\0';
	return (bytes);
}
