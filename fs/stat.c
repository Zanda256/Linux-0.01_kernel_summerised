#include <errno.h>
#include <sys/stat.h>

#include <gia/fs.h>
#include <gia/sched.h>
#include <gia/kernel.h>
#include <asm/segment.h>

static int 
cp_stat(struct m_inode *inode, struct stat *statbuf)
{
	struct stat tmp;
	int i;

	verify_area(statbuf,sizeof (*statbuf));
	tmp.st_dev = inode->i_dev;
	tmp.st_ino = inode->i_num;
	tmp.st_mode = inode->i_mode;
	tmp.st_nlink = inode->i_nlinks;
	tmp.st_uid = inode->i_uid;
	tmp.st_gid = inode->i_gid;
	tmp.st_rdev = inode->i_zone[0];
	tmp.st_size = inode->i_size;
	tmp.st_atime = inode->i_atime;
	tmp.st_mtime = inode->i_mtime;
	tmp.st_ctime = inode->i_ctime;
	for (i = 0; i < sizeof (tmp); i++)
		put_fs_byte(((char *) &tmp)[i], &((char *) statbuf)[i]);
	return (0);
}

int 
sys_stat(char *filename, struct stat *statbuf)
{
	int i;
	struct m_inode *inode;

	if (!(inode = namei(filename)))
		return -ENOENT;
	i = cp_stat(inode, statbuf);
	iput(inode);
	return i;
}

int 
sys_lstat(char *filename, struct stat *statbuf)
{
	return sys_stat(filename, statbuf);
}

int 
sys_fstat(unsigned int fd, struct stat *statbuf)
{
	struct file *f;
	struct m_inode *inode;

	if (fd >= NR_OPEN || !(f = current->filp[fd]) || !(inode = f->f_inode))
		return -ENOENT;
	return cp_stat(inode, statbuf);
}


static int 
cp_stat64(struct m_inode *inode, struct stat64 *statbuf)
{
	struct stat64 tmp;
	int i;

	verify_area(statbuf, sizeof (*statbuf));
	tmp.st_dev = inode->i_dev;
	tmp.st_ino = inode->i_num;
	tmp.st_mode = inode->i_mode;
	tmp.st_nlink = inode->i_nlinks;
	tmp.st_uid = inode->i_uid;
	tmp.st_gid = inode->i_gid;
	tmp.st_rdev = inode->i_zone[0];
	tmp.st_size = inode->i_size;
	tmp.st_atime = inode->i_atime;
	tmp.st_mtime = inode->i_mtime;
	tmp.st_ctime = inode->i_ctime;
	for (i = 0; i < sizeof (tmp); i++)
		put_fs_byte(((char *) &tmp)[i], &((char *) statbuf)[i]);
	return (0);
}

int 
sys_stat64(char *filename, struct stat64 *statbuf)
{
	int i;
	struct m_inode *inode;

	if (!(inode = namei(filename)))
		return -ENOENT;
	i = cp_stat64(inode, statbuf);
	iput(inode);
	return i;
}

int 
sys_fstat64(unsigned int fd, struct stat64 *statbuf)
{
	struct file * f;
	struct m_inode * inode;

	if (fd >= NR_OPEN || !(f = current->filp[fd]) || !(inode = f->f_inode))
		return -ENOENT;
	return cp_stat64(inode, statbuf);
}

int 
sys_lstat64(char *filename, struct stat *statbuf)
{
	return sys_stat64(filename, (struct stat64 *)statbuf);
}

int 
sys_oldstat()
{
	printk("calling obsolete system call oldstat\n");
	return 0;
}

int 
sys_oldfstat()
{
	printk("calling obsolete system call oldfstat\n");
	return 0;
}
