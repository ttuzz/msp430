#ifndef _FIFO_
#define _FIFO_
#define FIFO_SIZE 32
#define FIFO_DIST 0

struct my_fifo{
	unsigned char buffer [FIFO_SIZE] ;
	unsigned int write_index ;
	unsigned int read_index	 ;
	unsigned int distance ;
	unsigned int fdist,fread;
};

inline unsigned char fifo_available(struct my_fifo * const fif);

inline unsigned char fifo_peek(struct my_fifo * const fif);

inline void fifo_inc(struct my_fifo * const fif);

inline unsigned char fifo_read(struct my_fifo * const fif);

inline void fifo_write(struct my_fifo * const fif, const unsigned char c);

inline void fifo_init(struct my_fifo * const fif);

inline void get_struct_indis(struct my_fifo * const fif);

inline void set_struct_indis(struct my_fifo * const fif);

#endif
