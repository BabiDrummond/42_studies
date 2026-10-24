#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void redirect_output(const char *file, char *const argv[], int *fds)
{
	dup2(fds[1], 1);
	close(fds[0]);
	close(fds[1]);
	execvp(file, argv);
}

void redirect_input(const char *file, char *const argv[], int *fds)
{
	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);
	execvp(file, argv);
}

int	ft_popen(const char *file, char *const argv[], char type)
{
	if (file == NULL || argv == NULL || *argv == NULL
		|| (type != 'r' && type != 'w'))
		return (-1);

	int fds[2];
	if (pipe(fds) == -1)
		return (-1);
	if (fork() == 0)
	{
		if (type == 'r')
			redirect_output(file, argv, fds);
		else if (type == 'w')
			redirect_input(file, argv, fds);
		exit(0);
	}
	if (type == 'r')
	{
		close(fds[1]);
		return (fds[0]);
	}
	else
	{
		close(fds[0]);
		return (fds[1]);
	}
}

int	main()
{
	int		fd;
	char	buf = 0;
	printf("===========CMD LS===========\n");
	{
		fd = ft_popen("ls",  (char *const []){"ls", NULL}, 'r');
		while (read(fd, &buf, 1))
			printf("%c", buf);
	}
	printf("===========CMD LS & GREP===========\n");
	{
		fd = ft_popen("ls",  (char *const []){"ls", NULL}, 'r');
		dup2(fd, 0);
		fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');

		while (read(fd, &buf, 1))
			printf("%c", buf);
	}
	printf("===========CMD CAT===========\n");
	{
		fd = ft_popen("cat",  (char *const []){"cat", NULL}, 'w');
		write(fd, "batata\n", 8);
	}
	return(0);
}
