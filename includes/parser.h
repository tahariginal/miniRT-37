/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:15:19 by msitni            #+#    #+#             */
/*   Updated: 2024/09/28 06:18:06 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "Renderer.h"
# include "dynamic_arrays.h"
# include "utils.h"
# include <fcntl.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE 42

typedef struct s_parser
{
	int		camera_count;
	int		ambient_count;
	t_darr	objects;
	t_darr	lights;
}			t_parser;

int			check_args(char *s);
int			error_in_line(char *line, int fd, size_t line_num);
char		*get_next_line(int fd);
int			parsing(t_scene *scene, char **av);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s);
int			ft_isspace(char c);
char		**ft_split(char const *s, size_t *count, int (*delim)(char));
size_t		ft_strlen(const char *s);
int			get_vec3(t_vec3 *vec3, char *str);
int			get_float(float *f, char *str);
int			is_valid_color(t_vec3 color);
int			is_normalized(t_vec3 vec);
size_t		ft_strlcpy(char *dst, const char *src, size_t sz);

int			fill_ambient(t_scene *scene, char **param, size_t count);
int			fill_light(t_parser *p, char **param, size_t count);
int			fill_camera(t_scene *scene, char **param, size_t count);
int			fill_sphere(t_parser *p, char **param, size_t count);
int			fill_plane(t_parser *p, char **param, size_t count);
int			fill_cylinder(t_parser *p, char **param, size_t count);

#endif