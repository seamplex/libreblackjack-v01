LibreBlackjack is a blackjack engine that emulates a dealer, deals (digital) cards and understands plain-text commands such as `hit` or `stand`. The basic idea is that one or more players can talk to LibreBlackjack either in an interactive or in an automated way through
 
 * the standard input and/or output,
 * named pipes,
 * POSIX message queues,
 * TCP (web)sockets (using `netcat` or `gwsocket`), or
 * dynamically loaded arbitrary routines from shared objects.
  
These players can be actual human players playing in real-time through a front end (a GUI application, a web-based interface, a mobile app, etc.) or robots that implement a certain betting and playing strategy playing (i.e. card counting) as fast as possible to study and analyze game statistics. There is an internal player that reads the strategy from a text file and plays accordingly. It can also be used to play interactive ASCII blackjack.

![Interactive ASCII (actually UTF-8) blackjack](ascii.png){width=50%}
