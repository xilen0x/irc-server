
# Nombre del ejecutable
NAME = ircserv

# Directorios
OBJS_DIR = .objs/
DEP_DIR = .dep/

# Compilador y FLAGS
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address

# Archivos fuente y cabeceras
SRC_FILES = src/main.cpp \
	src/Server.cpp \
#	src/Client.cpp \
#	src/Messageprocessing.cpp \
#	src/commands/Ping.cpp

HDR_FILES = inc/Server.hpp
#inc/Client.hpp \
	inc/commands/ICommand.hpp \
	inc/Messageprocessing.hpp \
	inc/commands/Ping.hpp \
	inc/replies.hpp \
	

# Archivos objeto
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Rutas completas de los archivos objeto y dependencias
OBJS = $(addprefix $(OBJS_DIR), $(OBJ_FILES))
DEPS = $(addprefix $(DEP_DIR), $(SRC_FILES:.cpp=.d))

# Eliminar archivos
RM = rm -rf

# Colores
GREEN = \033[0;32m
RESET = \033[0m

# Regla por defecto
all: $(NAME)

# Regla de limpieza
clean:
	@echo "▶ Cleaning object files and dependencies..."
	@$(RM) $(OBJS_DIR) $(DEP_DIR)

# Regla de limpieza completa
fclean: clean
	@echo "▶ Cleaning executable..."
	@$(RM) $(NAME)

# Regla para reconstruir todo
re: fclean all

# Regla para crear los directorios
$(OBJS_DIR) $(DEP_DIR):
	@mkdir -p $@

# Regla para compilar archivos fuente en archivos objeto
$(OBJS_DIR)%.o: %.cpp $(HDR_FILES) Makefile | $(OBJS_DIR) $(DEP_DIR)
	@mkdir -p $(dir $@)
	@echo "▶ Compiling... $<"
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@
	@mv $(OBJS_DIR)$*.d $(DEP_DIR)

# Regla para crear el ejecutable
$(NAME): $(OBJS) Makefile
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $@
	@echo "$(GREEN)▉▉▉▉▉▉▉▉▉▉ ircserv project successfully compiled! ▉▉▉▉▉▉▉▉▉▉$(RESET)"

# Incluye archivos de dependencias si existen
-include $(DEPS)

# Objetivos PHONY
.PHONY: all clean fclean re
