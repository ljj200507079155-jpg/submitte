
app: main.c utils.c
	gcc -o app main.c utils.c

.PHONY: clean
clean:
	rm -f app