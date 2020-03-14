#!/usr/bin/perl
# this is needed to avoid deadlock with the fifo
STDOUT->autoflush(1);

while ($command ne "bye") {
  # do not play more than a number of commands
  # if the argument -n was not passed to blackjack
  if ($i++ == 123456789) {
    print "quit\n";
    exit;
  }
  
  # read and process the commands
  chomp($command = <STDIN>);
  
  if ($command eq "bet?") {
    print "1\n";
  } elsif ($command eq "insurance?") {
    print "no\n";
  } elsif (substr($command, 0, 5) eq "play?") {
    print "count\n";
    chomp($count = <STDIN>); # the count
    chomp($play = <STDIN>);  # again the "play?" query
    if ($count < 12) {
      print "hit\n";
    } else {
      print "stand\n";
    }
  }
}
