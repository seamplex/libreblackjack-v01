#!/usr/bin/gawk -f
function abs(x){return ( x >= 0 ) ? x : -x } 

/bet\?/ {
  print "1";
  fflush();
}

/insurance\?/ {
  print "no";
  fflush();
}

/play\?/ {
  count = $2
  # mimic the dealer: hit until 17 (hit soft 17)
  if (abs(count) < 17 || count == -17) {   # soft hands are negative
    print "hit";
  } else {
    print "stand";
  }
  fflush();  
}

/bye/ {
  exit;
}
