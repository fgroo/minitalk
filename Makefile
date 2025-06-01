# "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ😀🎉🚀💡abcdefghij"

CFLAGS += -Wall
CFLAGS += -Ofast
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -Wpedantic


SRC_DIR := src/
OBJ_DIR := obj/
INC_DIR := inc/
LIBFT_DIR := inc/libft/

LIBFT_A := $(LIBFT_DIR)libft.a

CPPFLAGS += -I$(LIBFT_DIR)
CPPFLAGS += -I$(INC_DIR)

LDFLAGS += -L$(LIBFT_DIR)
LDLIBS += -lft

SERVER_C_FILES := server.c
CLIENT_C_FILES := client.c

SERVER_O := $(SERVER_C_FILES:%.c=$(OBJ_DIR)%.o)
CLIENT_O := $(CLIENT_C_FILES:%.c=$(OBJ_DIR)%.o)

ALL_O := $(SERVER_O) $(CLIENT_O)

SERVER_EXE := server
CLIENT_EXE := client
ALL_EXE := $(SERVER_EXE) $(CLIENT_EXE)

.PHONY: all libft clean fclean re

all: $(ALL_EXE)

libft: $(LIBFT_A)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR) all

$(SERVER_EXE): $(SERVER_O) libft
	$(CC) $(CFLAGS) $(LDFLAGS) $(SERVER_O) $(LDLIBS) -o $@

$(CLIENT_EXE): $(CLIENT_O) libft
	$(CC) $(CFLAGS) $(LDFLAGS) $(CLIENT_O) $(LDLIBS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
$(OBJ_DIR):
	mkdir -p $@
clean:
	rm -f $(ALL_O)
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)
fclean: clean
	rm -f $(ALL_EXE)
	$(MAKE) -C $(LIBFT_DIR) fclean
re: fclean all
