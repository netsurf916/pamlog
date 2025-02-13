all: pam_log.so

pam_log.so: src/pam_log.c
	gcc -fPIC -DPIC -shared -rdynamic -o pam_log.so src/pam_log.c

install: pam_log.so
	cp pam_log.so    /lib64/security/pam_log.so
	chown root:root  /lib64/security/pam_log.so
	chmod 755        /lib64/security/pam_log.so

uninstall:
	rm /lib64/security/pam_log.so

clean:
	-rm pam_log.so

