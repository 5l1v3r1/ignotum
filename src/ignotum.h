#ifndef _IGNOTUM_H
#define _IGNOTUM_H 1

/* information macros */
#define IGNOTUM_VERSION "0.2"

/* initialization macros */
#define DEFAULT_IGNOTUM_MEMSEARCH (struct ignotum_search){ 0, NULL }

#include <stddef.h>
#include <sys/types.h>

typedef struct ignotum_maplist {
    size_t len;
    struct ignotum_mapinfo *maps;
} ignotum_maplist_t;

typedef struct ignotum_mapinfo {
    off_t start_addr;
    off_t end_addr;
    unsigned char perms[5];
    unsigned char is_x;
    unsigned char is_w;
    unsigned char is_r;
    off_t offset;
    dev_t st_dev;
    ino_t st_ino;
    char *pathname;
} ignotum_mapinfo_t;

typedef struct ignotum_search {
    size_t len;
    off_t *addrs;
} ignotum_search_t;

ssize_t ignotum_getmaplist(ignotum_maplist_t *list, pid_t pid);
int ignotum_getmapbyaddr(ignotum_mapinfo_t *out, pid_t pid, off_t addr);
int ignotum_getbasemap(ignotum_mapinfo_t *out, pid_t pid, const char *filename, int wildcard);

ssize_t ignotum_mem_write(pid_t pid, const void *buf, size_t n, off_t addr);
ssize_t ignotum_mem_read(pid_t pid, void *buf, size_t n, off_t addr);

ssize_t ignotum_ptrace_write(pid_t pid, const void *buf, size_t n, long addr);
ssize_t ignotum_ptrace_read(pid_t pid, void *buf, size_t n, long addr);

size_t ignotum_search(ignotum_search_t *out, off_t remote_addr, const void *haystack, size_t hlen, const void *needle, size_t nlen);

void free_ignotum_maplist(ignotum_maplist_t *);
void free_ignotum_search(ignotum_search_t *);


#endif /* _IGNOTUM_H */
