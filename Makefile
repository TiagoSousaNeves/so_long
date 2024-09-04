# Nome dos arquivos das bibliotecas e do executável
LIB_NAME = so_long.a
LIB_NAME_BONUS = so_long_bonus.a
EXEC_NAME = so_long
EXEC_NAME_BONUS = so_long_bonus

LIB_FT_PRINTF = ./lib/ft_printf/ft_printf.a
LIB_MINILIBX_DIR = lib/minilibx-linux

# Diretórios de includes
INCLUDES = -Iinclude -I/usr/include -I$(LIB_MINILIBX_DIR) -Ilib/ft_printf -Ilib/get_next_line
INCLUDES_BONUS = -Ibonus/include_bonus -I/usr/include -I$(LIB_MINILIBX_DIR) -Ilib/ft_printf -Ilib/get_next_line

# Diretórios de fontes e objetos
SRC_DIR = src
SRC_DIR_BONUS = bonus/src_bonus
SRC_DIR_GNL = lib/get_next_line
OBJ_DIR = obj
OBJ_DIR_BONUS = bonus/obj_bonus

# Arquivos fonte e objeto
SRC = $(wildcard $(SRC_DIR)/*.c)
SRC_BONUS = $(wildcard $(SRC_DIR_BONUS)/*.c)
SRC_GNL = $(wildcard $(SRC_DIR_GNL)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJS_BONUS = $(patsubst $(SRC_DIR_BONUS)/%.c, $(OBJ_DIR_BONUS)/%.o, $(SRC_BONUS))
OBJS_GNL = $(patsubst $(SRC_DIR_GNL)/%.c, $(OBJ_DIR)/%.o, $(SRC_GNL))

# Comandos e flags
RM = @rm -rf
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g
MK_LIB = ar rcs

# Linkagem com as bibliotecas X11, MLX e ft_printf
MLX_FLAGS = -L$(LIB_MINILIBX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

# Regra principal
all: download $(LIB_FT_PRINTF) $(EXEC_NAME)

bonus: download $(LIB_FT_PRINTF) $(EXEC_NAME_BONUS)

# Compilar a biblioteca so_long
$(LIB_NAME): $(OBJS) $(OBJS_GNL)
	$(MK_LIB) $(LIB_NAME) $(OBJS) $(OBJS_GNL)

$(LIB_NAME_BONUS): $(OBJS_BONUS) $(OBJS_GNL)
	$(MK_LIB) $(LIB_NAME_BONUS) $(OBJS_BONUS) $(OBJS_GNL)

# Compilar o executável
$(EXEC_NAME): $(LIB_NAME)
	$(CC) $(OBJS) $(LIB_FT_PRINTF) $(LIB_NAME) $(MLX_FLAGS) $(INCLUDES) -o $(EXEC_NAME)

$(EXEC_NAME_BONUS): $(LIB_NAME_BONUS)
	$(CC) $(OBJS_BONUS) $(LIB_FT_PRINTF) $(LIB_NAME_BONUS) $(MLX_FLAGS) $(INCLUDES_BONUS) -o $(EXEC_NAME_BONUS)

# Compilar a biblioteca ft_printf
$(LIB_FT_PRINTF):
	@$(MAKE) -C lib/ft_printf

# Regra para compilar arquivos .c em .o (inclui o get_next_line)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRC_DIR_GNL)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c | $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES_BONUS)

# Criar os diretórios de objetos
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR_BONUS):
	@mkdir -p $(OBJ_DIR_BONUS)

# Regra para limpar arquivos objeto
clean:
	$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS)
	@$(MAKE) -C lib/ft_printf clean

# Regra para limpar arquivos objeto, executáveis, ft_printf e toda a pasta MiniLibX
fclean: clean
	$(RM) $(LIB_NAME) $(LIB_NAME_BONUS) $(EXEC_NAME) $(EXEC_NAME_BONUS)
	$(RM) $(LIB_MINILIBX_DIR)
	@$(MAKE) -C lib/ft_printf fclean

# Regra para recompilar tudo
re: fclean all

# Baixar e compilar a MiniLibX
download:
	@if [ ! -d "$(LIB_MINILIBX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(LIB_MINILIBX_DIR); \
	fi
	@$(MAKE) -C $(LIB_MINILIBX_DIR)

# Definir targets como phony
.PHONY: all bonus clean fclean re download

