# pamlog
PAM module to add logging of authentication attempts.  This can be useful to determine what kinds of attacks are being attempted.  Installing the module as listed below means it will not see valid password authentication attempts.  Also note that it's generally good practice to disable unused authentication methods.  For SSH, it's generally good practice to disable PAM and password authentication altogether to rely solely on public key authentication (using the built-in PKI can make this simple while avoiding locking yourself out so easily).

To install this PAM module, you can try `make install`, but your system may not use `/lib64/security/` for PAM modules, so be careful to find the correct location.  If you have trouble building it, make sure you have the appropriate development package for PAM installed (e.g., `pam-dev` or `pam-devel` typically).

Add the following to an appropriate PAM configuration file in `/etc/pam.d/` -- for example, `password-auth` -- in order to activate the module.  Note: this should be the last `auth` entry.
```
auth optional pam_log.so
```
At this point, you may need to reload some services or configure them to use PAM, but running `journalctl -a` will show log entries like the following:
```
Feb 13 08:44:28 [redacted] sshd-session[25703]: pam_log(sshd:auth): gabriel:[redacted]@103.139.192.113
Feb 13 08:44:50 [redacted] sshd-session[25706]: pam_log(sshd:auth): ftp_id:[redacted]@195.19.97.203
Feb 13 08:45:01 [redacted] sshd-session[25708]: pam_log(sshd:auth): newuser:[redacted]@217.182.74.135
Feb 13 08:45:12 [redacted] sshd-session[25711]: pam_log(sshd:auth): newuser:[redacted]@36.134.96.76
Feb 13 08:45:48 [redacted] sshd-session[25714]: pam_log(sshd:auth): builder:[redacted]@195.19.97.203
```
The output uses the format: `<user>:<password>@<host>` and non-printable characters are shown as hex values inside of brackets (e.g., `[0A]`).

