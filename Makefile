build:
	gcc -o rafwm main.c -lX11 -lXrandr -lXinerama -lXi -lXtst

test:
	DISPLAY=:1 ./rafwm

test-screen:
	Xephyr :1 -screen 1024x768 &

