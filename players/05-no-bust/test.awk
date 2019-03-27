#!/usr/bin/gawk -f
/play\?/ {
  print "count";
  fflush();
  getline;
#   print $0 > "/dev/stderr";
  if ($1 > -19 && $1 < 12) {
    print "hit";
  } else {
    print "stand";
  }
  fflush();  
  getline;
}
# {
#   print "ign " $0 > "/dev/stderr"
# }
/bye/ {
  exit;
}
