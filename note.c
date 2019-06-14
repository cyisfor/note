#include <stdio.h>
#include <stdlib.h> // abort, getenv
#include <stdarg.h> // va_*


static void note(const char* how, int hlen,
								 const char* file, int flen,
								 int line, const char* fmt, va_list arg) {
	static size_t maxsourcelen = 0;
	if(getenv("plain_log") == NULL) {
		if(getenv("log_source") != NULL) {
			// eliminate common prefix between note/note.c and whatever source file it is
			const char* myfile = __FILE__;
			size_t mflen = sizeof(__FILE__)-1;
			size_t i;
			if(mflen > flen) {
				mflen = flen;
			}
			for(i=0;i<mflen;++i) {					
				if(file[i] != myfile[i]) break;
			}
			if(i != flen) {
				fwrite(file+i, flen-i, 1, stderr);
			}
			// the %d varies in size too, so it can change maxsourcelen even if flen is the same
			size_t sourcelen = flen + fprintf(stderr,":%d",line);
			if(maxsourcelen < sourcelen) {
				maxsourcelen = sourcelen;
			} else {
				int i;
				for(i=0;i<maxsourcelen-sourcelen;++i) {
					fputc(' ', stderr);
				}
			}
			fputc(' ', stderr);
		}

		fwrite(how, hlen, 1, stderr);
		fputc(' ', stderr);
	}
	vfprintf(stderr,fmt,arg);
	va_end(arg);
	fputc('\n',stderr);
}

#define BODY(name)														\
	va_list arg;														\
	va_start(arg, fmt);													\
	note(name,sizeof(name)-1,file,flen,line,fmt,arg);					\

#define HEAD(ident) void ident ## f(const char* file, int flen, int line, const char* fmt, ...)

#define DEFINE(ident,name) HEAD(ident) {								\
		BODY(name)														\
}

DEFINE(spam,"DEBUG");
DEFINE(info,"INFO");
DEFINE(warn,"WARN");

HEAD(error) {
	BODY("ERROR");
	if(getenv("error_nonfatal")) return;
	abort();
}
