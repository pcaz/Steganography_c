### Makefile --- 

## Author: pascaz10@debian
## Version: $Id: Makefile,v 0.0 2020/09/24 05:35:27 pascaz10 Exp $
## Keywords: 
## X-URL: 

PNGDIR = /usr/local/lib
PNGINC = -I/usr/include/png
PNGLIBd = -L$(PNGDIR) -lpng # dynamically linked, installed libpng
PNGLIBs = $(PNGDIR)/libpng.a # statically linked, installed libpng


ZDIR = /usr/lib/x86_64-linux-gnu
ZINC = -I/usr/include
ZLIBd = -L$(ZDIR) -lz			# dynamically linked against zlib
ZLIBs = $(ZDIR)/libz.a			# statically linked against zlib

#XINC = -I/usr/include			# new X distributions (X.org, etc.)
#XLIB = -L/usr/lib/x86_64-linux-gnu -lX11
XINC =
XLIB =

INCS = $(PNGINC) $(ZINC)
#$(XINC)


RLIBSd =  $(PNGLIBd) $(ZLIBd) $(XLIB) -lm
RLIBSs =  $(PNGLIBs) $(ZLIBs) $(XLIB) -lm

CC = gcc
LD = gcc
RM = rm -f


CFLAGS = -g -Wall $(INCS)
# [note that -Wall is a gcc-specific compilation flag ("most warnings on")]
# [-ansi, -pedantic and -W can also be used]


LDFLAGSd = -g $(RLIBSd)
LDFLAGSs = -g $(RLIBSs)
O = .o
E =
RPNG   = stegano

ROBJS  = stegano.o codage.o decodage.o util.o readpng.o image.o

STATIC_EXES  = stegano
#DYNAMIC_EXES = stegano

EXES = $(STATIC_EXES)
#EXES = $(DYNAMIC_EXES)


# implicit make rules -------------------------------------------------------

.c.o:
	$(CC) -c $(CFLAGS) $<


# dependencies --------------------------------------------------------------

all:	$(EXES)


$(RPNG)$(E): $(ROBJS) config.h
	$(LD) $(ROBJS) -o $@ $(LDFLAGSs)

image.o:	image.c image.h
	$(CC) -c $(CFLAGS) image.c



# maintenance ---------------------------------------------------------------

clean:
	$(RM) $(EXES) *.o


### Makefile ends here

