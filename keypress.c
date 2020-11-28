/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:55:42 by ltouret           #+#    #+#             */
/*   Updated: 2020/11/28 17:37:46 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/cub3d.h"
#include "mlx.h"
#include "keys.h"
#include "player_mov.h"

//TODO erase this
//this has to be in the Makefile only if at 42
#define LINUX 1

static int		active_key(t_data *data)
{
	if (data->keys[MAC_KEY_W] || data->keys[MAC_KEY_A] || data->keys[MAC_KEY_D]
		|| data->keys[MAC_KEY_S] || data->keys[MAC_KEY_UP] ||
		data->keys[MAC_KEY_DOWN] || data->keys[MAC_KEY_LEFT] ||
		data->keys[MAC_KEY_RIGHT] || data->keys[MAC_KEY_ESC])
		return (OK);
	return (ERR);
}

static int		linux_mac_keycode(int *keycode)
{
	if (*keycode == LIN_KEY_W)
		*keycode = MAC_KEY_W;
	else if (*keycode == LIN_KEY_A)
		*keycode = MAC_KEY_A;
	else if (*keycode == LIN_KEY_S)
		*keycode = MAC_KEY_S;
	else if (*keycode == LIN_KEY_D)
		*keycode = MAC_KEY_D;
	else if (*keycode == LIN_KEY_UP)
		*keycode = MAC_KEY_UP;
	else if (*keycode == LIN_KEY_DOWN)
		*keycode = MAC_KEY_DOWN;
	else if (*keycode == LIN_KEY_LEFT)
		*keycode = MAC_KEY_LEFT;
	else if (*keycode == LIN_KEY_RIGHT)
		*keycode = MAC_KEY_RIGHT;
	else if (*keycode == LIN_KEY_ESC)
		*keycode = MAC_KEY_ESC;
	return (OK);
}

int				player_movements(t_data *data)
{
	if (active_key(data))
	{
		if (data->keys[MAC_KEY_LEFT])
			rotate_player(data, ROT_LEFT);
		if (data->keys[MAC_KEY_RIGHT])
			rotate_player(data, ROT_RIGHT);
		if (data->keys[MAC_KEY_UP] || data->keys[MAC_KEY_W])
			move_player_ns(data, MOV_W);
		if (data->keys[MAC_KEY_DOWN] || data->keys[MAC_KEY_S])
			move_player_ns(data, MOV_S);
		if (data->keys[MAC_KEY_D])
			move_player_we(data, MOV_D);
		if (data->keys[MAC_KEY_A])
			move_player_we(data, MOV_A);
		create_image(data);
	}
	return (OK);
}

int				keypress(int keycode, t_data *data)
{
	if (LINUX)
		linux_mac_keycode(&keycode);
	if (keycode == MAC_KEY_ESC)
		exit_pro();
	if (keycode < 280)
		data->keys[keycode] = 1;
	return (OK);
}

int				keyrelease(int keycode, t_data *data)
{
	if (LINUX)
		linux_mac_keycode(&keycode);
	if (keycode < 280)
		data->keys[keycode] = 0;
	return (OK);
}
