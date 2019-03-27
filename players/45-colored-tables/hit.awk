BEGIN {
 for (i = 2; i < 10; i++) {
   upcard[i] = i;
 }
 upcard[10] = "T";
 upcard[11] = "A";
}
{
  if ($1 == player) {
    printf("%s  ", player);
    for (i = 2; i <= NF; i++) {
      if (upcard[i] == dealer) {
        printf("%s  ", action)
      } else {
        printf("%s  ", $i)
      }
    }
    printf("\n")
  } else {
    print $0
  }
}
