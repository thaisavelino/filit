/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 20:20:10 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/18 18:17:36 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include "../libft/libft.h"

#define BUFF_SIZE 21
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KCLR  "\x1B[2J"

#define KGRN_BLINK  "\x1B[5;32m"
#define SLP_CNFLCT  100000
#define SLP_VALID   300000

typedef struct	s_tetri
{
	int *coord;
	int pos;
	char name;
	struct	s_tetri *next;
}				t_tetri;

/*
** MAIN
*/
int		solve_tetri(t_tetri *list, char *map, int tetri_nbr, int display);
int		backtrack(t_tetri *ptr, char *map, int map_len, int i, int display);
int		conflict(t_tetri *tetri, char *map, int map_len, int pos);
void	put_tetri(t_tetri *tetri, char *map, int map_len, int pos);
/*
** PARSING
*/
int		set_list(char *file, t_tetri **list);
t_tetri	*get_tetri(char buff[BUFF_SIZE], int tetri_nbr);
int		read_file(int fd, char buff[BUFF_SIZE], int prev_bytes);
int		get_junctions(char *buff, int pos);
/*
** TOOLS
*/
void	tetri_push(t_tetri **alist, t_tetri *list);
t_tetri	*new_tetri(int *coord, int tetri_nbr);
void	tetri_del(t_tetri **alst);
int		*reset_tetri_position(int *coord);
char	*create_map(char *map, int size);
/*
** DISPLAY
*/
void	print_tetri_color(char *map, t_tetri *tetri, int size, int pos, char *color);
void	print_solution(char *map);
void	put_tetri_tmp(t_tetri *tetri, char *map, int map_len, int pos);

#endif
