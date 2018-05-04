/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 20:20:10 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/04 20:35:05 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include "libft/libft.h"

#define BUFF_SIZE 22

typedef struct	s_tetri
{
	int *coord;
	char name;
	struct	s_tetri *next;
}				t_tetri;

/*
** PARSING
*/
t_tetri	*parse_input(char *file);
int		get_input(int fd, char buff[BUFF_SIZE]);
t_tetri	*get_tetri(char buff[BUFF_SIZE], int tetri_count);
int		*trim_offset(int *coord);
void	set_coord(int *coord, int blocks, int pos);
/*
** TOOLS
*/
void	tetri_push(t_tetri **alist, t_tetri *list);
t_tetri	*new_tetri(int *coord, char name);
void	tetri_del(t_tetri **alst);
/*
** TESTING
*/
void	ts_print_tetri_map(char *buff);
#endif
