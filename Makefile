CC = g++
FLAGS = -lglut -lGLU

gridBend: gridBend.c
	$(CC) $(FLAGS) gridBend.c -o gridBend

tesselation: tesselation.c
	$(CC) $(FLAGS) tesselation.c -o tesselation

gradation: gradation.c
	$(CC) $(FLAGS) gradation.c -o gradation

overlay: overlay.c
	$(CC) $(FLAGS) overlay.c -o overlay

triangleSpiral: triangleSpiral
	$(CC) $(FLAGS) triangleSpiral.cpp -o triangleSpiral

wideningGyre: wideningGyre.c
	$(CC) $(FLAGS) wideningGyre.c -o wideningGyre
