# pamlog
PAM module to add logging of authentication attempts.  This can be useful to determine what kinds of attacks are being attempted.

To install, you can try `make install`, but your system may not use `/lib64/security/` for PAM modules, so be careful to find the correct location.

To activate, add the following to an appropriate PAM configuration file in `/etc/pam.d/` -- for example, `password-auth`:
```
auth optional pam_log.so
```
At this point, you may need to reload some services or configure them to use PAM, but running `journalctl -a` will show log entries like the following:
```
Feb 13 08:44:28 [redacted] sshd-session[25703]: pam_log(sshd:auth): gabriel:[08][0A][0D][7F]IN@103.139.192.113
Feb 13 08:44:50 [redacted] sshd-session[25706]: pam_log(sshd:auth): ftp_id:[08][0A][0D][7F]IN@195.19.97.203
Feb 13 08:45:01 [redacted] sshd-session[25708]: pam_log(sshd:auth): newuser:[08][0A][0D][7F]INCO@217.182.74.135
Feb 13 08:45:12 [redacted] sshd-session[25711]: pam_log(sshd:auth): newuser:[08][0A][0D][7F]INCO@36.134.96.76
Feb 13 08:45:48 [redacted] sshd-session[25714]: pam_log(sshd:auth): builder:[08][0A][0D][7F]@195.19.97.203
```
As you can see, the output uses the format: `<user>:<password>@<host>` and non-printable charcters are shown as hex values inside of brackets (e.g., `[0A]`).

