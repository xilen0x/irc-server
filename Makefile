# Nombre del ejecutable
NAME = ircserv

# Directorios
OBJS_DIR = .objs/
DEP_DIR = .dep/

# Compilador y FLAGS
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I./inc -I./inc/commands -g -fsanitize=address

# Archivos fuente y cabeceras
SRC_FILES = src/main.cpp \
			src/Client.cpp \
			src/Channel.cpp \
			src/Messageprocessing.cpp \
			src/Server.cpp \
			src/Server_signals.cpp \
			src/serverUtils.cpp \
			src/extractParams.cpp \
			src/splitDoublePoint.cpp \
			src/split_msg.cpp \
			src/deleteRN.cpp \
			src/commands/Cap.cpp \
			src/commands/Invite.cpp \
			src/commands/Join.cpp \
			src/commands/Kick.cpp \
			src/commands/Mode.cpp \
			src/commands/Nick.cpp \
			src/commands/Pass.cpp \
			src/commands/Ping.cpp \
			src/commands/Privmsg.cpp \
			src/commands/Quit.cpp \
			src/commands/Topic.cpp \
			src/commands/User.cpp

HDR_FILES = inc/Client.hpp \
			inc/Channel.hpp \
			inc/Channel.tpp \
			inc/Messageprocessing.hpp \
			inc/Server.hpp \
			inc/serverUtils.hpp \
			inc/commands/Cap.hpp \
			inc/commands/Invite.hpp \
			inc/commands/Join.hpp \
			inc/commands/Kick.hpp \
			inc/commands/Mode.hpp \
			inc/commands/Nick.hpp \
			inc/commands/Pass.hpp \
			inc/commands/Ping.hpp \
			inc/commands/Privmsg.hpp \
			inc/commands/Quit.hpp \
			inc/commands/Topic.hpp \
			inc/commands/User.hpp \
			inc/commands/ICommand.hpp \
			inc/irc.hpp \
			inc/replies.hpp

# Archivos objeto
OBJ_FILES = $(patsubst src/%.cpp, $(OBJS_DIR)%.o, $(SRC_FILES))

# Rutas completas de los archivos de dependencias
DEPS = $(OBJ_FILES:.o=.d)

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
$(OBJS_DIR)%.o: src/%.cpp | $(OBJS_DIR) $(DEP_DIR)
	@mkdir -p $(dir $@)
	@echo "▶ Compiling... $<"
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Regla para crear el ejecutable
$(NAME): $(OBJ_FILES) Makefile
	@$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $@
	@echo "$(GREEN)▉▉▉▉▉▉▉▉▉▉ ircserv project successfully compiled! ▉▉▉▉▉▉▉▉▉▉$(RESET)"

# Incluye archivos de dependencias si existen
-include $(DEPS)

# Objetivos PHONY
.PHONY: all clean fclean re
