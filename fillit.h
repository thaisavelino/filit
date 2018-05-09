/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 20:20:10 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/09 22:33:11 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include "libft/libft.h"

#define BUFF_SIZE 21

typedef struct	s_tetri
{
	int *coord;
	int height;
	int length;
	char name;
	struct	s_tetri *next;
}				t_tetri;

/*
** PARSING
*/
int		set_list_if_valid_input(char *file, t_tetri **list);
t_tetri	*get_tetri_if_valid(char buff[BUFF_SIZE]);
int		read_file_to_buffer(int fd, char buff[BUFF_SIZE], int prev_bytes);
int		get_junctions(char *buff, int pos);
/*
** TOOLS
*/
void	tetri_push(t_tetri **alist, t_tetri *list);
t_tetri	*new_tetri(int *coord);
void	tetri_del(t_tetri **alst);
int		*reset_tetri_position(int *coord);
void	set_tetri_size(t_tetri *tetri);
/*
** TESTING
*/
void	ts_print_tetri_map(char *buff);
void	ts_print_tetri(t_tetri *tetri, int map_size);
/*
** ALGO
*/
int		solver(t_tetri *begin, t_tetri *ptr, int map_size);
int		conflict(t_tetri *begin, t_tetri *current, int map_size);
int		try_next(t_tetri *begin, t_tetri *current, int map_size);
void	reset_y_pos(t_tetri *tetri);
int		get_tetri_len(t_tetri *tetri);
int		get_tetri_height(t_tetri *tetri);
void	print_result(t_tetri *list, int map_size);
char	find_block_at_coord(t_tetri *list, int x, int y);
#endif
