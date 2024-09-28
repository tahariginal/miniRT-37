# SRCS
LinAlgebra	= src/linear_algebra/Mat4x4.c src/linear_algebra/Vec3_0.c src/linear_algebra/Vec3_1.c src/linear_algebra/Vec3_2.c
Renderer	= src/renderer/Camera.c src/renderer/Ray.c src/renderer/Renderer.c src/renderer/Shading.c
Parser_m	= src/parser/ft_split.c src/parser/get_next_line.c src/parser/get_next_line_utils.c src/parser/get_vec3.c src/parser/parser.c src/parser/parser_utils_0.c src/parser/parser_utils_1.c src/parser/filler_0.c src/parser/filler_1.c 
Parser_b	= src/parser/ft_split.c src/parser/get_next_line.c src/parser/get_next_line_utils.c src/parser/get_vec3.c src/parser/parser_bonus.c src/parser/parser_utils_0.c src/parser/parser_utils_1.c  src/parser/filler_0_bonus.c src/parser/filler_1_bonus.c src/parser/filler_2_bonus.c
Object_m	= src/objects/Object.c src/objects/Object_rotations.c src/objects/mandatory/Cylinder_0.c src/objects/mandatory/Cylinder_1.c src/objects/mandatory/Light.c src/objects/mandatory/Plane.c src/objects/mandatory/Sphere.c
Object_b	= ${Object_m} src/objects/bonus/Cone_bonus_0.c src/objects/bonus/Cone_bonus_1.c src/objects/bonus/Cone_cap_bonus.c src/objects/bonus/Rectangle_bonus.c
input		= src/input/input_0.c src/input/input_1.c src/input/camera.c src/input/object.c
utils		= src/utils/dynamic_arrays.c src/utils/free.c src/utils/logging.c src/utils/ft_memset.c src/utils/math_utils.c
mlx_utils	= src/mlx/mlx_utils_0.c  src/mlx/mlx_utils_1.c

SRC_m = ${LinAlgebra} ${Renderer} ${Parser_m} ${Object_m} ${input} ${utils} ${mlx_utils} src/main.c src/mlx/mlx_init.c 
OBJ_m = $(SRC_m:.c=.o)

SRC_b = ${LinAlgebra} ${Renderer} ${Parser_b} ${Object_b} ${input} ${utils} ${mlx_utils} src/main_bonus.c src/mlx/mlx_init_bonus.c 
OBJ_b = $(SRC_b:.c=.o)

# VARS
CC = cc
NAME = miniRT
NAME_b = miniRT_bonus
CFLAGS = -Iincludes -Wall -Wextra -Werror
LDFLAGS = -Lmlx_Linux -lmlx_Linux -lXext -lX11 -lm

ifeq ($(shell uname -s),Darwin)
	CFLAGS += -DINPUT_MAC
	LDFLAGS = -L. -lmlx -framework OpenGL -framework AppKit
endif

.PHONY : re be fclean clean all bonus
.SECONDARY : ${OBJ_m} ${OBJ_b}

%.o : %.c
	$(CC) $(CFLAGS) $< -c -o $@

all : ${NAME}
bonus: ${NAME_b}

clean :
	rm -f ${OBJ_m} ${OBJ_b}

fclean : clean
	rm -f $(NAME)
	rm -f $(NAME_b)

${NAME}: $(OBJ_m)
	$(CC) $(CFLAGS) $(OBJ_m) -o $(NAME) $(LDFLAGS)

 ${NAME_b}: $(OBJ_b)
	$(CC) $(CFLAGS) $(OBJ_b) -o $(NAME_b) $(LDFLAGS)

re : fclean all
be : fclean bonus