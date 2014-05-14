mdk: mdk.c *.h
	gcc -Wall -pedantic -std=c99 -L /usr/lib/mysql -lsqlite3 -lmysqlclient -o $@ $<
.PHONY: clean

clean:
	rm -rf mdk
	
##alt: 64bit
#mdk: mdk.c *.h
#	gcc -Wall -pedantic -std=c99 -L /usr/lib64/mysql -lsqlite3 -lmysqlclient -o $@ $<
#.PHONY: clean
#
#clean:
#	rm -rf mdk
