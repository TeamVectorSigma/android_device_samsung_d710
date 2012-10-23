#include <string.h>
#include <sys/mount.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdarg.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>

#include <cutils/misc.h>
#include <cutils/sockets.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/mman.h>
#include <sys/atomics.h>
#include <private/android_filesystem_config.h>

extern prop_area *__system_property_area__;

static void update_prop_info(prop_info *pi, const char *value, unsigned len)
{
    pi->serial = pi->serial | 1;
    memcpy(pi->value, value, len + 1);
    pi->serial = (len << 24) | ((pi->serial + 1) & 0xffffff);
    __futex_wake(&pi->serial, INT32_MAX);
}

int main() {
	int fd;
	char b[256];
	int bc;

	mount("rootfs","/","rootfs",MS_REMOUNT|0,NULL);

	fd = open("/serial.no",O_RDONLY);
	if (fd<0)
		return 0;

	bc = read(fd, b, sizeof(b)-1);
	close(fd);
	fd = open("/default.prop", O_WRONLY|O_APPEND);
	if (fd>0){
		write(fd,"ro.serialno=",12);
		write(fd,b,bc);
	property_set("ro.serialno", bc);
		close (fd);
	}

	return 0;
}
int property_set(const char *name, const char *value)
{
    prop_area *pa;
    prop_info *pi;

    int namelen = strlen(name);
    int valuelen = strlen(value);

    if(namelen >= PROP_NAME_MAX) return -1;
    if(valuelen >= PROP_VALUE_MAX) return -1;
    if(namelen < 1) return -1;

    pi = (prop_info*) __system_property_find(name);

        /* ro.* properties may NEVER be modified once set */
        if(!strncmp(name, "ro.", 3)) return -1;

        pa = __system_property_area__;
        update_prop_info(pi, value, valuelen);
        pa->serial++;
        __futex_wake(&pa->serial, INT32_MAX);

    return 0;
}
