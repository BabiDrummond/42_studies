#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	if (file == NULL || argv == NULL || *argv == NULL
		|| (type != 'r' && type != 'w'))
		return (-1);

	int fds[2];
	int pid;
	type = (type == 'r');
	if (pipe(fds))
		return (-1);
	if ((pid = fork()) == -1)
		return (close(fds[0]), close(fds[1]), -1);
	if (pid == 0)
	{
		if (dup2(fds[type], type) == -1)
			exit(1);
		close(fds[0]);
		close(fds[1]);
		execvp(file, argv);
		exit(1);
	}
	close(fds[type]);
	return (fds[!type]);
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
