/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboeuf <eboeuf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/16 12:02:12 by eboeuf            #+#    #+#             */
/*   Updated: 2015/04/24 13:10:22 by eboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define IP "127.0.0.1"

#include "../../includes/client.h"

static void							usage(char *str)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" <addr> <port>", 2);
	exit(-1);
}

static int								create_client(char *addr, int port)
{
	int						sock;
	struct protoent			*proto;
	struct sockaddr_in		sin;

	if ((proto = getprotobyname("tcp")) == 0)
		error_display("ERROR getprotobyname");
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		error_display("ERROR socket");
	printf("socket %d is now opened in TCP/IP mode\n", sock);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	printf("Waiting for a connection to the server on %s:%d...\n", IP, port);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		error_display("ERROR connect");
	printf("Client connected with socket %d from %s:%d\n", sock, inet_ntoa(sin.sin_addr), htons(sin.sin_port));
	return (sock);
}

static int								wait_ret(int sock)
{
	char						data[4096];
	int 						ret;

	ft_bzero(data, 4096);
	if ((ret = recv(sock, data, sizeof(data), 0)) > -1)
	{
		ft_putendl(data);
		ft_bzero(data, 4096);
	}
	if (ret < 0)
		error_display("ERROR recv");
	return (1);
}

static int								ft_func(int ret, char *data, int sock)
{
	char						pwd[4096];

	getcwd(pwd, 4096);
	if ((ret = read(0, data, 1023)) > 1)
	{
		data[ret - 1] = '\0';
		if ((send(sock, data, 1023, 0)) < 0)
            error_display("ERROR send");
		else if (!ft_strncmp(data, "quit", 4))
			exit(1);
		else if (!ft_strncmp(data, "get", 3))
			ft_receive_server(sock);
		else if (!ft_strncmp(data, "put", 3))
			ft_put(data + 4, sock, pwd);
		else
		{
			wait_ret(sock);
			ft_bzero(data, 1024);
		}
	}
	return (1);
}

int								main(int ac, char **av)
{
	int						port;
	int						sock;
	int						ret;
	char					data[1024];

	ret = 0;
	if (ac != 3)
		usage(av[0]);
	port = ft_atoi(av[2]);
	if ((sock = create_client(av[1], port)) == -1)
        error_display("ERROR sock");
	while (1)
	{
		ft_putstr("\x1B[31mft_p> \x1B[0m");
		ft_func(ret, data, sock);
	}
	if (!close(sock))
		printf("the socket is now closed\n");
	return (0);
}
