
---
title: Derivation of the basic strategy
...

# Derivation of the basic strategy

> Difficulty: 20/100

## Quick run

Execute the `run.sh` script. It should take a minute or so:

```
$ ./run.sh
h20-2 (10 10) n=1000    s=0.634 (0.03)  d=-1.676 (0.03) h=-0.844 (0.02) stand
h20-3 (10 10) n=1000    s=0.66 (0.03)   d=-1.744 (0.03) h=-0.847 (0.02) stand
h20-4 (10 10) n=1000    s=0.65 (0.03)   d=-1.708 (0.03) h=-0.852 (0.02) stand
[...]
p2-T n=1000     y=-0.552 (0.05) n=-0.381 (0.03) no
p2-A n=1000     y=-0.565 (0.04) n=-0.543 (0.03) uncertain
p2-A n=10000    y=-0.6505 (0.01)        n=-0.5025 (0.008)       no
```

A new text file called `bs.txt` with the strategy should be created from scratch:

```
#    2  3  4  5  6  7  8  9  T  A
h20  s  s  s  s  s  s  s  s  s  s  
h19  s  s  s  s  s  s  s  s  s  s  
h18  s  s  s  s  s  s  s  s  s  s  
h17  s  s  s  s  s  s  s  s  s  s  
h16  s  s  s  s  s  h  h  h  s  h  
h15  s  s  s  s  s  h  h  h  h  h  
h14  s  s  s  s  s  h  h  h  h  h  
h13  s  s  s  s  s  h  h  h  h  h  
h12  h  h  s  s  s  h  h  h  h  h  
h11  d  d  d  d  d  d  d  d  d  d  
h10  d  d  d  d  d  d  d  d  h  h  
h9   h  d  d  d  d  h  h  h  h  h  
h8   h  h  h  h  h  h  h  h  h  h  
h7   h  h  h  h  h  h  h  h  h  h  
h6   h  h  h  h  h  h  h  h  h  h  
h5   h  h  h  h  h  h  h  h  h  h  
h4   h  h  h  h  h  h  h  h  h  h  
#    2  3  4  5  6  7  8  9  T  A
s20  s  s  s  s  s  s  s  s  s  s  
s19  s  s  s  s  d  s  s  s  s  s  
s18  d  d  d  d  d  s  s  h  h  h  
s17  h  d  d  d  d  h  h  h  h  h  
s16  h  h  d  d  d  h  h  h  h  h  
s15  h  h  d  d  d  h  h  h  h  h  
s14  h  h  h  d  d  h  h  h  h  h  
s13  h  h  h  d  d  h  h  h  h  h  
s12  h  h  h  h  d  h  h  h  h  h  
#    2  3  4  5  6  7  8  9  T  A
pA   y  y  y  y  y  y  y  y  y  y  
pT   n  n  n  n  n  n  n  n  n  n  
p9   y  y  y  y  y  n  y  y  n  n  
p8   y  y  y  y  y  y  y  y  y  y  
p7   y  y  y  y  y  y  n  n  n  n  
p6   y  y  y  y  y  n  n  n  n  n  
p5   n  n  n  n  n  n  n  n  n  n  
p4   n  n  n  y  y  n  n  n  n  n  
p3   n  y  y  y  y  y  n  n  n  n  
p2   y  y  y  y  y  y  n  n  n  n  
```

## Full table with results

The script computes the expected value of each combination

 1. Player’s hand (hard, soft and pair)
 2. Dealer upcard
 3. Hit, soft and stand (for hards and softs) and splitting or not (for pairs)
 
The results are given as the expected value in percentage with the uncertainty (one standard deviation) in the last significant digit.
 


 
<table class="table table-sm table-responsive table-hover small w-100">
 <thead>
  <tr>
   <th class="text-center" width="10%" colspan="2">Hand</th>
   <th class="text-center" width="9%">2</th>
   <th class="text-center" width="9%">3</th>
   <th class="text-center" width="9%">4</th>
   <th class="text-center" width="9%">5</th>
   <th class="text-center" width="9%">6</th>
   <th class="text-center" width="9%">7</th>
   <th class="text-center" width="9%">8</th>
   <th class="text-center" width="9%">9</th>
   <th class="text-center" width="9%">T</th>
   <th class="text-center" width="9%">A</th>
  </tr>
 </thead> 

 <tbody> 
 <tr>
  <td>h20</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center " style='background-color: rgb(69,245,128)'>+65(3)</div><div class="text-center text-white" style='background-color: rgb(253,24,111)'>-88(1)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-173(3)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(70,245,129)'>+64(3)</div><div class="text-center text-white" style='background-color: rgb(253,26,112)'>-87(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-171(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(68,245,128)'>+65(3)</div><div class="text-center text-white" style='background-color: rgb(253,28,113)'>-86(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-172(3)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(63,247,126)'>+68(3)</div><div class="text-center text-white" style='background-color: rgb(252,35,116)'>-82(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-169(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(65,246,127)'>+67(3)</div><div class="text-center text-white" style='background-color: rgb(253,31,114)'>-84(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-171(3)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(42,251,118)'>+79(3)</div><div class="text-center text-white" style='background-color: rgb(253,30,114)'>-85(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-170(3)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(42,251,118)'>+79(3)</div><div class="text-center text-white" style='background-color: rgb(252,33,115)'>-83(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-172(3)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center " style='background-color: rgb(45,250,119)'>+77(3)</div><div class="text-center text-white" style='background-color: rgb(253,29,113)'>-85(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-171(3)</div> </td>
 <!-- T -->
 <td>
<div class="text-center " style='background-color: rgb(106,231,140)'>+45(3)</div><div class="text-center text-white" style='background-color: rgb(253,24,111)'>-88(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-160(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center " style='background-color: rgb(155,201,151)'>+16(3)</div><div class="text-center text-white" style='background-color: rgb(254,19,109)'>-90(1)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-148(3)</div> </td>
</tr>
 <tr>
  <td>h19</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center " style='background-color: rgb(112,228,142)'>+42(4)</div><div class="text-center text-white" style='background-color: rgb(248,55,123)'>-72(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-142(4)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(112,228,142)'>+42(4)</div><div class="text-center text-white" style='background-color: rgb(249,52,122)'>-73(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-146(4)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(113,228,142)'>+41(4)</div><div class="text-center text-white" style='background-color: rgb(248,57,124)'>-71(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-143(4)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(105,232,140)'>+46(4)</div><div class="text-center text-white" style='background-color: rgb(248,55,123)'>-72(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-145(4)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(108,230,141)'>+44(4)</div><div class="text-center text-white" style='background-color: rgb(248,55,123)'>-72(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-146(4)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(69,245,128)'>+65(5)</div><div class="text-center text-white" style='background-color: rgb(248,55,123)'>-72(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-139(5)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(76,243,131)'>+61(4)</div><div class="text-center text-white" style='background-color: rgb(248,56,124)'>-71(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-140(4)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center " style='background-color: rgb(141,212,149)'>+25(4)</div><div class="text-center text-white" style='background-color: rgb(248,56,124)'>-71(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-146(4)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(181,179,152)'>-0(4)</div><div class="text-center text-white" style='background-color: rgb(249,50,121)'>-75(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-144(4)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(206,150,150)'>-20(3)</div><div class="text-center text-white" style='background-color: rgb(252,34,115)'>-82(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-139(3)</div> </td>
</tr>
 <tr>
  <td>h18</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center " style='background-color: rgb(157,200,151)'>+15(5)</div><div class="text-center text-white" style='background-color: rgb(243,74,130)'>-62(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-115(5)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(158,199,151)'>+15(5)</div><div class="text-center text-white" style='background-color: rgb(245,70,129)'>-64(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-117(5)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(157,200,151)'>+15(5)</div><div class="text-center text-white" style='background-color: rgb(244,71,129)'>-64(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-127(5)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(148,207,150)'>+21(5)</div><div class="text-center text-white" style='background-color: rgb(245,69,128)'>-65(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-119(5)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(141,212,149)'>+25(5)</div><div class="text-center text-white" style='background-color: rgb(246,66,127)'>-67(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-124(5)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(118,225,143)'>+38(5)</div><div class="text-center text-white" style='background-color: rgb(242,78,132)'>-60(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-118(5)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(162,196,152)'>+12(5)</div><div class="text-center text-white" style='background-color: rgb(241,80,132)'>-59(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-114(5)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(206,149,150)'>-20(5)</div><div class="text-center text-white" style='background-color: rgb(242,77,131)'>-61(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-124(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(212,140,148)'>-26(5)</div><div class="text-center text-white" style='background-color: rgb(247,61,125)'>-69(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-123(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(234,101,139)'>-48(4)</div><div class="text-center text-white" style='background-color: rgb(249,52,122)'>-73(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-124(4)</div> </td>
</tr>
 <tr>
  <td>h17</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(201,156,151)'>-16(5)</div><div class="text-center text-white" style='background-color: rgb(239,86,134)'>-56(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-113(5)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(195,163,152)'>-11(5)</div><div class="text-center text-white" style='background-color: rgb(236,94,137)'>-52(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-105(5)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(190,169,152)'>-7(5)</div><div class="text-center text-white" style='background-color: rgb(240,83,133)'>-58(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-107(5)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(190,169,152)'>-7(5)</div><div class="text-center text-white" style='background-color: rgb(236,94,137)'>-51(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-105(5)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(174,185,152)'>+4(5)</div><div class="text-center text-white" style='background-color: rgb(239,86,134)'>-56(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-108(5)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(193,166,152)'>-10(5)</div><div class="text-center text-white" style='background-color: rgb(235,98,138)'>-50(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-104(5)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(223,122,144)'>-36(5)</div><div class="text-center text-white" style='background-color: rgb(236,95,137)'>-51(3)</div><div class="text-center text-white" style='background-color: rgb(254,2,103)'>-99(5)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(229,111,142)'>-42(5)</div><div class="text-center text-white" style='background-color: rgb(238,91,136)'>-53(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-118(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(231,106,140)'>-45(5)</div><div class="text-center text-white" style='background-color: rgb(240,83,133)'>-57(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-115(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(245,67,128)'>-66(1)</div><div class="text-center text-white" style='background-color: rgb(247,60,125)'>-69.6(7)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-111(1)</div> </td>
</tr>
 <tr>
  <td>h16</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(214,137,148)'>-28(5)</div><div class="text-center text-white" style='background-color: rgb(232,104,140)'>-46(3)</div><div class="text-center text-white" style='background-color: rgb(254,13,107)'>-93(5)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(212,140,148)'>-26(6)</div><div class="text-center text-white" style='background-color: rgb(233,103,139)'>-47(3)</div><div class="text-center text-white" style='background-color: rgb(253,31,114)'>-84(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(203,153,151)'>-18(5)</div><div class="text-center text-white" style='background-color: rgb(226,117,143)'>-39(3)</div><div class="text-center text-white" style='background-color: rgb(254,3,103)'>-98(5)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(197,161,151)'>-13(5)</div><div class="text-center text-white" style='background-color: rgb(231,107,140)'>-45(3)</div><div class="text-center text-white" style='background-color: rgb(254,4,103)'>-98(5)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(202,155,151)'>-17(5)</div><div class="text-center text-white" style='background-color: rgb(234,99,138)'>-49(3)</div><div class="text-center text-white" style='background-color: rgb(254,21,110)'>-89(5)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(234,101,139)'>-48(2)</div><div class="text-center text-white" style='background-color: rgb(228,113,142)'>-41.4(9)</div><div class="text-center text-white" style='background-color: rgb(252,35,115)'>-82(2)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,93,136)'>-52(2)</div><div class="text-center text-white" style='background-color: rgb(233,103,139)'>-47.0(9)</div><div class="text-center text-white" style='background-color: rgb(254,17,109)'>-91(2)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,88,135)'>-55(2)</div><div class="text-center text-white" style='background-color: rgb(236,94,137)'>-51.8(8)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-101(2)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(240,83,133)'>-57.57(1)</div><div class="text-center text-white" style='background-color: rgb(241,83,133)'>-57.62(1)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-107.30(1)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,54,123)'>-72(1)</div><div class="text-center text-white" style='background-color: rgb(246,64,126)'>-67.6(7)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-107(1)</div> </td>
</tr>
 <tr>
  <td>h15</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(208,147,150)'>-22(5)</div><div class="text-center text-white" style='background-color: rgb(225,118,144)'>-38(3)</div><div class="text-center text-white" style='background-color: rgb(254,20,110)'>-90(5)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(212,141,149)'>-25(6)</div><div class="text-center text-white" style='background-color: rgb(229,110,141)'>-43(3)</div><div class="text-center text-white" style='background-color: rgb(251,41,118)'>-79(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(209,145,149)'>-22(6)</div><div class="text-center text-white" style='background-color: rgb(226,116,143)'>-39(3)</div><div class="text-center text-white" style='background-color: rgb(252,38,117)'>-81(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(200,157,151)'>-15(6)</div><div class="text-center text-white" style='background-color: rgb(230,110,141)'>-43(3)</div><div class="text-center text-white" style='background-color: rgb(250,45,120)'>-77(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(190,169,152)'>-8(6)</div><div class="text-center text-white" style='background-color: rgb(222,123,145)'>-35(3)</div><div class="text-center text-white" style='background-color: rgb(249,52,122)'>-74(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,93,136)'>-52(6)</div><div class="text-center text-white" style='background-color: rgb(224,120,144)'>-38(3)</div><div class="text-center text-white" style='background-color: rgb(252,35,116)'>-82(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,94,137)'>-52(2)</div><div class="text-center text-white" style='background-color: rgb(229,111,142)'>-42.4(9)</div><div class="text-center text-white" style='background-color: rgb(252,34,115)'>-83(2)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,88,135)'>-55(2)</div><div class="text-center text-white" style='background-color: rgb(233,101,139)'>-47.9(8)</div><div class="text-center text-white" style='background-color: rgb(254,12,106)'>-94(2)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,82,133)'>-58.0(5)</div><div class="text-center text-white" style='background-color: rgb(238,89,135)'>-54.5(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-101.4(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,55,123)'>-72(1)</div><div class="text-center text-white" style='background-color: rgb(246,64,127)'>-67.2(7)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-105(1)</div> </td>
</tr>
 <tr>
  <td>h14</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(215,135,148)'>-28(2)</div><div class="text-center text-white" style='background-color: rgb(223,122,145)'>-36.0(9)</div><div class="text-center text-white" style='background-color: rgb(248,57,124)'>-71(2)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(213,140,148)'>-26(2)</div><div class="text-center text-white" style='background-color: rgb(221,126,145)'>-33.8(9)</div><div class="text-center text-white" style='background-color: rgb(248,58,124)'>-70(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(206,149,150)'>-20(2)</div><div class="text-center text-white" style='background-color: rgb(219,130,146)'>-31.7(9)</div><div class="text-center text-white" style='background-color: rgb(245,68,128)'>-66(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(203,153,151)'>-18(2)</div><div class="text-center text-white" style='background-color: rgb(219,129,146)'>-32.4(9)</div><div class="text-center text-white" style='background-color: rgb(246,64,127)'>-67(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(194,164,152)'>-11(6)</div><div class="text-center text-white" style='background-color: rgb(221,127,146)'>-34(3)</div><div class="text-center text-white" style='background-color: rgb(244,71,129)'>-64(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,93,136)'>-52(6)</div><div class="text-center text-white" style='background-color: rgb(223,122,144)'>-36(3)</div><div class="text-center text-white" style='background-color: rgb(248,59,125)'>-70(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,94,137)'>-51(6)</div><div class="text-center text-white" style='background-color: rgb(229,112,142)'>-42(3)</div><div class="text-center text-white" style='background-color: rgb(249,53,122)'>-73(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,91,136)'>-53(5)</div><div class="text-center text-white" style='background-color: rgb(229,111,142)'>-42(3)</div><div class="text-center text-white" style='background-color: rgb(254,8,105)'>-96(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,81,132)'>-59(2)</div><div class="text-center text-white" style='background-color: rgb(235,97,138)'>-49.8(8)</div><div class="text-center text-white" style='background-color: rgb(254,13,107)'>-93(2)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,54,123)'>-72(1)</div><div class="text-center text-white" style='background-color: rgb(244,73,130)'>-62.9(7)</div><div class="text-center text-white" style='background-color: rgb(254,5,104)'>-97(1)</div> </td>
</tr>
 <tr>
  <td>h13</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(216,134,147)'>-29(2)</div><div class="text-center text-white" style='background-color: rgb(219,129,146)'>-32.1(9)</div><div class="text-center text-white" style='background-color: rgb(241,81,132)'>-59(2)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,141,149)'>-25(2)</div><div class="text-center text-white" style='background-color: rgb(216,134,147)'>-29.3(9)</div><div class="text-center text-white" style='background-color: rgb(240,84,133)'>-57(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(207,148,150)'>-21(2)</div><div class="text-center text-white" style='background-color: rgb(217,133,147)'>-29.9(9)</div><div class="text-center text-white" style='background-color: rgb(239,86,134)'>-56(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(203,153,151)'>-18(2)</div><div class="text-center text-white" style='background-color: rgb(213,139,148)'>-26.2(9)</div><div class="text-center text-white" style='background-color: rgb(235,96,137)'>-50(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(199,159,151)'>-14(6)</div><div class="text-center text-white" style='background-color: rgb(216,134,147)'>-29(3)</div><div class="text-center text-white" style='background-color: rgb(232,105,140)'>-46(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,96,137)'>-51(6)</div><div class="text-center text-white" style='background-color: rgb(214,137,148)'>-28(3)</div><div class="text-center text-white" style='background-color: rgb(244,70,129)'>-64(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(234,99,138)'>-49(6)</div><div class="text-center text-white" style='background-color: rgb(219,130,146)'>-32(3)</div><div class="text-center text-white" style='background-color: rgb(247,61,125)'>-69(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,87,134)'>-55(6)</div><div class="text-center text-white" style='background-color: rgb(225,119,144)'>-38(3)</div><div class="text-center text-white" style='background-color: rgb(249,52,122)'>-74(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,80,132)'>-59(5)</div><div class="text-center text-white" style='background-color: rgb(233,102,139)'>-47(3)</div><div class="text-center text-white" style='background-color: rgb(253,26,112)'>-87(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(250,48,121)'>-75(5)</div><div class="text-center text-white" style='background-color: rgb(242,78,131)'>-60(2)</div><div class="text-center text-white" style='background-color: rgb(253,28,113)'>-86(5)</div> </td>
</tr>
 <tr>
  <td>h12</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(216,135,147)'>-28.8(6)</div><div class="text-center text-white" style='background-color: rgb(212,141,149)'>-25.1(3)</div><div class="text-center text-white" style='background-color: rgb(236,94,137)'>-51.5(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(212,140,148)'>-25.4(6)</div><div class="text-center text-white" style='background-color: rgb(210,144,149)'>-23.2(3)</div><div class="text-center text-white" style='background-color: rgb(233,103,139)'>-47.0(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(206,149,150)'>-20.3(6)</div><div class="text-center text-white" style='background-color: rgb(208,147,150)'>-21.7(3)</div><div class="text-center text-white" style='background-color: rgb(229,110,141)'>-42.8(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(200,157,151)'>-15(6)</div><div class="text-center text-white" style='background-color: rgb(211,142,149)'>-25(3)</div><div class="text-center text-white" style='background-color: rgb(228,112,142)'>-42(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12(2)</div><div class="text-center text-white" style='background-color: rgb(203,153,151)'>-18(1)</div><div class="text-center text-white" style='background-color: rgb(221,125,145)'>-34(2)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(234,100,138)'>-48(6)</div><div class="text-center text-white" style='background-color: rgb(210,143,149)'>-24(3)</div><div class="text-center text-white" style='background-color: rgb(231,107,140)'>-45(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(235,98,138)'>-49(6)</div><div class="text-center text-white" style='background-color: rgb(215,136,148)'>-28(3)</div><div class="text-center text-white" style='background-color: rgb(239,86,134)'>-56(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,94,137)'>-52(6)</div><div class="text-center text-white" style='background-color: rgb(222,124,145)'>-35(3)</div><div class="text-center text-white" style='background-color: rgb(247,59,125)'>-70(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,78,131)'>-60(5)</div><div class="text-center text-white" style='background-color: rgb(230,108,141)'>-44(3)</div><div class="text-center text-white" style='background-color: rgb(253,26,112)'>-87(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,53,122)'>-73(5)</div><div class="text-center text-white" style='background-color: rgb(241,82,133)'>-58(2)</div><div class="text-center text-white" style='background-color: rgb(254,19,109)'>-90(5)</div> </td>
</tr>
 <tr>
  <td>h11</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(215,135,148)'>-28(6)</div><div class="text-center " style='background-color: rgb(143,210,149)'>+24(3)</div><div class="text-center " style='background-color: rgb(110,229,141)'>+43(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(212,141,149)'>-25(6)</div><div class="text-center " style='background-color: rgb(138,213,148)'>+27(3)</div><div class="text-center " style='background-color: rgb(90,238,135)'>+54(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(208,146,149)'>-22(6)</div><div class="text-center " style='background-color: rgb(130,219,146)'>+32(3)</div><div class="text-center " style='background-color: rgb(73,244,130)'>+63(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(199,158,151)'>-15(6)</div><div class="text-center " style='background-color: rgb(125,221,145)'>+34(3)</div><div class="text-center " style='background-color: rgb(74,243,130)'>+62(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(200,157,151)'>-15(6)</div><div class="text-center " style='background-color: rgb(140,213,148)'>+26(3)</div><div class="text-center " style='background-color: rgb(72,244,129)'>+63(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,96,137)'>-51(6)</div><div class="text-center " style='background-color: rgb(140,213,148)'>+26(3)</div><div class="text-center " style='background-color: rgb(104,232,140)'>+46(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,92,136)'>-53(2)</div><div class="text-center " style='background-color: rgb(142,211,149)'>+24.3(9)</div><div class="text-center " style='background-color: rgb(111,229,142)'>+42(2)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,93,136)'>-52(6)</div><div class="text-center " style='background-color: rgb(165,194,152)'>+10(3)</div><div class="text-center " style='background-color: rgb(141,212,149)'>+25(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(240,83,133)'>-57(2)</div><div class="text-center " style='background-color: rgb(175,184,152)'>+3(1)</div><div class="text-center " style='background-color: rgb(167,192,152)'>+9(2)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,55,123)'>-72.12(1)</div><div class="text-center text-white" style='background-color: rgb(210,143,149)'>-23.79(1)</div><div class="text-center text-white" style='background-color: rgb(210,144,149)'>-23.45(1)</div> </td>
</tr>
 <tr>
  <td>h10</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(215,135,148)'>-28(6)</div><div class="text-center " style='background-color: rgb(150,206,150)'>+20(3)</div><div class="text-center " style='background-color: rgb(129,219,146)'>+32(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-24(6)</div><div class="text-center " style='background-color: rgb(156,201,151)'>+16(3)</div><div class="text-center " style='background-color: rgb(117,226,143)'>+39(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(208,146,149)'>-22(6)</div><div class="text-center " style='background-color: rgb(156,201,151)'>+16(3)</div><div class="text-center " style='background-color: rgb(110,229,141)'>+43(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(201,155,151)'>-16(6)</div><div class="text-center " style='background-color: rgb(139,213,148)'>+26(3)</div><div class="text-center " style='background-color: rgb(116,226,143)'>+39(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(194,164,152)'>-11(6)</div><div class="text-center " style='background-color: rgb(130,219,146)'>+32(3)</div><div class="text-center " style='background-color: rgb(96,236,137)'>+51(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,86,134)'>-56(6)</div><div class="text-center " style='background-color: rgb(136,215,148)'>+28(3)</div><div class="text-center " style='background-color: rgb(119,225,144)'>+38(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,94,137)'>-52(2)</div><div class="text-center " style='background-color: rgb(149,206,150)'>+20.1(9)</div><div class="text-center " style='background-color: rgb(134,216,147)'>+29(2)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,89,135)'>-54.3(6)</div><div class="text-center " style='background-color: rgb(162,196,152)'>+12.3(3)</div><div class="text-center " style='background-color: rgb(157,200,151)'>+15.3(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,82,133)'>-58.2(6)</div><div class="text-center text-white" style='background-color: rgb(188,172,152)'>-5.6(3)</div><div class="text-center text-white" style='background-color: rgb(191,167,152)'>-8.4(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,55,123)'>-72(2)</div><div class="text-center text-white" style='background-color: rgb(216,134,147)'>-29.3(9)</div><div class="text-center text-white" style='background-color: rgb(221,127,146)'>-34(2)</div> </td>
</tr>
 <tr>
  <td>h9</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(215,135,147)'>-28.6(6)</div><div class="text-center " style='background-color: rgb(169,190,152)'>+7.5(3)</div><div class="text-center " style='background-color: rgb(170,189,152)'>+6.6(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-25(2)</div><div class="text-center " style='background-color: rgb(165,193,152)'>+10(1)</div><div class="text-center " style='background-color: rgb(161,197,151)'>+13(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(209,146,149)'>-22(2)</div><div class="text-center " style='background-color: rgb(162,196,152)'>+12(1)</div><div class="text-center " style='background-color: rgb(151,205,150)'>+19(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(202,155,151)'>-16(2)</div><div class="text-center " style='background-color: rgb(159,198,151)'>+14(1)</div><div class="text-center " style='background-color: rgb(145,209,149)'>+23(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(197,161,151)'>-13(2)</div><div class="text-center " style='background-color: rgb(151,205,150)'>+19.1(9)</div><div class="text-center " style='background-color: rgb(135,215,147)'>+29(2)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(228,113,142)'>-41(6)</div><div class="text-center " style='background-color: rgb(150,206,150)'>+20(3)</div><div class="text-center " style='background-color: rgb(166,193,152)'>+10(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,95,137)'>-51(6)</div><div class="text-center " style='background-color: rgb(158,200,151)'>+15(3)</div><div class="text-center " style='background-color: rgb(178,182,152)'>+1(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,81,133)'>-58(6)</div><div class="text-center text-white" style='background-color: rgb(182,178,152)'>-2(3)</div><div class="text-center text-white" style='background-color: rgb(212,140,148)'>-26(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,82,133)'>-58(6)</div><div class="text-center text-white" style='background-color: rgb(204,151,150)'>-19(3)</div><div class="text-center text-white" style='background-color: rgb(238,89,135)'>-54(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,52,122)'>-74(5)</div><div class="text-center text-white" style='background-color: rgb(223,123,145)'>-36(3)</div><div class="text-center text-white" style='background-color: rgb(237,93,136)'>-52(5)</div> </td>
</tr>
 <tr>
  <td>h8</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(218,131,147)'>-31(6)</div><div class="text-center text-white" style='background-color: rgb(187,172,152)'>-5(3)</div><div class="text-center text-white" style='background-color: rgb(206,150,150)'>-20(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(217,132,147)'>-30(6)</div><div class="text-center " style='background-color: rgb(175,185,152)'>+4(3)</div><div class="text-center text-white" style='background-color: rgb(194,164,152)'>-11(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(202,155,151)'>-17(6)</div><div class="text-center " style='background-color: rgb(174,186,152)'>+4(3)</div><div class="text-center text-white" style='background-color: rgb(193,166,152)'>-9(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(195,163,152)'>-12(6)</div><div class="text-center " style='background-color: rgb(165,194,152)'>+10(3)</div><div class="text-center text-white" style='background-color: rgb(189,170,152)'>-7(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12.0(6)</div><div class="text-center " style='background-color: rgb(165,194,152)'>+10.3(3)</div><div class="text-center " style='background-color: rgb(169,190,152)'>+7.7(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(230,108,141)'>-44(6)</div><div class="text-center " style='background-color: rgb(170,189,152)'>+6(3)</div><div class="text-center text-white" style='background-color: rgb(194,164,152)'>-10(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(235,98,138)'>-50(6)</div><div class="text-center text-white" style='background-color: rgb(188,172,152)'>-6(3)</div><div class="text-center text-white" style='background-color: rgb(224,120,144)'>-37(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,86,134)'>-56(6)</div><div class="text-center text-white" style='background-color: rgb(210,143,149)'>-24(3)</div><div class="text-center text-white" style='background-color: rgb(251,44,119)'>-78(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(243,74,130)'>-62(5)</div><div class="text-center text-white" style='background-color: rgb(219,130,146)'>-32(3)</div><div class="text-center text-white" style='background-color: rgb(251,43,119)'>-78(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,50,121)'>-75(4)</div><div class="text-center text-white" style='background-color: rgb(233,102,139)'>-47(3)</div><div class="text-center text-white" style='background-color: rgb(254,21,110)'>-89(4)</div> </td>
</tr>
 <tr>
  <td>h7</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(212,141,148)'>-25(6)</div><div class="text-center text-white" style='background-color: rgb(197,161,152)'>-13(3)</div><div class="text-center text-white" style='background-color: rgb(219,129,146)'>-32(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(207,147,150)'>-21(6)</div><div class="text-center text-white" style='background-color: rgb(191,168,152)'>-8(3)</div><div class="text-center text-white" style='background-color: rgb(219,130,146)'>-32(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(205,150,150)'>-20(2)</div><div class="text-center text-white" style='background-color: rgb(187,173,152)'>-5(1)</div><div class="text-center text-white" style='background-color: rgb(216,135,147)'>-29(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(200,157,151)'>-15(6)</div><div class="text-center " style='background-color: rgb(174,185,152)'>+4(3)</div><div class="text-center text-white" style='background-color: rgb(209,145,149)'>-23(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(198,160,151)'>-13(6)</div><div class="text-center " style='background-color: rgb(174,185,152)'>+4(3)</div><div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(233,101,139)'>-48(6)</div><div class="text-center text-white" style='background-color: rgb(193,165,152)'>-10(3)</div><div class="text-center text-white" style='background-color: rgb(239,87,134)'>-56(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,90,135)'>-54(6)</div><div class="text-center text-white" style='background-color: rgb(207,148,150)'>-21(3)</div><div class="text-center text-white" style='background-color: rgb(252,33,115)'>-83(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,87,134)'>-55(5)</div><div class="text-center text-white" style='background-color: rgb(217,133,147)'>-30(3)</div><div class="text-center text-white" style='background-color: rgb(254,4,103)'>-98(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,86,134)'>-56(5)</div><div class="text-center text-white" style='background-color: rgb(226,116,143)'>-40(3)</div><div class="text-center text-white" style='background-color: rgb(254,10,106)'>-95(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,51,122)'>-74(4)</div><div class="text-center text-white" style='background-color: rgb(240,85,134)'>-57(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-110(4)</div> </td>
</tr>
 <tr>
  <td>h6</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(212,140,148)'>-26(6)</div><div class="text-center text-white" style='background-color: rgb(195,163,152)'>-12(3)</div><div class="text-center text-white" style='background-color: rgb(235,98,138)'>-50(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(208,147,150)'>-22(6)</div><div class="text-center text-white" style='background-color: rgb(194,164,152)'>-11(3)</div><div class="text-center text-white" style='background-color: rgb(235,97,137)'>-50(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(208,146,149)'>-22(2)</div><div class="text-center text-white" style='background-color: rgb(192,167,152)'>-9(1)</div><div class="text-center text-white" style='background-color: rgb(227,115,143)'>-40(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(205,151,150)'>-19(6)</div><div class="text-center text-white" style='background-color: rgb(192,166,152)'>-9(3)</div><div class="text-center text-white" style='background-color: rgb(222,125,145)'>-35(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(199,159,151)'>-14(2)</div><div class="text-center " style='background-color: rgb(179,181,152)'>+1(1)</div><div class="text-center text-white" style='background-color: rgb(209,144,149)'>-23(2)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,96,137)'>-51(6)</div><div class="text-center text-white" style='background-color: rgb(203,154,151)'>-17(3)</div><div class="text-center text-white" style='background-color: rgb(253,22,111)'>-89(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(234,100,138)'>-48(5)</div><div class="text-center text-white" style='background-color: rgb(212,140,148)'>-26(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-104(5)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,79,132)'>-60(5)</div><div class="text-center text-white" style='background-color: rgb(218,130,146)'>-32(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-114(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,87,134)'>-56(5)</div><div class="text-center text-white" style='background-color: rgb(224,120,144)'>-38(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-105(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(250,47,120)'>-76(4)</div><div class="text-center text-white" style='background-color: rgb(241,83,133)'>-58(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-121(4)</div> </td>
</tr>
 <tr>
  <td>h5</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(215,136,148)'>-28(2)</div><div class="text-center text-white" style='background-color: rgb(198,160,151)'>-13(1)</div><div class="text-center text-white" style='background-color: rgb(241,81,133)'>-58(2)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-24(6)</div><div class="text-center text-white" style='background-color: rgb(196,163,152)'>-12(3)</div><div class="text-center text-white" style='background-color: rgb(237,91,136)'>-53(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(206,149,150)'>-20(6)</div><div class="text-center text-white" style='background-color: rgb(195,163,152)'>-11(3)</div><div class="text-center text-white" style='background-color: rgb(229,111,142)'>-42(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(202,154,151)'>-17(2)</div><div class="text-center text-white" style='background-color: rgb(185,175,152)'>-4(1)</div><div class="text-center text-white" style='background-color: rgb(223,123,145)'>-36(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(194,164,152)'>-11(6)</div><div class="text-center " style='background-color: rgb(175,185,152)'>+3(3)</div><div class="text-center text-white" style='background-color: rgb(209,145,149)'>-23(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(233,103,139)'>-47(6)</div><div class="text-center text-white" style='background-color: rgb(198,160,151)'>-14(3)</div><div class="text-center text-white" style='background-color: rgb(253,27,112)'>-86(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,95,137)'>-51(5)</div><div class="text-center text-white" style='background-color: rgb(207,148,150)'>-21(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-102(5)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,91,136)'>-53(5)</div><div class="text-center text-white" style='background-color: rgb(224,121,144)'>-37(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-116(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,79,132)'>-60(5)</div><div class="text-center text-white" style='background-color: rgb(227,114,142)'>-41(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-105(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,54,123)'>-73(4)</div><div class="text-center text-white" style='background-color: rgb(242,77,131)'>-61(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-121(4)</div> </td>
</tr>
 <tr>
  <td>h4</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(213,139,148)'>-26(6)</div><div class="text-center text-white" style='background-color: rgb(199,158,151)'>-14(3)</div><div class="text-center text-white" style='background-color: rgb(241,82,133)'>-58(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(210,144,149)'>-23(6)</div><div class="text-center text-white" style='background-color: rgb(195,164,152)'>-11(3)</div><div class="text-center text-white" style='background-color: rgb(230,110,141)'>-43(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-24(6)</div><div class="text-center text-white" style='background-color: rgb(185,174,152)'>-4(3)</div><div class="text-center text-white" style='background-color: rgb(232,105,140)'>-46(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(205,150,150)'>-20(6)</div><div class="text-center text-white" style='background-color: rgb(181,178,152)'>-1(3)</div><div class="text-center text-white" style='background-color: rgb(219,130,146)'>-32(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(197,161,151)'>-13(6)</div><div class="text-center " style='background-color: rgb(174,185,152)'>+4(3)</div><div class="text-center text-white" style='background-color: rgb(214,137,148)'>-28(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(230,109,141)'>-43(6)</div><div class="text-center text-white" style='background-color: rgb(203,154,151)'>-17(3)</div><div class="text-center text-white" style='background-color: rgb(254,17,109)'>-91(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,95,137)'>-51(6)</div><div class="text-center text-white" style='background-color: rgb(205,150,150)'>-20(3)</div><div class="text-center text-white" style='background-color: rgb(254,4,103)'>-98(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,86,134)'>-56(5)</div><div class="text-center text-white" style='background-color: rgb(213,138,148)'>-27(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-106(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(240,85,134)'>-56(5)</div><div class="text-center text-white" style='background-color: rgb(222,123,145)'>-36(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-113(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,58,124)'>-70(4)</div><div class="text-center text-white" style='background-color: rgb(235,96,137)'>-50(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-111(4)</div> </td>
</tr>

 </tbody>
 <thead>
  <tr>
   <th class="text-center" width="10%" colspan="2">Hand</th>
   <th class="text-center" width="9%">2</th>
   <th class="text-center" width="9%">3</th>
   <th class="text-center" width="9%">4</th>
   <th class="text-center" width="9%">5</th>
   <th class="text-center" width="9%">6</th>
   <th class="text-center" width="9%">7</th>
   <th class="text-center" width="9%">8</th>
   <th class="text-center" width="9%">9</th>
   <th class="text-center" width="9%">T</th>
   <th class="text-center" width="9%">A</th>
  </tr>
 </thead> 

 <tbody> 
 <tr>
  <td>s20</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center " style='background-color: rgb(71,244,129)'>+64(6)</div><div class="text-center " style='background-color: rgb(152,204,150)'>+18(3)</div><div class="text-center " style='background-color: rgb(113,228,142)'>+41(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(75,243,130)'>+62(6)</div><div class="text-center " style='background-color: rgb(146,208,149)'>+22(3)</div><div class="text-center " style='background-color: rgb(115,227,143)'>+40(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(62,247,126)'>+69(6)</div><div class="text-center " style='background-color: rgb(143,211,149)'>+24(3)</div><div class="text-center " style='background-color: rgb(105,232,140)'>+46(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(68,245,128)'>+66(6)</div><div class="text-center " style='background-color: rgb(137,214,148)'>+27(3)</div><div class="text-center " style='background-color: rgb(92,237,136)'>+53(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(64,246,126)'>+67(2)</div><div class="text-center " style='background-color: rgb(134,216,147)'>+29.0(9)</div><div class="text-center " style='background-color: rgb(84,240,133)'>+57(2)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(50,249,121)'>+74(6)</div><div class="text-center " style='background-color: rgb(139,213,148)'>+26(3)</div><div class="text-center " style='background-color: rgb(106,231,140)'>+45(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(41,251,118)'>+79(6)</div><div class="text-center " style='background-color: rgb(145,209,149)'>+22(3)</div><div class="text-center " style='background-color: rgb(130,219,146)'>+32(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center " style='background-color: rgb(53,249,122)'>+73(6)</div><div class="text-center " style='background-color: rgb(163,195,152)'>+11(3)</div><div class="text-center " style='background-color: rgb(170,189,152)'>+7(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center " style='background-color: rgb(110,230,141)'>+43(6)</div><div class="text-center text-white" style='background-color: rgb(186,173,152)'>-5(3)</div><div class="text-center text-white" style='background-color: rgb(190,169,152)'>-8(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center " style='background-color: rgb(166,193,152)'>+10(5)</div><div class="text-center text-white" style='background-color: rgb(218,131,146)'>-31(3)</div><div class="text-center text-white" style='background-color: rgb(219,130,146)'>-32(5)</div> </td>
</tr>
 <tr>
  <td>s19</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center " style='background-color: rgb(113,228,142)'>+41(6)</div><div class="text-center " style='background-color: rgb(166,192,152)'>+9(3)</div><div class="text-center " style='background-color: rgb(150,206,150)'>+20(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(117,226,143)'>+39(6)</div><div class="text-center " style='background-color: rgb(161,196,152)'>+12(3)</div><div class="text-center " style='background-color: rgb(145,209,149)'>+23(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(114,227,142)'>+41(2)</div><div class="text-center " style='background-color: rgb(152,204,150)'>+18.3(9)</div><div class="text-center " style='background-color: rgb(125,222,145)'>+35(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(107,231,141)'>+44(2)</div><div class="text-center " style='background-color: rgb(148,207,150)'>+20.7(9)</div><div class="text-center " style='background-color: rgb(119,225,144)'>+38(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(106,231,140)'>+45.35(1)</div><div class="text-center " style='background-color: rgb(144,210,149)'>+23.26(1)</div><div class="text-center " style='background-color: rgb(104,232,140)'>+46.26(1)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(82,241,133)'>+58(6)</div><div class="text-center " style='background-color: rgb(146,208,149)'>+22(3)</div><div class="text-center " style='background-color: rgb(131,218,146)'>+31(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(80,241,132)'>+59(6)</div><div class="text-center " style='background-color: rgb(162,196,152)'>+12(3)</div><div class="text-center " style='background-color: rgb(156,201,151)'>+16(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center " style='background-color: rgb(138,214,148)'>+27(6)</div><div class="text-center " style='background-color: rgb(174,185,152)'>+4(3)</div><div class="text-center text-white" style='background-color: rgb(181,178,152)'>-1(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center " style='background-color: rgb(180,180,153)'>+0(6)</div><div class="text-center text-white" style='background-color: rgb(197,161,151)'>-13(3)</div><div class="text-center text-white" style='background-color: rgb(217,132,147)'>-30(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(203,153,151)'>-18(5)</div><div class="text-center text-white" style='background-color: rgb(222,124,145)'>-35(3)</div><div class="text-center text-white" style='background-color: rgb(238,89,135)'>-54(5)</div> </td>
</tr>
 <tr>
  <td>s18</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center " style='background-color: rgb(163,195,152)'>+11.12(1)</div><div class="text-center " style='background-color: rgb(171,188,152)'>+6.04(1)</div><div class="text-center " style='background-color: rgb(163,196,152)'>+11.69(1)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(158,199,151)'>+14.4(6)</div><div class="text-center " style='background-color: rgb(167,192,152)'>+8.8(3)</div><div class="text-center " style='background-color: rgb(153,203,151)'>+17.9(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(154,203,151)'>+17.3(6)</div><div class="text-center " style='background-color: rgb(163,195,152)'>+11.4(3)</div><div class="text-center " style='background-color: rgb(143,210,149)'>+23.8(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(156,201,151)'>+16(6)</div><div class="text-center " style='background-color: rgb(159,198,151)'>+14(3)</div><div class="text-center " style='background-color: rgb(129,219,146)'>+32(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(142,211,149)'>+25(6)</div><div class="text-center " style='background-color: rgb(165,193,152)'>+10(3)</div><div class="text-center " style='background-color: rgb(112,228,142)'>+42(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(106,231,140)'>+45(6)</div><div class="text-center " style='background-color: rgb(152,204,150)'>+18(3)</div><div class="text-center " style='background-color: rgb(159,199,151)'>+14(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(165,193,152)'>+10(2)</div><div class="text-center " style='background-color: rgb(173,187,152)'>+5.0(9)</div><div class="text-center text-white" style='background-color: rgb(183,176,152)'>-3(2)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(202,154,151)'>-17(2)</div><div class="text-center text-white" style='background-color: rgb(194,164,152)'>-10.4(9)</div><div class="text-center text-white" style='background-color: rgb(214,137,148)'>-27(2)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-24(2)</div><div class="text-center text-white" style='background-color: rgb(207,148,150)'>-21.0(9)</div><div class="text-center text-white" style='background-color: rgb(225,119,144)'>-38(2)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(231,106,140)'>-45(2)</div><div class="text-center text-white" style='background-color: rgb(228,113,142)'>-41.1(9)</div><div class="text-center text-white" style='background-color: rgb(243,76,131)'>-61(2)</div> </td>
</tr>
 <tr>
  <td>s17</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(200,156,151)'>-15.56(1)</div><div class="text-center text-white" style='background-color: rgb(181,179,152)'>-0.51(1)</div><div class="text-center text-white" style='background-color: rgb(181,178,152)'>-1.04(1)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12(2)</div><div class="text-center " style='background-color: rgb(178,182,152)'>+1(1)</div><div class="text-center " style='background-color: rgb(170,189,152)'>+7(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(188,172,152)'>-6(6)</div><div class="text-center " style='background-color: rgb(170,189,152)'>+7(3)</div><div class="text-center " style='background-color: rgb(153,203,151)'>+18(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(189,170,152)'>-7(6)</div><div class="text-center " style='background-color: rgb(167,192,152)'>+9(3)</div><div class="text-center " style='background-color: rgb(148,207,150)'>+21(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(178,182,152)'>+1(6)</div><div class="text-center " style='background-color: rgb(165,193,152)'>+10(3)</div><div class="text-center " style='background-color: rgb(140,212,148)'>+26(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(193,166,152)'>-10(6)</div><div class="text-center " style='background-color: rgb(164,194,152)'>+11(3)</div><div class="text-center " style='background-color: rgb(178,182,152)'>+1(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(226,117,143)'>-39(6)</div><div class="text-center text-white" style='background-color: rgb(190,169,152)'>-7(3)</div><div class="text-center text-white" style='background-color: rgb(211,142,149)'>-25(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(229,111,142)'>-43(6)</div><div class="text-center text-white" style='background-color: rgb(204,152,150)'>-19(3)</div><div class="text-center text-white" style='background-color: rgb(224,120,144)'>-37(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(233,101,139)'>-48(6)</div><div class="text-center text-white" style='background-color: rgb(217,133,147)'>-30(3)</div><div class="text-center text-white" style='background-color: rgb(235,98,138)'>-49(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(245,70,129)'>-64(5)</div><div class="text-center text-white" style='background-color: rgb(232,103,139)'>-47(3)</div><div class="text-center text-white" style='background-color: rgb(246,64,126)'>-68(5)</div> </td>
</tr>
 <tr>
  <td>s16</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(217,133,147)'>-30(6)</div><div class="text-center " style='background-color: rgb(178,182,152)'>+1(3)</div><div class="text-center text-white" style='background-color: rgb(206,149,150)'>-20(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-24.2(6)</div><div class="text-center " style='background-color: rgb(180,180,152)'>+0.2(3)</div><div class="text-center text-white" style='background-color: rgb(181,179,152)'>-0.9(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(206,149,150)'>-20.5(6)</div><div class="text-center " style='background-color: rgb(174,185,152)'>+3.8(3)</div><div class="text-center " style='background-color: rgb(171,189,152)'>+6.3(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(203,153,150)'>-18(2)</div><div class="text-center " style='background-color: rgb(169,190,152)'>+8(1)</div><div class="text-center " style='background-color: rgb(161,197,151)'>+13(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(192,167,152)'>-9(6)</div><div class="text-center " style='background-color: rgb(164,194,152)'>+10(3)</div><div class="text-center " style='background-color: rgb(150,205,150)'>+20(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(232,105,140)'>-46(6)</div><div class="text-center text-white" style='background-color: rgb(186,174,152)'>-4(3)</div><div class="text-center text-white" style='background-color: rgb(213,140,148)'>-26(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,87,134)'>-55(6)</div><div class="text-center text-white" style='background-color: rgb(191,168,152)'>-8(3)</div><div class="text-center text-white" style='background-color: rgb(211,142,149)'>-25(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,87,134)'>-56(6)</div><div class="text-center text-white" style='background-color: rgb(193,165,152)'>-10(3)</div><div class="text-center text-white" style='background-color: rgb(235,97,138)'>-50(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,78,131)'>-60(6)</div><div class="text-center text-white" style='background-color: rgb(212,141,148)'>-25(3)</div><div class="text-center text-white" style='background-color: rgb(236,95,137)'>-51(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(250,48,121)'>-75(5)</div><div class="text-center text-white" style='background-color: rgb(229,110,141)'>-43(3)</div><div class="text-center text-white" style='background-color: rgb(247,60,125)'>-70(5)</div> </td>
</tr>
 <tr>
  <td>s15</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(217,133,147)'>-30(2)</div><div class="text-center " style='background-color: rgb(177,182,152)'>+2(1)</div><div class="text-center text-white" style='background-color: rgb(187,172,152)'>-5(2)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(216,134,147)'>-29(6)</div><div class="text-center " style='background-color: rgb(177,183,152)'>+2(3)</div><div class="text-center text-white" style='background-color: rgb(192,167,152)'>-9(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(207,148,150)'>-20.9(6)</div><div class="text-center " style='background-color: rgb(172,187,152)'>+5.3(3)</div><div class="text-center " style='background-color: rgb(169,190,152)'>+7.2(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(201,156,151)'>-16(2)</div><div class="text-center " style='background-color: rgb(167,191,152)'>+8(1)</div><div class="text-center " style='background-color: rgb(158,199,151)'>+14(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(189,171,152)'>-6(6)</div><div class="text-center " style='background-color: rgb(174,186,152)'>+4(3)</div><div class="text-center " style='background-color: rgb(148,207,150)'>+21(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(228,113,142)'>-41(6)</div><div class="text-center " style='background-color: rgb(174,186,152)'>+4(3)</div><div class="text-center text-white" style='background-color: rgb(197,160,151)'>-13(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,91,136)'>-53(6)</div><div class="text-center text-white" style='background-color: rgb(186,173,152)'>-5(3)</div><div class="text-center text-white" style='background-color: rgb(209,145,149)'>-22(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(235,96,137)'>-50(6)</div><div class="text-center text-white" style='background-color: rgb(200,157,151)'>-15(3)</div><div class="text-center text-white" style='background-color: rgb(232,105,140)'>-46(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,78,131)'>-60(6)</div><div class="text-center text-white" style='background-color: rgb(208,147,150)'>-22(3)</div><div class="text-center text-white" style='background-color: rgb(242,79,132)'>-59(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,53,122)'>-73(5)</div><div class="text-center text-white" style='background-color: rgb(228,113,142)'>-41(3)</div><div class="text-center text-white" style='background-color: rgb(251,44,119)'>-78(5)</div> </td>
</tr>
 <tr>
  <td>s14</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(216,134,147)'>-29(6)</div><div class="text-center " style='background-color: rgb(171,189,152)'>+6(3)</div><div class="text-center text-white" style='background-color: rgb(188,171,152)'>-6(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,141,149)'>-24.9(6)</div><div class="text-center " style='background-color: rgb(173,186,152)'>+4.6(3)</div><div class="text-center text-white" style='background-color: rgb(181,178,152)'>-1.2(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(204,152,150)'>-19(6)</div><div class="text-center " style='background-color: rgb(170,189,152)'>+7(3)</div><div class="text-center text-white" style='background-color: rgb(185,175,152)'>-3(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(202,155,151)'>-16.55(1)</div><div class="text-center " style='background-color: rgb(164,194,152)'>+10.72(1)</div><div class="text-center " style='background-color: rgb(161,197,151)'>+12.64(1)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(195,163,152)'>-11(2)</div><div class="text-center " style='background-color: rgb(163,195,152)'>+11(1)</div><div class="text-center " style='background-color: rgb(150,205,150)'>+19(2)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(233,101,139)'>-48(6)</div><div class="text-center " style='background-color: rgb(168,191,152)'>+8(3)</div><div class="text-center text-white" style='background-color: rgb(195,163,152)'>-11(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,95,137)'>-51(6)</div><div class="text-center " style='background-color: rgb(179,181,152)'>+1(3)</div><div class="text-center text-white" style='background-color: rgb(219,130,146)'>-32(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,90,135)'>-54(6)</div><div class="text-center text-white" style='background-color: rgb(183,176,152)'>-2(3)</div><div class="text-center text-white" style='background-color: rgb(229,111,142)'>-42(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,86,134)'>-56(6)</div><div class="text-center text-white" style='background-color: rgb(201,156,151)'>-16(3)</div><div class="text-center text-white" style='background-color: rgb(236,95,137)'>-51(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,56,123)'>-72(5)</div><div class="text-center text-white" style='background-color: rgb(227,114,143)'>-40(3)</div><div class="text-center text-white" style='background-color: rgb(248,58,124)'>-70(5)</div> </td>
</tr>
 <tr>
  <td>s13</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(215,136,148)'>-28(2)</div><div class="text-center " style='background-color: rgb(175,185,152)'>+4(1)</div><div class="text-center text-white" style='background-color: rgb(193,166,152)'>-10(2)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-25(2)</div><div class="text-center " style='background-color: rgb(167,192,152)'>+9(1)</div><div class="text-center " style='background-color: rgb(178,181,152)'>+1(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(207,148,150)'>-21(2)</div><div class="text-center " style='background-color: rgb(166,193,152)'>+9(1)</div><div class="text-center " style='background-color: rgb(171,188,152)'>+6(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(201,155,151)'>-16.40(1)</div><div class="text-center " style='background-color: rgb(161,197,151)'>+12.91(1)</div><div class="text-center " style='background-color: rgb(160,197,151)'>+13.05(1)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(194,165,152)'>-10(6)</div><div class="text-center " style='background-color: rgb(165,194,152)'>+10(3)</div><div class="text-center " style='background-color: rgb(145,209,149)'>+23(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(234,100,138)'>-48(6)</div><div class="text-center " style='background-color: rgb(167,192,152)'>+9(3)</div><div class="text-center text-white" style='background-color: rgb(203,153,150)'>-18(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(230,108,141)'>-44(6)</div><div class="text-center " style='background-color: rgb(173,187,152)'>+5(3)</div><div class="text-center text-white" style='background-color: rgb(211,142,149)'>-25(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(240,86,134)'>-56(6)</div><div class="text-center text-white" style='background-color: rgb(185,174,152)'>-4(3)</div><div class="text-center text-white" style='background-color: rgb(224,120,144)'>-37(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,79,132)'>-59(6)</div><div class="text-center text-white" style='background-color: rgb(206,150,150)'>-20(3)</div><div class="text-center text-white" style='background-color: rgb(244,73,130)'>-63(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,59,125)'>-70(5)</div><div class="text-center text-white" style='background-color: rgb(226,117,143)'>-39(3)</div><div class="text-center text-white" style='background-color: rgb(247,60,125)'>-69(5)</div> </td>
</tr>
 <tr>
  <td>s12</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(214,137,148)'>-28(6)</div><div class="text-center " style='background-color: rgb(172,187,152)'>+5(3)</div><div class="text-center text-white" style='background-color: rgb(185,174,152)'>-4(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-24(6)</div><div class="text-center " style='background-color: rgb(161,197,151)'>+13(3)</div><div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(207,148,150)'>-21(2)</div><div class="text-center " style='background-color: rgb(160,198,151)'>+14(1)</div><div class="text-center " style='background-color: rgb(172,187,152)'>+5(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(201,155,151)'>-16.3(6)</div><div class="text-center " style='background-color: rgb(156,200,151)'>+15.6(3)</div><div class="text-center " style='background-color: rgb(162,196,152)'>+12.2(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(195,163,152)'>-12(2)</div><div class="text-center " style='background-color: rgb(159,198,151)'>+14(1)</div><div class="text-center " style='background-color: rgb(143,211,149)'>+24(2)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,94,137)'>-52(6)</div><div class="text-center " style='background-color: rgb(155,201,151)'>+16(3)</div><div class="text-center text-white" style='background-color: rgb(199,158,151)'>-14(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,94,137)'>-52(6)</div><div class="text-center " style='background-color: rgb(165,193,152)'>+10(3)</div><div class="text-center text-white" style='background-color: rgb(217,133,147)'>-30(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,89,135)'>-55(6)</div><div class="text-center " style='background-color: rgb(177,183,152)'>+2(3)</div><div class="text-center text-white" style='background-color: rgb(234,100,138)'>-49(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,90,135)'>-54(6)</div><div class="text-center text-white" style='background-color: rgb(191,168,152)'>-8(3)</div><div class="text-center text-white" style='background-color: rgb(236,96,137)'>-51(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,55,123)'>-72(5)</div><div class="text-center text-white" style='background-color: rgb(220,128,146)'>-33(3)</div><div class="text-center text-white" style='background-color: rgb(247,60,125)'>-69(5)</div> </td>
</tr>

 </tbody>
 <thead>
  <tr>
   <th class="text-center" width="10%" colspan="2">Hand</th>
   <th class="text-center" width="9%">2</th>
   <th class="text-center" width="9%">3</th>
   <th class="text-center" width="9%">4</th>
   <th class="text-center" width="9%">5</th>
   <th class="text-center" width="9%">6</th>
   <th class="text-center" width="9%">7</th>
   <th class="text-center" width="9%">8</th>
   <th class="text-center" width="9%">9</th>
   <th class="text-center" width="9%">T</th>
   <th class="text-center" width="9%">A</th>
  </tr>
 </thead> 

 <tbody> 
 <tr>
  <td>pA</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center " style='background-color: rgb(95,236,137)'>+51(5)</div><div class="text-center " style='background-color: rgb(169,190,152)'>+7(3)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(88,239,135)'>+55(5)</div><div class="text-center " style='background-color: rgb(164,194,152)'>+11(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(77,242,131)'>+61(5)</div><div class="text-center " style='background-color: rgb(164,194,152)'>+11(3)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(75,243,130)'>+62(5)</div><div class="text-center " style='background-color: rgb(158,199,151)'>+15(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(69,245,128)'>+65(5)</div><div class="text-center " style='background-color: rgb(154,202,151)'>+17(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(89,238,135)'>+54(5)</div><div class="text-center " style='background-color: rgb(156,201,151)'>+16(3)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(121,224,144)'>+37(5)</div><div class="text-center " style='background-color: rgb(168,191,152)'>+8(3)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center " style='background-color: rgb(154,202,151)'>+17(5)</div><div class="text-center text-white" style='background-color: rgb(190,169,152)'>-7(3)</div> </td>
 <!-- T -->
 <td>
<div class="text-center " style='background-color: rgb(152,204,150)'>+18(5)</div><div class="text-center text-white" style='background-color: rgb(200,157,151)'>-15(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(210,143,149)'>-24(4)</div><div class="text-center text-white" style='background-color: rgb(223,122,144)'>-36(3)</div> </td>
 <tr>
  <td>pT</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center " style='background-color: rgb(119,225,144)'>+38(5)</div><div class="text-center " style='background-color: rgb(70,244,129)'>+64(2)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(125,221,145)'>+34(5)</div><div class="text-center " style='background-color: rgb(68,245,128)'>+66(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(103,232,139)'>+47(5)</div><div class="text-center " style='background-color: rgb(61,247,125)'>+69(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(105,232,140)'>+46(5)</div><div class="text-center " style='background-color: rgb(60,247,125)'>+69(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(86,239,134)'>+56(5)</div><div class="text-center " style='background-color: rgb(69,245,128)'>+65(2)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(105,232,140)'>+46(5)</div><div class="text-center " style='background-color: rgb(45,250,120)'>+77(2)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(107,231,141)'>+44(4)</div><div class="text-center " style='background-color: rgb(38,252,117)'>+81(2)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center " style='background-color: rgb(135,216,147)'>+29(5)</div><div class="text-center " style='background-color: rgb(52,249,122)'>+74(2)</div> </td>
 <!-- T -->
 <td>
<div class="text-center " style='background-color: rgb(174,186,152)'>+4(5)</div><div class="text-center " style='background-color: rgb(110,229,141)'>+43(2)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(218,130,146)'>-32(4)</div><div class="text-center " style='background-color: rgb(164,195,152)'>+11(3)</div> </td>
 <tr>
  <td>p9</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center " style='background-color: rgb(150,206,150)'>+20(2)</div><div class="text-center " style='background-color: rgb(163,195,152)'>+11.5(9)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(129,219,146)'>+32(6)</div><div class="text-center " style='background-color: rgb(165,194,152)'>+10(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(137,214,148)'>+27(2)</div><div class="text-center " style='background-color: rgb(154,203,151)'>+17.3(9)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(123,223,145)'>+36(6)</div><div class="text-center " style='background-color: rgb(146,208,150)'>+22(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(114,227,142)'>+41(6)</div><div class="text-center " style='background-color: rgb(145,209,149)'>+23(3)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(127,220,146)'>+33(2)</div><div class="text-center " style='background-color: rgb(114,227,142)'>+40.8(8)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(140,212,148)'>+26(5)</div><div class="text-center " style='background-color: rgb(159,199,151)'>+14(2)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(185,174,152)'>-4(5)</div><div class="text-center text-white" style='background-color: rgb(205,151,150)'>-19(3)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(222,124,145)'>-35(5)</div><div class="text-center text-white" style='background-color: rgb(212,141,148)'>-25(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,91,136)'>-53(5)</div><div class="text-center text-white" style='background-color: rgb(228,113,142)'>-41(3)</div> </td>
 <tr>
  <td>p8</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center " style='background-color: rgb(179,180,152)'>+0(6)</div><div class="text-center text-white" style='background-color: rgb(220,128,146)'>-33(3)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(176,184,152)'>+3(7)</div><div class="text-center text-white" style='background-color: rgb(205,151,150)'>-19(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(169,190,152)'>+7(7)</div><div class="text-center text-white" style='background-color: rgb(208,146,150)'>-22(3)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(151,204,150)'>+19(7)</div><div class="text-center text-white" style='background-color: rgb(199,158,151)'>-15(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(140,212,148)'>+26(7)</div><div class="text-center text-white" style='background-color: rgb(196,161,152)'>-12(3)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(152,204,150)'>+19(6)</div><div class="text-center text-white" style='background-color: rgb(227,115,143)'>-40(3)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(186,173,152)'>-5(6)</div><div class="text-center text-white" style='background-color: rgb(230,109,141)'>-44(3)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(228,113,142)'>-41(2)</div><div class="text-center text-white" style='background-color: rgb(236,94,137)'>-51.5(8)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(235,97,138)'>-50(2)</div><div class="text-center text-white" style='background-color: rgb(241,83,133)'>-57.7(8)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(245,68,128)'>-65(1)</div><div class="text-center text-white" style='background-color: rgb(247,61,125)'>-69.2(7)</div> </td>
 <tr>
  <td>p7</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(204,151,150)'>-19(7)</div><div class="text-center text-white" style='background-color: rgb(216,134,147)'>-29(3)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(199,159,151)'>-14(8)</div><div class="text-center text-white" style='background-color: rgb(218,132,147)'>-31(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(178,182,152)'>+1(8)</div><div class="text-center text-white" style='background-color: rgb(201,155,151)'>-16(3)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(170,189,152)'>+7(8)</div><div class="text-center text-white" style='background-color: rgb(195,163,152)'>-11(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(145,209,149)'>+23(8)</div><div class="text-center text-white" style='background-color: rgb(194,164,152)'>-10(3)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(180,179,152)'>-0(6)</div><div class="text-center text-white" style='background-color: rgb(223,123,145)'>-36(3)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(226,117,143)'>-38.9(6)</div><div class="text-center text-white" style='background-color: rgb(224,121,144)'>-36.8(3)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(240,84,134)'>-57(6)</div><div class="text-center text-white" style='background-color: rgb(231,106,140)'>-45(3)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(244,71,129)'>-64(5)</div><div class="text-center text-white" style='background-color: rgb(238,90,135)'>-54(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(251,39,117)'>-80(4)</div><div class="text-center text-white" style='background-color: rgb(244,73,130)'>-63(2)</div> </td>
 <tr>
  <td>p6</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(207,147,150)'>-21.3(7)</div><div class="text-center text-white" style='background-color: rgb(212,141,149)'>-25.1(3)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(177,182,152)'>+2(8)</div><div class="text-center text-white" style='background-color: rgb(212,141,149)'>-25(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(186,173,152)'>-5(2)</div><div class="text-center text-white" style='background-color: rgb(208,147,150)'>-22(1)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(185,174,152)'>-4(8)</div><div class="text-center text-white" style='background-color: rgb(206,149,150)'>-20(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(162,196,152)'>+12(8)</div><div class="text-center text-white" style='background-color: rgb(194,164,152)'>-11(3)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(215,136,148)'>-28(2)</div><div class="text-center text-white" style='background-color: rgb(208,147,150)'>-21.6(9)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(225,118,143)'>-39(2)</div><div class="text-center text-white" style='background-color: rgb(213,139,148)'>-26.1(9)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(231,107,141)'>-44(5)</div><div class="text-center text-white" style='background-color: rgb(219,130,146)'>-32(3)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(244,72,129)'>-63(5)</div><div class="text-center text-white" style='background-color: rgb(228,112,142)'>-42(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(252,33,115)'>-83(4)</div><div class="text-center text-white" style='background-color: rgb(241,82,133)'>-58(2)</div> </td>
 <tr>
  <td>p5</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(203,153,151)'>-18(7)</div><div class="text-center " style='background-color: rgb(116,226,143)'>+40(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(187,172,152)'>-5(7)</div><div class="text-center " style='background-color: rgb(103,233,139)'>+47(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(193,166,152)'>-10(8)</div><div class="text-center " style='background-color: rgb(93,237,136)'>+52(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(171,188,152)'>+6(8)</div><div class="text-center " style='background-color: rgb(87,239,134)'>+56(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(160,197,151)'>+13(8)</div><div class="text-center " style='background-color: rgb(86,239,134)'>+56(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(207,147,150)'>-21(6)</div><div class="text-center " style='background-color: rgb(118,225,144)'>+38(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(218,131,147)'>-31(5)</div><div class="text-center " style='background-color: rgb(132,217,147)'>+30(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(226,117,143)'>-39(5)</div><div class="text-center " style='background-color: rgb(164,194,152)'>+11(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,78,131)'>-60(5)</div><div class="text-center text-white" style='background-color: rgb(191,168,152)'>-8(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,51,122)'>-74(4)</div><div class="text-center text-white" style='background-color: rgb(216,134,147)'>-29(3)</div> </td>
 <tr>
  <td>p4</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(204,152,150)'>-19(2)</div><div class="text-center text-white" style='background-color: rgb(182,178,152)'>-1(1)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(205,150,150)'>-20(7)</div><div class="text-center " style='background-color: rgb(169,190,152)'>+8(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(182,178,152)'>-1(2)</div><div class="text-center " style='background-color: rgb(174,186,152)'>+4(1)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(163,195,152)'>+11(2)</div><div class="text-center " style='background-color: rgb(168,191,152)'>+8(1)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(157,200,151)'>+15(2)</div><div class="text-center " style='background-color: rgb(169,190,152)'>+7(1)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(192,166,152)'>-9(6)</div><div class="text-center " style='background-color: rgb(166,193,152)'>+10(3)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(220,127,146)'>-33(5)</div><div class="text-center text-white" style='background-color: rgb(189,171,152)'>-6(3)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(226,117,143)'>-39(5)</div><div class="text-center text-white" style='background-color: rgb(208,146,150)'>-22(3)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(243,75,130)'>-62(5)</div><div class="text-center text-white" style='background-color: rgb(216,135,147)'>-29(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(247,62,126)'>-69(4)</div><div class="text-center text-white" style='background-color: rgb(235,97,137)'>-50(3)</div> </td>
 <tr>
  <td>p3</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(198,159,151)'>-13.89(1)</div><div class="text-center text-white" style='background-color: rgb(198,159,151)'>-13.77(1)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(189,170,152)'>-6.7(7)</div><div class="text-center text-white" style='background-color: rgb(194,164,152)'>-10.5(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(170,189,152)'>+7(7)</div><div class="text-center text-white" style='background-color: rgb(189,170,152)'>-7(3)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(166,192,152)'>+9(8)</div><div class="text-center text-white" style='background-color: rgb(185,174,152)'>-4(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(152,204,150)'>+19(8)</div><div class="text-center text-white" style='background-color: rgb(184,176,152)'>-3(3)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(188,171,152)'>-6(2)</div><div class="text-center text-white" style='background-color: rgb(200,157,151)'>-15.0(9)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(210,144,149)'>-23.27(1)</div><div class="text-center text-white" style='background-color: rgb(208,147,150)'>-21.65(1)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(227,115,143)'>-40(2)</div><div class="text-center text-white" style='background-color: rgb(218,131,147)'>-31.0(9)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,82,133)'>-58(2)</div><div class="text-center text-white" style='background-color: rgb(226,116,143)'>-39.3(9)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(246,64,126)'>-68(4)</div><div class="text-center text-white" style='background-color: rgb(240,83,133)'>-57(2)</div> </td>
 <tr>
  <td>p2</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(188,171,152)'>-6(6)</div><div class="text-center text-white" style='background-color: rgb(200,157,151)'>-15(3)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(178,181,152)'>+1(7)</div><div class="text-center text-white" style='background-color: rgb(194,164,152)'>-10(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(171,188,152)'>+6(2)</div><div class="text-center text-white" style='background-color: rgb(186,173,152)'>-5(1)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(142,211,149)'>+25(8)</div><div class="text-center " style='background-color: rgb(179,180,152)'>+0(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(152,204,150)'>+19(2)</div><div class="text-center " style='background-color: rgb(175,184,152)'>+3(1)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(168,191,152)'>+8(6)</div><div class="text-center text-white" style='background-color: rgb(195,163,152)'>-11(3)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(203,153,151)'>-17.5(6)</div><div class="text-center text-white" style='background-color: rgb(200,157,151)'>-15.5(3)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(221,125,145)'>-34(6)</div><div class="text-center text-white" style='background-color: rgb(210,143,149)'>-24(3)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,80,132)'>-59(5)</div><div class="text-center text-white" style='background-color: rgb(221,125,145)'>-34(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(247,61,125)'>-69(4)</div><div class="text-center text-white" style='background-color: rgb(239,87,134)'>-55(3)</div> </td>

 </tbody>
</table>

## Detailed explanation

We want to derive the basic strategy from scratch, i.e. without assuming anything. What we are going to do is to play a large (more on what _large_ means below) number of hands by fixing our first two cards and the dealer upcard and sequentially standing, doubling or hitting the first card. Then we will compare the results for the three cases and select as the proper strategy the better one.

Standing and doubling are easy plays, because after we stand or double the dealer plays accordingly to the rules. She hits until seventeen (either soft or hard). But if we hit on our hand, we might need to make another decision wether to stand or hit again. As we do not want to assume anything, we have to play in such an order that if we do need to make another decision, we already know which is the better one. 

**TO BE COMPLETED**


-------
:::{.text-center}
[Previous](../08-mimic-the-dealer) | [Index](../) | [Next](../)
:::
