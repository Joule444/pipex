NAME        = pipex

LIB_DIR        = ./libft

MLX_DIR     = ./mlx

LIBFT        = ./libft/libft.a

MLX        = ./mlx/libmlx.a

SRCS        = main.c exec_cmd.c

OBJS        = ${SRCS:.c=.o}

RM        = rm -f

CC        = gcc

FLAGS        = -Wall -Werror -Wextra -g3

all        : ${NAME}

.c.o        :
		  @${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${LIBFT}    :
		  @echo "\033[35m----Building libft----"
		  @make -sC ${LIB_DIR}
		  @echo "OK"

${NAME}        : ${OBJS} ${LIBFT}
		  @echo "\033[34m----Compiling----"
		  @${CC} ${FLAGS} ${OBJS} ${FLAGS_LIB} -o ${NAME} ${LIBFT}
		  @echo "OK"

clean        :
		  @echo "\033[31m----Cleaning libft----"
		  @make clean -sC ${LIB_DIR}
		  @echo "OK"
		  @echo "\033[31m----Cleaning objects----"
		  @${RM} ${OBJS}
		  @echo "OK"

fclean        : clean
		  @echo "\033[33m----Cleaning all----"
		  @${RM} ${NAME}
		  @${RM} ${LIBFT}
		  @echo "OK"

re        : fclean all

.PHONY        : all clean fclean re
