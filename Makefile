all: mini-shell

mini-shell: ./Source/main.o ./Source/mon_shell.o ./Source/Lire_commande.o ./Source/exec_command_rec.o  ./Source/commande_externe.o ./Source/commande_interne.o
	gcc $^ -o $@ -Wall -Werror
	rm ./Source/*.o
%.o: %.c %.h
	gcc -o $@ -c $<
