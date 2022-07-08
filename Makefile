# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 22:26:19 by mporras-          #+#    #+#              #
#    Updated: 2022/07/08 12:53:04 by msoler-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES		=	aaa_debug.c \
					bns/bns_expand_chars.c \
					bns/bns_logics.c \
					bns/bns_regex.c \
					bns/bns_sub_mini.c \
					bns/bns_wildcard.c \
					cmd/cmd_cd.c \
					cmd/cmd_echo.c \
					cmd/cmd_env.c \
					cmd/cmd_exit.c \
					cmd/cmd_export.c \
					cmd/cmd_null_nodes.c \
					cmd/cmd_pwd.c \
					cmd/cmd_redirs.c \
					cmd/cmd_unset.c \
					err/ms_error_handler.c \
					err/ms_error_export.c \
					err/ms_error_comands.c \
					err/ms_error_rare.c \
					err/msg_child_signals.c \
					inp/inp_bns_open_nodes.c \
					inp/inp_checker.c \
					inp/inp_directory.c \
					inp/inp_export.c \
					inp/inp_input.c \
					inp/inp_input_utl.c \
					inp/inp_open_nodes.c \
					inp/inp_parse.c \
					inp/inp_preprocess.c \
					inp/inp_redir.c \
					inp/inp_workflow.c \
					inp/inp_workflow_check.c \
					ms/ms_expand.c \
					ms/ms_expand_utl.c \
					ms/ms_main.c \
					ms/ms_process.c \
					ms/ms_signals.c \
					exe/exe_exec.c \
					exe/exe_pipes.c \
					exe/exe_exec_aux.c \
					utl/utl_args.c \
					utl/utl_cleaning.c \
					utl/utl_list.c \
					utl/utl_shlvl.c \
					utl/utl_strings.c \
					utl/utl_struct_utils.c \
					utl/utl_atoi_test.c \
					utl/utl_getpid.c \
					var/var_sort.c \
					var/var_export.c
SRCS_DIR		=	srcs
OBJS_DIR		=	obj
OBJS_SUBS		= 	obj \
					obj/bns \
					obj/cmd \
					obj/err \
					obj/exe \
					obj/inp \
					obj/ms \
					obj/utl \
					obj/var
SRCS 			=	$(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
OBJS			=	$(addprefix $(OBJS_DIR)/,$(SRCS_FILES:.c=.o))
LIB_DIR			=	lib
LIB 			=	libft.a
LEAKS			=	valgrind --leak-check=full --track-fds=yes --trace-children=yes -s -q
CC				=	gcc
RM				= 	rm -rf
CFLAGS			=	-Wall -Wextra -Werror
#INC_READLINE	=	/home/${USER}/.brew/opt/readline/include/
#LIB_READLINE	=	/home/${USER}/.brew/opt/readline/lib/
INC_READLINE	=	/Users/${USER}/.brew/opt/readline/include
LIB_READLINE	=	/Users/${USER}/.brew/opt/readline/lib/
#manuel readline
#INC_READLINE	=	/usr/local/opt/readline/include
#LIB_READLINE	=	/usr/local/opt/readline/lib
HEADER			=	minishell.h
HEADER_DIR		=	inc
NAME			=	minishell


all: $(OBJS_SUBS) libs $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIB_DIR)/$(LIB) $(CFLAGS) -L$(LIB_READLINE) -lreadline -o $(NAME)

libs:
	$(MAKE) -C ./$(LIB_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER_DIR)/$(HEADER)
	$(CC) $(CFLAGS) -I$(LIB_DIR)/inc -I$(HEADER_DIR) -I$(INC_READLINE) -c $< -o $@

$(OBJS_SUBS):
	-mkdir $(OBJS_SUBS)

clean:
	$(MAKE) -C ./$(LIB_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C ./$(LIB_DIR) fclean
	$(RM) $(NAME)
	$(RM) $(OBJS_SUBS)

leak: all
	$(LEAKS) ./$(NAME)

re:	fclean libs $(OBJS_SUBS) $(NAME)

.PHONY: all clean fclean re leak
