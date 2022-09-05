all: prolific generation explorer

prolific: 
	gcc -Wall -o prolific prolific.c
generation: 
	gcc -Wall -o generation generation.c
explorer: 
	gcc -Wall -o explorer explorer.c