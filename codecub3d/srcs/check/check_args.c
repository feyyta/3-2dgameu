/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:08:54 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/25 18:21:08 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int open_file(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);
    return (close (fd), 1);
}

static int check_name_map(char *map_name)
{
    int length;

    length = 0;

    while (map_name[length] != '\0')
        length++;
    if (length < 4 || map_name[length - 4] != '.' || map_name[length - 3] != 'c' ||
        map_name[length - 2] != 'u' || map_name[length - 1] != 'b')
        return (0);
    return (1);
}
int check_args(int argc, char **argv)
{
    if (argc < 2)
        return (printf("Error\nNo map provided\n"), 0);
    if (argc > 2)
        return (printf("Error\nToo many arguments\n"), 0);
    if (check_name_map(argv[1]) == 0)
        return (printf("Error\nInvalid extension, not a .cub file\n"), 0);
    if (open_file(argv[1]) == 0)
        return (printf("Error\nCould not open map file\n"), 0);
    return (1);
}