#include "philo_one.h"

char		*ft_strdup(const char *s)
{
	char	*new;
	int		len;

	len = ft_strlen(s);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, s, len + 1);
	return (new);
}

void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destination;
	unsigned char	*source;

	if (!dest && !src)
		return (NULL);
	destination = (unsigned char*)dest;
	source = (unsigned char*)src;
	while (n != 0)
	{
		*destination = *source;
		destination++;
		source++;
		n--;
	}
	return (dest);
}

void		ft_putnbr(int n)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(1, "-2147483648", 11);
			return ;
		}
		n = n * -1;
		ft_putchar('-');
	}
	if (n < 10)
		ft_putchar(n + 48);
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

long int	get_time(void)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}
