#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	printf("Hello, World!");
	int fd;
	if (argc < 2)
	{
		printf("usage: %s <device>\n", argv[0]);
		return 1;
	}
	fd = open(argv[1], O_RDONLY);
	struct input_event ev;
	int type;
	int code;
	int value;
	while (1){
		// if ((ev.code != code) && (ev.value != value)){
		read(fd, &ev, sizeof(struct input_event));
		printf("Event.type is: %d, ", type);
		printf("key: %i, state: %i\n", code, value);
		if (ev.type == 1){
			printf("Correct type");
		}
		// }
		type = ev.type;
		code = ev.code;
		value = ev.value;
	}
}