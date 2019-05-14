CFLAGS = -Wall -c
EFLAGS =
EOPTION = `pkg-config --cflags --libs allegro-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_image-5.0 allegro_primitives-5.0` -lm
#EOPTION = `pkg-config --cflags --libs allegro-5.0 allegro_primitives-5.0 allegro_font-5.0 allegro_audio-5.0 allegro_ttf-5.0 allegro_image-5.0 allegro_acodec-5.0` -lm
OBJFOLD = objectfiles
SOURCE = main.cpp
OBJECT = main.o
EXC = golf

all: $(SOURCE) $(EXC)

$(EXC): $(OBJECT)
	g++ $(EFLAGS) -o $(EXC) $(OBJECT) $(EOPTION) 

$(OBJFOLD)/%.o: %.c
	g++ $(CFLAGS) $< -o $@

$(OBJFOLD)/%.o: libraries/%.c
	g++ $(CFLAGS) $< -o $@

clean:
	rm $(OBJECT)
	rm $(EXC)
