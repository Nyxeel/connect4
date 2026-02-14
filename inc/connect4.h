#ifndef CONNECT4_H
# define CONNECT4_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/time.h>
# include <sys/ioctl.h>
# include "time.h"
# include "signal.h"



# include "libft/src/libft.h"
# include "defines.h"
# include "structs.h"
# include "game.h"
# include "ai.h"

extern volatile sig_atomic_t g_signal;


#endif /* CONNECT4_H */