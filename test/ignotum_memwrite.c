#include <ignotum.h>

int main(void){
	static const char change_me[]="You cannot change me !!!";
	int mem_fd;

	printf("(%p) before -> %s\n", change_me, change_me);

	mem_fd = ignotum_openmem( getpid(), O_RDWR );
	ignotum_memwrite(mem_fd, (off_t)change_me, "Yes, i can\0", 11);

	printf("(%p) after  -> %s\n", change_me, change_me);

	close(mem_fd);

	return 0;

}
