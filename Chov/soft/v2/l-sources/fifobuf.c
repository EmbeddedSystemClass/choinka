/**
  ******************************************************************************
  * @file    fifo.c
  * @author  Miroslaw Lach
  * @version V.1.0
  * @date    09.02.2012
  * @brief   Procedury kolejek fifo
  ******************************************************************************
  * @copyright
  *
  *
  * <h2><center>&copy; COPYRIGHT 2011 Miroslaw Lach</center></h2>
  */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "fifobuf.h"


void FlushFIFOBuf(fifobuf_t *Buf){
  Buf->FirstItemPos=0;
  Buf->Count=0;
}

void afifo_flush(afifobuf_t *buf){
	buf->count=0;
	buf->firstitempos=0;
}

char ReadFromFIFOBuf(fifobuf_t *Buf, unsigned int Pos){
  char tmp;
  Pos += Buf->FirstItemPos;
  Pos %= Buf->Length;
  tmp = Buf->BufferIn[Pos];
  return (tmp);
}


int32_t i32fio_read(int32fifo_t * buf, uint32_t Pos, int32_t item){
	Pos+=buf->firstitempos;
	Pos %= buf->length;
	return buf->items[Pos];
}

void afifo_read(afifobuf_t *buf, unsigned int Pos, void *item){
	void *tmp;
	Pos+= buf->firstitempos;
	Pos %= buf->length;
	tmp=buf->items;
	tmp+=(Pos*buf->itemlen);
	memcpy(item,tmp,buf->itemlen);
}

char afifo_to(afifobuf_t *buf, void *item, char Update){
	void *tmp;
	char Result=0;
	tmp =buf->items+(((buf->firstitempos+buf->count) % buf->length)*buf->itemlen);
	if (buf->count < buf->length){
		memcpy(tmp,item,buf->itemlen);
		(buf->count)++;
		Result=1;
	}else{
		if (Update){
			memcpy(tmp,item,buf->itemlen);
			(buf->firstitempos)++;
			buf->firstitempos %= buf->length;
			Result=1;
		}
	}
	return Result;
}

void afifo_to_update(afifobuf_t *buf, void * item){
	afifo_to(buf,item,1);
}

char afifo_to_no_update(afifobuf_t *buf, void * item){
	return afifo_to(buf,item,0);
}


char int32fifo_to(int32fifo_t *buf, int32_t item, char update){
	uint32_t pos;
	char result=0;
	pos=buf->firstitempos+buf->count;
	pos%=buf->length;
	if (buf->count<buf->length){
		buf->items[pos]=item;
		result=1;
	}else{
		if (update){
			buf->items[pos]=item;
			(buf->firstitempos)++;
			buf->firstitempos %= buf->length;
			result=1;
		}
	}
	return result;
}

char int32fifo_to_update(int32fifo_t *buf, int32_t item){
	return int32fifo_to(buf,item,1);
}

char int32fifo_to_no_update(int32fifo_t *buf, int32_t item){
	return int32fifo_to(buf,item,0);
}

char ToFIFOBuf(fifobuf_t *Buf, char Item, char Update){
//Update == 0 => when buffer is full Item is lost and the function returns 0 
//Update == 1 => when buffer is full Item is updates the oldest data item and the funtion returns 1
	char *tmp;
	char Result=0;
	tmp = Buf->BufferIn+((Buf->FirstItemPos+Buf->Count) % Buf->Length);
	if (Buf->Count<Buf->Length){
		*tmp=Item;
		(Buf->Count)++;
		Result=1;
	}else{
		if (Update){
			*tmp=Item;
			(Buf->FirstItemPos)++;
			Buf->FirstItemPos %= Buf->Length;
			Result=1;
		}
	}
	return Result;
}

void FIFOBufInit(fifobuf_t *FIFOBuf, char *Buf,unsigned int Length)
{
	FIFOBuf->BufferIn=Buf;
	FIFOBuf->Length=Length;
	FlushFIFOBuf(FIFOBuf);
}

char afifo_from(afifobuf_t *buf, void *item){
	void *tmp;
	if (buf->count>0){
		tmp=buf->items+(buf->firstitempos * buf->itemlen);
		memcpy(item,tmp,buf->itemlen);
		(buf->firstitempos)++;
		buf->firstitempos %= buf->length;
		(buf->count)--;
		return 1;
	}else{
		return 0;
	}
}

char FromFIFOBuf(fifobuf_t *Buf){
  char tmp=0;
  if (Buf->Count>0){
    tmp = Buf->BufferIn[Buf->FirstItemPos];
    (Buf->FirstItemPos)++;
    Buf->FirstItemPos %= Buf->Length;
    (Buf->Count)--;
  }
  return tmp;
}

char FIFOstrstr(fifobuf_t *buf, const char *str, unsigned int *pos){
	unsigned int i,j;
	char *c;
	unsigned int len=strlen(str);
	if (len>buf->Count)
		return 0;
	for (i = 0; i<buf->Count-len ; i++){
		for (j = 0,c = (char*)str ; i+j<buf->Count && j<len ; j++, c++){
			if (ReadFromFIFOBuf(buf,i+j) != *c){
				break;
			}
		}
		if (j==len){
			*pos=i;
			return 1;
		}
	}
	return 0;
}


