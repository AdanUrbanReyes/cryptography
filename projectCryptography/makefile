run: a.out
	./a.out 

a.out: main.o list.o signatureGAMAL.o dataEncryptionStandard.o analyzer.o counterMode.o MD5.o FileCipherWithDES.o User.o ElgamalSignature.o random.o mysql.o
	gcc main.o list.o signatureGAMAL.o dataEncryptionStandard.o analyzer.o counterMode.o MD5.o FileCipherWithDES.o User.o ElgamalSignature.o random.o mysql.o `mysql_config --cflags` `mysql_config --libs` -Wall -Werror

main.o: main.c
	gcc -c main.c -Wall -Werror 

list.o: list.c
	gcc -c list.c -Wall -Werror

signatureGAMAL.o: signatureGAMAL.c
	gcc -c signatureGAMAL.c -Wall -Werror

dataEncryptionStandard.o: dataEncryptionStandard.c
	gcc -c dataEncryptionStandard.c -Wall -Werror
	
analyzer.o: analyzer.c
	gcc -c analyzer.c -Wall -Werror

counterMode.o: counterMode.c
	gcc -c counterMode.c -Wall -Werror

MD5.o: MD5.c
	gcc -c MD5.c -Wall -Werror

FileCipherWithDES.o: FileCipherWithDES.c
	gcc -c FileCipherWithDES.c -Wall -Werror

User.o: User.c
	gcc -c User.c -Wall -Werror

ElgamalSignature.o: ElgamalSignature.c
	gcc -c ElgamalSignature.c -Wall -Werror

random.o: random.c
	gcc -c random.c -Wall -Werror

mysql.o: mysql.c
	gcc -c mysql.c `mysql_config --cflags` `mysql_config --libs` -Werror -Wall

clean:
	rm *.o a.out temporarily primeNumberAndGeneratorSelected

dependencias:
	sudo apt-get install mysql-server
	sudo apt-get install libmysqlclient-dev
