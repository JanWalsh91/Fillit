/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tetri.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 15:38:14 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 14:11:35 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Takes the double array of tetriminos and the nummber of tetriminos,
** sets the values of the members of each structure and returns a list
** of t_tetriminos.
*/

t_tetrimino	*set_tetriminos(char **ts, short num)
{
	t_tetrimino	*new;
	t_pt		ref;
	short		i;

	if (!(new = ft_memalloc(sizeof(t_tetrimino) * num)))
		return (0);
	i = 0;
	while (ts[i])
	{
		get_reference(ts[i], &ref);
		//printf("T# %d: min (%d, %d) max (%d, %d)\n", i, minmax.min.x, minmax.min.y, minmax.max.x, minmax.max.y);
		new[i] = set_points(ts[i], ref);
		new[i].i = i;
		new[i].x = 0;
		new[i].y = 0;
		free(ts[i]);
		//printf("added points: (%d, %d) (%d, %d) (%d, %d) (%d, %d)\n", new[i].pts[0].x, new[i].pts[0].y, new[i].pts[1].x, new[i].pts[1].y, new[i].pts[2].x, new[i].pts[2].y, new[i].pts[3].x, new[i].pts[3].y);
		i++;
	}
	free(ts);
	return (new);
}

/*
 ** Takes a string representing a tetrimino and its minmax pts.
 ** Sets the coordinatates of its four points.
 ** Returns the tetrminino.
 */

t_tetrimino	set_points(char *t, t_pt ref)
{
	short		i;
	short		j;
	t_tetrimino	new; // in order to return a new tetri trimmed

	if (!(new.pts = ft_memalloc(sizeof(t_pt) * 4)))
		return (new);
	i = 0;
	j = 0;
	while (t[i])//i / T_WIDTH <= pts.max.y && i % T_WIDTH <= pts.max.x)
	{
		if (t[i] == CHAR_FULL) // we save coordonates of the #s in the new t
		{
			new.pts[j].x = i % T_WIDTH - ref.x;
			new.pts[j].y = i / T_WIDTH - ref.y;
			//printf("new point: (%d, %d)\n", new.pts[j].x, new.pts[j].y);
			j++;
		}
		++i;
	}
	return (new);
}

void		get_reference(char *t, t_pt *ref)
{
	short	i;

	ref->x = 100;
	ref->y = 100;
	i = 0;
	while (t[i])
	{
		if (t[i] == CHAR_FULL)
		{
			//printf("getting minmax i: %d\n", i);
			//printf("pts->min.x: %dpts->min.y: %d\n", pts->min.x, pts->min.y);
			if (ref->x > i % T_WIDTH)
				ref->x = i % T_WIDTH;
			if (ref->y > i / T_WIDTH)
				ref->y = i / T_WIDTH;
			//printf("pts->min.x: %dpts->min.y: %d\n", pts->min.x, pts->min.y);
		}
		i++;
	}
}

/* Combined in function get_reference
void		reset_pts(t_pt *min)
{
	min->x = 100;
	min->y = 100;
}
*/
