/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:58:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/11 23:32:16 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	print_map(t_dot **map)
{
	int		y_index;
	int		x_index;

	y_index = 0;
	while (map[y_index])
	{
		x_index = 0;
		while (map[y_index][x_index].color != 0)
		{
			printf("%i,%i,%i,/%lx\n", x_index + 1, y_index + 1, map[y_index][x_index].z, map[y_index][x_index].color);
			x_index++;
		}
		printf("\n");
		y_index++;
	}
}

static t_data	init_data(int argc, char **argv)
{
	t_data	data;

	data.xy_scale = XY_SCALE;
	data.z_scale = Z_SCALE;
	data.def_color = DEF_COLOR;
	if (argc >= 3)
		data.xy_scale = ft_atoi(argv[2]);
	if (argc >= 4)
		data.z_scale = ft_atoi(argv[3]);
	if (argc == 5)
		data.def_color = my_atoh(argv[4]);
	return (data);
}

void	test_draw_dots(t_data data, t_dot **map, mlx_image_t *img)
{
	int	y_index;
	int	x_index;
	// int	y_pos;
	// int	x_pos;

	y_index = 0;
	while (y_index < data.max_y)
	{
		x_index = 0;
		while (x_index < data.max_x)
		{
			mlx_put_pixel(img, (x_index + 1) * data.xy_scale,
				(y_index + 1) * data.xy_scale, map[y_index][x_index].color);
			x_index++;
		}
		y_index++;
	}
}

void	test(t_data data, t_dot **map)
{
	size_t		width;
	size_t		height;
	mlx_t		*mlx;
	mlx_image_t	*img;

	width = data.max_x * data.xy_scale + data.xy_scale;
	height = data.max_y * data.xy_scale + data.xy_scale;
	printf("%li\n%li\n", width, height);
	mlx = mlx_init(width, height, "Test", true);
	if (!mlx)
		return ;
	img = mlx_new_image(mlx, width, height);
	if (!img)
		return ;
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		return ;
	test_draw_dots(data, map, img);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	(void) map;
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_dot	**map;

	if (argc < 2 || argc > 5)
	{
		ft_putendl_fd("Format: <filename> [XY_SCALE] [Z_SCALE] [DEF_COLOR]",
			STDERR_FILENO);
		return (1);
	}
	data = init_data(argc, argv);
	map = buil_map_arrays(argv[1], &data);
	if (map == NULL)
		return (ft_putendl_fd("Failed to read map.", STDERR_FILENO), 1);
	print_map(map);
	test(data, map);
	free_map(map, 0);
}
