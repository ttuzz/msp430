#include "fifo.h"

inline unsigned char fifo_available(struct my_fifo * const fif) {
	return fif->distance > FIFO_DIST;
}
/*
inline unsigned char fifo_peek(struct my_fifo * const fif) {
	while (fif->distance < FIFO_DIST);
	unsigned char c = fif->buffer[fif->read_index];
	return c;
}

inline void fifo_inc(struct my_fifo * const fif) {
	fif->read_index = (fif->read_index + 1) % FIFO_SIZE;
	fif->distance--;
}
*/
//fifo read fifo_avaible kontrolunde yapilmalıdır.
inline unsigned char fifo_read(struct my_fifo * const fif) {
	unsigned char c = fif->buffer[fif->read_index];
	fif->read_index = (fif->read_index + 1) % FIFO_SIZE;
	fif->distance--;
	return c;
}

inline void fifo_write(struct my_fifo * const fif, const unsigned char c) {
	if (fif->distance < FIFO_SIZE) {
		fif->buffer[fif->write_index] = c;
		fif->write_index = (fif->write_index + 1) % FIFO_SIZE;
		fif->distance ++;
	}
}

inline void fifo_init(struct my_fifo * const fif){
	fif->write_index = 0 ;
	fif->read_index = 0 ;
	fif->distance = 0 ;
}
inline void get_fifo_index(struct my_fifo * const fif){
	fif->fread=fif->read_index  ;
	fif->fdist=fif->write_index  ;
	fif->fdist=fif->distance  ;
}
inline void set_fifo_index(struct my_fifo * const fif){
	fif->read_index =fif->fread ;
	fif->write_index =fif->fwrite ;
	fif->distance =fif->fdist ;
}
inline unsigned char fifo_check(struct my_fifo * const fif ,char * nextChar){
	j_fifo=0;
	while (fif->distance)
		{
		swap= fif->buffer[fif->read_index];fif->read_index = (fif->read_index + 1) % FIFO_SIZE;fif->distance--;
	    if(swap == nextChar[j_fifo]){
	    	while(swap == nextChar[j_fifo]){
	    		j_fifo++;
				if(nextChar[j_fifo] == '\0'){return(1);}
				swap=fif->buffer[fif->read_index];fif->read_index = (fif->read_index + 1) % FIFO_SIZE;fif->distance--;
	    	}
	    	return(0);
	    }
	}
	return(0);
}
