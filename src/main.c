#include <libevdev-1.0/libevdev/libevdev.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "../../usr/include/linux/input-event-codes.h"

int main()
{
    const char *dev = "/dev/input/event4"; // Substitua X pelo número do seu dispositivo

    int fd = open(dev, O_RDONLY);
    if (fd < 0)
    {
        perror("Erro ao abrir o dispositivo de entrada");
        return 1;
    }

    struct libevdev *devinfo;
    int err = libevdev_new_from_fd(fd, &devinfo);
    if (err < 0)
    {
        perror("Erro ao inicializar o libevdev");
        close(fd);
        return 1;
    }

    printf("Aguardando eventos. Pressione Ctrl+C para sair.\n");

    while (1)
    {
        struct input_event ev;
        err = libevdev_next_event(devinfo, LIBEVDEV_READ_FLAG_NORMAL, &ev);

        if (err == 0)
        {
            if (ev.type == EV_KEY && ev.value == 1)
            {
                // Tecla pressionada
                printf("Tecla pressionada: %s\n", libevdev_event_code_get_name(ev.type, ev.code));
            }
        }
        else
        {
            perror("Erro ao ler o evento");
            break;
        }
    }

    libevdev_free(devinfo);
    close(fd);

    return 0;
}
