function abs(v) {return v < 0 ? -v : v}
{
 ev=$1
 error=$2

 if (ev < -1)
   x=-1
 else if (ev > 1)
   x=1
 else
   x=ev
   
#  r=0.5-0.5*x
#  g=0.5+0.5*x
#  b=1-abs(x)

 pi = atan2(0, -1)
 r=cos((x+1)*pi/4)
 g=cos((x-1)*pi/4)
 b=0.4+0.2*cos(x*pi/2)

 
 if (error < 1e-6) {
   error=1e-4;
 }  

 x=-log(error)/log(10);
 prec=(x%1) ? (int(x)+1) : (x);
 
 printf("<div class=\"text-center %s\" style='background-color: rgb(%d,%d,%d)'>", (ev<0)?"text-white":"", 255*r, 255*g, 255*b);
 printf(sprintf("%%+.%df", prec-2), 1e2*ev);
 printf("(%.0g)", 10^prec * error);
 printf("</div>");
 
}
