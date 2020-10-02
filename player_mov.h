/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 16:31:30 by ltouret           #+#    #+#             */
/*   Updated: 2020/10/02 17:03:48 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_MOV_H
# define PLAYER_MOV_H

# include "srcs/cub3d.h"

# define ROT_LEFT 1
# define ROT_RIGHT -1
# define MOV_W 1
# define MOV_S -1
# define MOV_D 1
# define MOV_A -1

void	rotate_player(t_data *data, int flag);
void	move_player_ns(t_data *data, int flag);
void	move_player_we(t_data *data, int flag);

#endif
