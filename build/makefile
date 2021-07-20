FLAGS = -L /lib64 
LIBS = -lpng

make:
	g++ ../src/cga/*.cpp ../src/color/*.cpp ../src/ega/*.cpp ../src/img/*.cpp ../src/graphic/*.cpp ../src/map/*.cpp ../src/t1k/*.cpp ../src/*.cpp ../src/tinyfiledialogs-master/*.c -o ud -lglut -lGLU -lGL -fpermissive `pkg-config --cflags --libs gtk+-3.0` -o ud $(FLAGS) $(LIBS)
