# Project name
NAME = philo

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRC_FILES = main.c time.c forks.c philo.c routine.c

# Object files
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Static libraries
AUX_LIB     = src/aux/lib_aux.a
PARCING_LIB = src/parcing/parcing.a

# Compiler and flags
CCFLAGS  = cc -Wall -Wextra -Werror -g
LDFLAGS  = -lreadline -lncurses
INCLUDES = -Isrc/aux -Isrc/parcing

all: $(NAME)

# Link the executable
$(NAME): $(OBJ) $(AUX_LIB) $(PARCING_LIB)
	$(CCFLAGS) $(OBJ) $(PARCING_LIB) $(AUX_LIB) $(LDFLAGS) -o $(NAME)
	@echo "Compiled $(NAME)"

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CCFLAGS) $(INCLUDES) -c $< -o $@

# Build aux static lib
$(AUX_LIB):
	@$(MAKE) -C src/aux

# Build parcing static lib
$(PARCING_LIB):
	@$(MAKE) -C src/parcing

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C src/aux clean
	$(MAKE) -C src/parcing clean

fclean: clean
	rm -f $(NAME)
	rm -f $(AUX_LIB)
	rm -f $(PARCING_LIB)
	@echo "Fully cleaned."

re: fclean all

.PHONY: all clean fclean re