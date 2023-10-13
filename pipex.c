/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:34:00 by ekordi            #+#    #+#             */
/*   Updated: 2023/10/13 15:54:04 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arrayofstrings(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}

char	*cmd_path(char *cmd, char **envp)
{
	char	*temp;
	char	**paths;
	int		i;
	char	*path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		temp = ft_strjoin(path, cmd);
		if (access(temp, X_OK) == 0)
		{
			// free_arrayofstrings(paths);
			// free(path);
			return (temp);
		}
		// free(temp);
		// free(path);
		i++;
	}
	ft_putstr_fd("Command not found\n", 2);
	free_arrayofstrings(paths);
	exit(1);
}

int	child(char **argv, int *p_fd, char **envp)
{
	char	**cmd;
	char	*cmdpath;
	int		fd;

	cmd = ft_split(argv[2], ' ');
	if (access(cmd[0], X_OK) == 0)
		cmdpath = cmd[0];
	else
		cmdpath = cmd_path(cmd[0], envp);
	close(p_fd[0]);
	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
	{
		perror("Error");
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
	dup2(p_fd[1], 1);
	close(p_fd[1]);
	execve(cmdpath, cmd, envp);
	// free_arrayofstrings(cmd);
	return (4);
}

void	parent(char **argv, int *p_fd, char **envp, int *status)
{
	char	**cmd;
	char	*cmdpath;
	int		fd;
	int		pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		cmd = ft_split(argv[3], ' ');
		if (access(cmd[0], X_OK) == 0)
			cmdpath = cmd[0];
		else
			cmdpath = cmd_path(cmd[0], envp);
		fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		close(p_fd[1]);
		dup2(fd, 1);
		close(fd);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		execve(cmdpath, cmd, envp);
		// free_arrayofstrings(cmd);
	}
	close(p_fd[1]);
	waitpid(pid, status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	p_fd[2];
	int	pid1;
	int	status;
	int	child_status;

	child_status = 0;
	status = 0;
	if (argc != 5)
	{
		printf("Usage: <infile> <cmd1> <cmd2> <outfile>\n");
		exit(0);
	}
	if (pipe(p_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid1 == 0)
		child(argv, p_fd, envp);
	waitpid(pid1, &status, 0);
	parent(argv, p_fd, envp, &child_status);
	if (status != 0 || child_status != 0)
		exit(1);
	system("leaks pipex");
	return (0);
}
