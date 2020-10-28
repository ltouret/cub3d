/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:21:07 by ltouret           #+#    #+#             */
/*   Updated: 2020/10/28 13:27:49 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/cub3d.h"
#include "mlx.h"
#include "bmp.h"
#include <fcntl.h>

static void		set_header(t_bitmap_file_header *bfh,
		t_bitmap_info_header *bih, unsigned short *bf_type, t_data *data)
{
	*bf_type = 0x4d42;
	bfh->bf_reserved1 = 0;
	bfh->bf_reserved2 = 0;
	bfh->bf_size = 2 + sizeof(t_bitmap_file_header)
		+ sizeof(t_bitmap_info_header)
		+ data->mlx.mlx_wid * data->mlx.mlx_hei * 4;
	bfh->bf_off_bits = 0x36;
	bih->bi_size = sizeof(t_bitmap_info_header);
	bih->bi_width = data->mlx.mlx_wid;
	bih->bi_height = data->mlx.mlx_hei;
	bih->bi_planes = 1;
	bih->bi_bit_count = 32;
	bih->bi_compression = 0;
	bih->bi_size_image = 0;
	bih->bi_x_pels_per_meter = 5000;
	bih->bi_y_pels_per_meter = 5000;
	bih->bi_clr_used = 0;
	bih->bi_clr_important = 0;
}

static void		set_body(int file, t_img *img, t_bitmap_info_header *bih)
{
	int				x;
	int				y;
	unsigned int	color;

	y = bih->bi_height;
	while (--y >= 0 && (x = -1))
		while (++x < bih->bi_width)
		{
			color = img->addr[bih->bi_width * y + x];
			write(file, &color, 4);
		}
}

static void		write_file(int file, t_img *img, t_data *data)
{
	t_bitmap_file_header	bfh;
	t_bitmap_info_header	bih;
	unsigned short			bf_type;

	set_header(&bfh, &bih, &bf_type, data);
	write(file, &bf_type, sizeof(bf_type));
	write(file, &bfh, sizeof(bfh));
	write(file, &bih, sizeof(bih));
	set_body(file, img, &bih);
}

int				save_bmp(t_data *data)
{
	int		file;
	t_img	*img;
	int		ret_code;

	if ((ret_code = fill_image(data, &img)) != OK)
		return (ret_code);
	if (!(file = open("save.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666)))
		return (ERR_WRI_BMP);
	write_file(file, img, data);
	close(file);
	mlx_destroy_image(data->mlx.mlx, img->img);
	free(img);
	return (OK);
}
