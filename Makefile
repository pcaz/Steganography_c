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

JPGDIR = /usr/local/lib
JPGINC = -I/usr/local/include
JPGLIBd =-L$(JPGDIR) -libjpeg
JPGLIBs = $(JPGDIR)/libjpeg.a

#XINC = -I/usr/include			# new X distributions (X.org, etc.)
#XLIB = -L/usr/lib/x86_64-linux-gnu -lX11
XINC =
XLIB =

INCS = $(PNGINC) $(ZINC) $(JPGINC)
#$(XINC)


RLIBSd =  $(PNGLIBd) $(ZLIBd) $(XLIB) $(JPGLIBd) -lm
RLIBSs =  $(PNGLIBs) $(ZLIBs) $(XLIB) $(JPGLIBs) -lm

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

ROBJS  = stegano.o codage.o decodage.o util.o image_png.o readpng.o image_jpg.o

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

# take image.h into account

image_png.o:	image_png.c image_png.h
	$(CC) -c $(CFLAGS) image_png.c

image_jpg.o:	image_jpg.c image_jpg.h
	$(CC) -c $(CFLAGS) image_jpg.c




# maintenance ---------------------------------------------------------------

clean:
	$(RM) $(EXES) *.o


### Makefile ends here

