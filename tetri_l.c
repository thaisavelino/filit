/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetri_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tavelino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 19:00:30 by tavelino          #+#    #+#             */
/*   Updated: 2018/05/03 19:58:16 by tavelino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*check_l_vertical_right(piece)  
{
	int	check;

	check = 0;
	if (ft_strcmp(piece, "#...\n#...\n##..\n...." == 0))
		check = 1;
	if (ft_strcmp(piece, ".#..\n.#..\n.##.\n...." == 0))
		check = 1;
	if (ft_strcmp(piece, "..#.\n..#.\n..##\n...." == 0))
		check = 1;
	if (ft_strcmp(piece, "....\n#...\n#...\n##.." == 0))
		check = 1;
	if (ft_strcmp(piece, "....\n.#..\n.#..\n.##." == 0))
		check = 1;
	if (ft_strcmp(piece, "....\n..#.\n..#.\n..##" == 0))
		check = 1;
	return ((check) ? "#...\n#...\n##.." : NULL);
}

char	*check_l_vertical_left(piece)
{
	int	check;

	check = 0;
	if (ft_strcmp(piece, "##..\n.#..\n.#..\n...." == 0))
		check = 1;
	if (ft_strcmp(piece, "....\n##..\n.#..\n.#.." == 0))
		check = 1;
	if (ft_strcmp(piece, ".##.\n..#.\n..#.\n...." == 0))
		check = 1;
	if (ft_strcmp(piece, "....\n.##.\n..#.\n..#." == 0))
		check = 1;
	if (ft_strcmp(piece, "..##\n...#\n...#\n...." == 0))
		check = 1;
	if (ft_strcmp(piece, "....\n..##\n...#\n...#" == 0))
		check = 1;
	return ((check) ? "##..\n.#..\n.#.." : NULL);
}

char	*check_l_horizontal_up(piece) 
{
	int	check;

	check = 0;
	if (ft_strcmp(piece, "#...\n###.\n....\n...." == 0))
		check = 1;
	if (ft_strcmp(piece, "....\n#...\n###.\n...." == 0))
		check = 1;
	if (ft_strcmp(piece, "....\n....\n#...\n###." == 0))
		check = 1;
	if (ft_strcmp(piece, ".#..\n.###\n....\n...." == 0))
		check = 1;
	if (ft_strcmp(piece, "....\n.#..\n.###\n...." == 0))
		check = 1;
	if (ft_strcmp(piece, "....\n....\n.#..\n.###" == 0))
		check = 1;
	return ((check) ? "#...\n###." : NULL);
}

char	*check_l_horizontal_down(piece) 
{
	int	check;

	check = 0;
	if (ft_strcmp(piece, "###.\n#...\n....\n...." == 0))
		check = 1;
	if (ft_strcmp(piece, "....\n###.\n#...\n...." == 0))
		check = 1;
	if (ft_strcmp(piece, "....\n....\n###.\n#..." == 0))
		check = 1;
	if (ft_strcmp(piece, ".###\n.#..\n....\n...." == 0))
		check = 1;
	if (ft_strcmp(piece, "....\n.###\n.#..\n...." == 0))
		check = 1;
	if (ft_strcmp(piece, "....\n....\n.###\n.#.." == 0))
		check = 1;
	return ((check) ? "###.\n#..." : NULL); 
}

char	*tetri_l(char *piece)
{
	if (check_l_vertical_right(piece) == 1)
		return (check_l_vertical_right(piece));
	if (check_l_vertical_left(piece) == 1)
		return (check_l_vertical_left(piece) ;
	if (check_l_horizontal_up(piece) == 1)
		return (check_l_horizontal_up(piece));
	if (check_l_horizontal_down(piece) == 1)
		return (check_l_horizontal_down(piece));
	return (NULL);
}
