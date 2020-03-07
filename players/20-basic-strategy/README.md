
---
title: Derivation of the basic strategy
...

# Derivation of the basic strategy

> Difficulty: 20/100

## Quick run

Execute the `run.sh` script. It should take a minute or so:

```terminal
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
h11  d  d  d  d  d  d  d  d  d  h  
h10  d  d  d  d  d  d  d  d  h  d  
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
s13  h  h  h  h  d  h  h  h  h  h  
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
p3   y  y  y  y  y  y  n  n  n  n  
p2   y  y  y  y  y  y  n  n  n  n  
```

## Full table with results

The script computes the expected value of each combination

 1. Player’s hand (hard, soft and pair)
 2. Dealer upcard
 3. Hit, soft and stand (for hards and softs) and splitting or not (for pairs)
 
The results are given as the expected value in percentage with the uncertainty (one standard deviation) in the last significant digit.
 

 
```{=html}
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
  <td>pA</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center " style='background-color: rgb(108,230,141)'>+44(5)</div><div class="text-center " style='background-color: rgb(171,188,152)'>+6(3)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(105,231,140)'>+46(5)</div><div class="text-center " style='background-color: rgb(161,197,151)'>+13(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(76,243,131)'>+61(5)</div><div class="text-center " style='background-color: rgb(163,195,152)'>+11(3)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(79,242,132)'>+60(5)</div><div class="text-center " style='background-color: rgb(158,199,151)'>+14(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(48,250,121)'>+76(5)</div><div class="text-center " style='background-color: rgb(169,190,152)'>+8(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(104,232,139)'>+46(5)</div><div class="text-center " style='background-color: rgb(149,206,150)'>+20(3)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(115,227,143)'>+40(5)</div><div class="text-center " style='background-color: rgb(163,195,152)'>+12(3)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center " style='background-color: rgb(150,205,150)'>+20(5)</div><div class="text-center " style='background-color: rgb(178,181,152)'>+1(3)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(183,176,152)'>-2(5)</div><div class="text-center text-white" style='background-color: rgb(205,151,150)'>-19(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(214,138,148)'>-27(4)</div><div class="text-center text-white" style='background-color: rgb(223,123,145)'>-36(3)</div> </td>
 <tr>
  <td>pT</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center " style='background-color: rgb(93,237,136)'>+52(5)</div><div class="text-center " style='background-color: rgb(76,243,131)'>+61(2)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(111,229,142)'>+42(5)</div><div class="text-center " style='background-color: rgb(64,246,127)'>+67(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(87,239,134)'>+55(5)</div><div class="text-center " style='background-color: rgb(67,245,128)'>+66(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(100,234,138)'>+49(5)</div><div class="text-center " style='background-color: rgb(58,248,124)'>+70(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(80,241,132)'>+59(5)</div><div class="text-center " style='background-color: rgb(66,246,127)'>+66(2)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(100,234,139)'>+48(5)</div><div class="text-center " style='background-color: rgb(45,250,119)'>+77(2)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(119,225,144)'>+38(5)</div><div class="text-center " style='background-color: rgb(37,252,116)'>+81(2)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center " style='background-color: rgb(142,211,149)'>+25(4)</div><div class="text-center " style='background-color: rgb(48,250,121)'>+75(2)</div> </td>
 <!-- T -->
 <td>
<div class="text-center " style='background-color: rgb(175,185,152)'>+4(5)</div><div class="text-center " style='background-color: rgb(110,230,141)'>+43(2)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,143,149)'>-24(4)</div><div class="text-center " style='background-color: rgb(167,192,152)'>+9(3)</div> </td>
 <tr>
  <td>p9</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center " style='background-color: rgb(154,203,151)'>+17(2)</div><div class="text-center " style='background-color: rgb(164,194,152)'>+10.7(9)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(134,216,147)'>+29(6)</div><div class="text-center " style='background-color: rgb(160,198,151)'>+13(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(137,215,148)'>+28(2)</div><div class="text-center " style='background-color: rgb(155,202,151)'>+16.6(9)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(111,229,142)'>+42(6)</div><div class="text-center " style='background-color: rgb(156,201,151)'>+16(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(122,223,144)'>+36(6)</div><div class="text-center " style='background-color: rgb(148,207,150)'>+21(3)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(119,225,144)'>+37.7(5)</div><div class="text-center " style='background-color: rgb(115,227,143)'>+39.9(3)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(144,210,149)'>+23(5)</div><div class="text-center " style='background-color: rgb(169,190,152)'>+7(2)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(193,166,152)'>-10(2)</div><div class="text-center text-white" style='background-color: rgb(202,155,151)'>-16.5(9)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(230,109,141)'>-43(5)</div><div class="text-center text-white" style='background-color: rgb(213,139,148)'>-26(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(233,101,139)'>-47.9(4)</div><div class="text-center text-white" style='background-color: rgb(232,104,140)'>-46.3(3)</div> </td>
 <tr>
  <td>p8</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(184,176,152)'>-3(7)</div><div class="text-center text-white" style='background-color: rgb(208,146,149)'>-22(3)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(166,193,152)'>+10(7)</div><div class="text-center text-white" style='background-color: rgb(215,136,148)'>-28(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(151,205,150)'>+19(7)</div><div class="text-center text-white" style='background-color: rgb(206,149,150)'>-20(3)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(151,205,150)'>+19(7)</div><div class="text-center text-white" style='background-color: rgb(199,159,151)'>-14(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(140,213,148)'>+26(7)</div><div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12(3)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(139,213,148)'>+26(6)</div><div class="text-center text-white" style='background-color: rgb(228,113,142)'>-41(3)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(188,171,152)'>-6(6)</div><div class="text-center text-white" style='background-color: rgb(232,104,139)'>-46(3)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(226,117,143)'>-39(2)</div><div class="text-center text-white" style='background-color: rgb(236,95,137)'>-51.4(8)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,96,137)'>-51(5)</div><div class="text-center text-white" style='background-color: rgb(242,78,131)'>-60(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(247,63,126)'>-68.13(1)</div><div class="text-center text-white" style='background-color: rgb(247,62,126)'>-68.40(1)</div> </td>
 <tr>
  <td>p7</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(195,164,152)'>-11(7)</div><div class="text-center text-white" style='background-color: rgb(221,125,145)'>-34(3)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(195,163,152)'>-11(8)</div><div class="text-center text-white" style='background-color: rgb(211,142,149)'>-25(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(180,180,152)'>-0(8)</div><div class="text-center text-white" style='background-color: rgb(206,150,150)'>-20(3)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(160,198,151)'>+13(8)</div><div class="text-center text-white" style='background-color: rgb(209,144,149)'>-23(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(173,187,152)'>+5(8)</div><div class="text-center text-white" style='background-color: rgb(202,154,151)'>-17(3)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(202,155,151)'>-17(6)</div><div class="text-center text-white" style='background-color: rgb(220,127,146)'>-33(3)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(226,117,143)'>-39.02(1)</div><div class="text-center text-white" style='background-color: rgb(224,120,144)'>-37.11(1)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,82,133)'>-58(6)</div><div class="text-center text-white" style='background-color: rgb(230,109,141)'>-43(3)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,53,123)'>-73(5)</div><div class="text-center text-white" style='background-color: rgb(234,99,138)'>-49(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(251,44,119)'>-78(4)</div><div class="text-center text-white" style='background-color: rgb(246,65,127)'>-67(2)</div> </td>
 <tr>
  <td>p6</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(207,147,150)'>-21.3(7)</div><div class="text-center text-white" style='background-color: rgb(212,141,148)'>-25.4(3)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12(2)</div><div class="text-center text-white" style='background-color: rgb(210,143,149)'>-23.9(9)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(192,167,152)'>-9(8)</div><div class="text-center text-white" style='background-color: rgb(212,141,149)'>-25(3)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(183,177,152)'>-2(8)</div><div class="text-center text-white" style='background-color: rgb(201,156,151)'>-16(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(154,202,151)'>+17(8)</div><div class="text-center text-white" style='background-color: rgb(194,164,152)'>-11(3)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(213,139,148)'>-26(2)</div><div class="text-center text-white" style='background-color: rgb(208,147,150)'>-21.6(9)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(222,125,145)'>-35(5)</div><div class="text-center text-white" style='background-color: rgb(212,141,149)'>-25(3)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,80,132)'>-59(5)</div><div class="text-center text-white" style='background-color: rgb(218,130,146)'>-31(3)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,81,132)'>-59(5)</div><div class="text-center text-white" style='background-color: rgb(228,112,142)'>-42(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(251,40,117)'>-80(4)</div><div class="text-center text-white" style='background-color: rgb(238,90,135)'>-54(3)</div> </td>
 <tr>
  <td>p5</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(191,168,152)'>-8(7)</div><div class="text-center " style='background-color: rgb(114,227,142)'>+41(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(205,151,150)'>-19(7)</div><div class="text-center " style='background-color: rgb(118,225,144)'>+38(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(190,169,152)'>-7(8)</div><div class="text-center " style='background-color: rgb(106,231,140)'>+45(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(182,177,152)'>-2(8)</div><div class="text-center " style='background-color: rgb(88,239,135)'>+55(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(165,194,152)'>+10(8)</div><div class="text-center " style='background-color: rgb(81,241,132)'>+59(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(204,151,150)'>-19(5)</div><div class="text-center " style='background-color: rgb(94,236,137)'>+52(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(209,145,149)'>-23(6)</div><div class="text-center " style='background-color: rgb(127,220,146)'>+33(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,79,132)'>-60(5)</div><div class="text-center " style='background-color: rgb(165,193,152)'>+10(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,58,124)'>-70(5)</div><div class="text-center text-white" style='background-color: rgb(188,171,152)'>-6(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(251,41,118)'>-79(4)</div><div class="text-center text-white" style='background-color: rgb(224,121,144)'>-37(5)</div> </td>
 <tr>
  <td>p4</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(205,150,150)'>-20(6)</div><div class="text-center text-white" style='background-color: rgb(183,176,152)'>-2(3)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(199,159,151)'>-14(7)</div><div class="text-center " style='background-color: rgb(179,181,152)'>+1(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(183,177,152)'>-2(2)</div><div class="text-center " style='background-color: rgb(175,184,152)'>+3(1)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(145,209,149)'>+23(8)</div><div class="text-center " style='background-color: rgb(171,188,152)'>+6(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(157,200,151)'>+15(2)</div><div class="text-center " style='background-color: rgb(168,191,152)'>+8(1)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(203,153,151)'>-18(6)</div><div class="text-center " style='background-color: rgb(164,194,152)'>+10(3)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(217,133,147)'>-30(6)</div><div class="text-center text-white" style='background-color: rgb(183,176,152)'>-3(3)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,81,133)'>-58(5)</div><div class="text-center text-white" style='background-color: rgb(212,141,148)'>-25(3)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,92,136)'>-53(5)</div><div class="text-center text-white" style='background-color: rgb(215,136,148)'>-28(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(250,47,120)'>-76(4)</div><div class="text-center text-white" style='background-color: rgb(236,95,137)'>-51(3)</div> </td>
 <tr>
  <td>p3</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(195,163,152)'>-12(2)</div><div class="text-center text-white" style='background-color: rgb(201,155,151)'>-16(1)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(179,181,152)'>+1(7)</div><div class="text-center text-white" style='background-color: rgb(200,156,151)'>-16(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(175,184,152)'>+3(2)</div><div class="text-center text-white" style='background-color: rgb(189,171,152)'>-6(1)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(166,192,152)'>+9(2)</div><div class="text-center text-white" style='background-color: rgb(184,175,152)'>-3(1)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(148,207,150)'>+21(8)</div><div class="text-center text-white" style='background-color: rgb(181,179,152)'>-1(3)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(187,172,152)'>-5(2)</div><div class="text-center text-white" style='background-color: rgb(202,155,151)'>-16.5(9)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(210,143,149)'>-24(2)</div><div class="text-center text-white" style='background-color: rgb(207,148,150)'>-21.1(9)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(228,112,142)'>-42(6)</div><div class="text-center text-white" style='background-color: rgb(210,143,149)'>-24(3)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,87,134)'>-56(5)</div><div class="text-center text-white" style='background-color: rgb(228,113,142)'>-41(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,56,123)'>-72(4)</div><div class="text-center text-white" style='background-color: rgb(234,99,138)'>-49(3)</div> </td>
 <tr>
  <td>p2</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(192,167,152)'>-8.6(6)</div><div class="text-center text-white" style='background-color: rgb(195,163,152)'>-11.2(3)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(184,176,152)'>-3(2)</div><div class="text-center text-white" style='background-color: rgb(192,166,152)'>-9(1)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(177,183,152)'>+2(2)</div><div class="text-center text-white" style='background-color: rgb(185,175,152)'>-3(1)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(165,194,152)'>+10(2)</div><div class="text-center text-white" style='background-color: rgb(181,179,152)'>-1(1)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(148,207,150)'>+21(8)</div><div class="text-center text-white" style='background-color: rgb(182,177,152)'>-2(3)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(178,182,152)'>+2(2)</div><div class="text-center text-white" style='background-color: rgb(192,167,152)'>-9(1)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(203,153,151)'>-17.56(1)</div><div class="text-center text-white" style='background-color: rgb(201,156,151)'>-15.99(1)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(223,122,145)'>-36(2)</div><div class="text-center text-white" style='background-color: rgb(211,142,149)'>-24.2(9)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,94,137)'>-52(5)</div><div class="text-center text-white" style='background-color: rgb(218,130,146)'>-31(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,78,131)'>-60(4)</div><div class="text-center text-white" style='background-color: rgb(234,100,138)'>-48(3)</div> </td>

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
<div class="text-center " style='background-color: rgb(69,245,128)'>+65(6)</div><div class="text-center " style='background-color: rgb(147,208,150)'>+22(3)</div><div class="text-center " style='background-color: rgb(131,218,146)'>+31(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(63,246,126)'>+68(6)</div><div class="text-center " style='background-color: rgb(152,204,150)'>+18(3)</div><div class="text-center " style='background-color: rgb(126,221,145)'>+34(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(71,244,129)'>+64(6)</div><div class="text-center " style='background-color: rgb(147,207,150)'>+21(3)</div><div class="text-center " style='background-color: rgb(109,230,141)'>+44(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(67,245,127)'>+66(2)</div><div class="text-center " style='background-color: rgb(142,211,149)'>+24.6(9)</div><div class="text-center " style='background-color: rgb(90,238,135)'>+54(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(60,247,125)'>+69(6)</div><div class="text-center " style='background-color: rgb(136,215,148)'>+28(3)</div><div class="text-center " style='background-color: rgb(93,237,136)'>+52(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(49,250,121)'>+75(6)</div><div class="text-center " style='background-color: rgb(132,217,147)'>+30(3)</div><div class="text-center " style='background-color: rgb(99,234,138)'>+49(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(44,251,119)'>+78(6)</div><div class="text-center " style='background-color: rgb(145,209,149)'>+23(3)</div><div class="text-center " style='background-color: rgb(137,214,148)'>+27(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center " style='background-color: rgb(53,249,122)'>+73(6)</div><div class="text-center " style='background-color: rgb(159,198,151)'>+14(3)</div><div class="text-center " style='background-color: rgb(165,193,152)'>+10(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center " style='background-color: rgb(108,230,141)'>+44(6)</div><div class="text-center text-white" style='background-color: rgb(188,172,152)'>-6(3)</div><div class="text-center text-white" style='background-color: rgb(185,174,152)'>-4(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center " style='background-color: rgb(170,189,152)'>+7(5)</div><div class="text-center text-white" style='background-color: rgb(214,137,148)'>-27(3)</div><div class="text-center text-white" style='background-color: rgb(221,126,145)'>-34(5)</div> </td>
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
<div class="text-center " style='background-color: rgb(117,226,143)'>+39(6)</div><div class="text-center " style='background-color: rgb(166,192,152)'>+9(3)</div><div class="text-center " style='background-color: rgb(140,212,148)'>+26(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(117,226,143)'>+39(2)</div><div class="text-center " style='background-color: rgb(158,199,151)'>+14.6(9)</div><div class="text-center " style='background-color: rgb(130,219,146)'>+32(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(114,227,142)'>+41(2)</div><div class="text-center " style='background-color: rgb(152,204,150)'>+18.2(9)</div><div class="text-center " style='background-color: rgb(128,220,146)'>+33(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(109,230,141)'>+43.5(6)</div><div class="text-center " style='background-color: rgb(149,206,150)'>+20.0(3)</div><div class="text-center " style='background-color: rgb(116,227,143)'>+39.8(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(106,231,140)'>+45.35(1)</div><div class="text-center " style='background-color: rgb(144,209,149)'>+23.15(1)</div><div class="text-center " style='background-color: rgb(104,232,140)'>+46.06(1)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(72,244,129)'>+63(6)</div><div class="text-center " style='background-color: rgb(144,209,149)'>+23(3)</div><div class="text-center " style='background-color: rgb(120,224,144)'>+37(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(80,241,132)'>+59(6)</div><div class="text-center " style='background-color: rgb(162,196,152)'>+12(3)</div><div class="text-center " style='background-color: rgb(151,205,150)'>+19(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center " style='background-color: rgb(133,217,147)'>+30(6)</div><div class="text-center text-white" style='background-color: rgb(182,178,152)'>-1(3)</div><div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(184,175,152)'>-3(6)</div><div class="text-center text-white" style='background-color: rgb(203,153,151)'>-18(3)</div><div class="text-center text-white" style='background-color: rgb(226,116,143)'>-40(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(198,160,151)'>-13(5)</div><div class="text-center text-white" style='background-color: rgb(220,127,146)'>-33(3)</div><div class="text-center text-white" style='background-color: rgb(234,101,139)'>-48(5)</div> </td>
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
<div class="text-center " style='background-color: rgb(164,195,152)'>+10.99(1)</div><div class="text-center " style='background-color: rgb(171,188,152)'>+5.88(1)</div><div class="text-center " style='background-color: rgb(162,196,152)'>+11.78(1)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(160,198,151)'>+13(2)</div><div class="text-center " style='background-color: rgb(165,194,152)'>+10(1)</div><div class="text-center " style='background-color: rgb(148,207,150)'>+21(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(156,201,151)'>+16(2)</div><div class="text-center " style='background-color: rgb(161,197,151)'>+13(1)</div><div class="text-center " style='background-color: rgb(141,211,149)'>+25(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(149,206,150)'>+20(6)</div><div class="text-center " style='background-color: rgb(160,198,151)'>+14(3)</div><div class="text-center " style='background-color: rgb(125,221,145)'>+34(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(145,209,149)'>+22(2)</div><div class="text-center " style='background-color: rgb(151,204,150)'>+18.9(9)</div><div class="text-center " style='background-color: rgb(118,225,143)'>+38(2)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(115,227,143)'>+40(2)</div><div class="text-center " style='background-color: rgb(154,202,151)'>+16.9(9)</div><div class="text-center " style='background-color: rgb(149,206,150)'>+20(2)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(164,195,152)'>+11(2)</div><div class="text-center " style='background-color: rgb(173,186,152)'>+4.5(9)</div><div class="text-center text-white" style='background-color: rgb(185,174,152)'>-4(2)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(203,153,151)'>-17(2)</div><div class="text-center text-white" style='background-color: rgb(193,166,152)'>-9.4(9)</div><div class="text-center text-white" style='background-color: rgb(214,137,148)'>-28(2)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-24(2)</div><div class="text-center text-white" style='background-color: rgb(206,149,150)'>-20.4(9)</div><div class="text-center text-white" style='background-color: rgb(226,117,143)'>-39(2)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(235,98,138)'>-49(5)</div><div class="text-center text-white" style='background-color: rgb(227,114,143)'>-40(3)</div><div class="text-center text-white" style='background-color: rgb(246,66,127)'>-66(5)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(200,156,151)'>-15.59(1)</div><div class="text-center text-white" style='background-color: rgb(181,179,152)'>-0.66(1)</div><div class="text-center text-white" style='background-color: rgb(182,178,152)'>-1.22(1)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(195,163,152)'>-11(6)</div><div class="text-center text-white" style='background-color: rgb(181,179,152)'>-1(3)</div><div class="text-center " style='background-color: rgb(166,193,152)'>+10(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(188,171,152)'>-6(6)</div><div class="text-center " style='background-color: rgb(177,182,152)'>+2(3)</div><div class="text-center " style='background-color: rgb(163,195,152)'>+11(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(180,179,152)'>-0(6)</div><div class="text-center " style='background-color: rgb(169,190,152)'>+7(3)</div><div class="text-center " style='background-color: rgb(130,218,146)'>+31(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(182,178,152)'>-2(6)</div><div class="text-center " style='background-color: rgb(164,195,152)'>+11(3)</div><div class="text-center " style='background-color: rgb(141,212,149)'>+25(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(192,167,152)'>-9(6)</div><div class="text-center " style='background-color: rgb(171,188,152)'>+6(3)</div><div class="text-center text-white" style='background-color: rgb(186,174,152)'>-4(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(222,124,145)'>-35(6)</div><div class="text-center text-white" style='background-color: rgb(189,171,152)'>-6(3)</div><div class="text-center text-white" style='background-color: rgb(210,144,149)'>-23(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(227,114,142)'>-41(6)</div><div class="text-center text-white" style='background-color: rgb(207,148,150)'>-21(3)</div><div class="text-center text-white" style='background-color: rgb(220,127,146)'>-33(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(231,105,140)'>-46(6)</div><div class="text-center text-white" style='background-color: rgb(207,148,150)'>-21(3)</div><div class="text-center text-white" style='background-color: rgb(236,96,137)'>-51(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(245,69,128)'>-65(5)</div><div class="text-center text-white" style='background-color: rgb(233,101,139)'>-48(3)</div><div class="text-center text-white" style='background-color: rgb(245,69,128)'>-65(5)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(212,140,148)'>-26(6)</div><div class="text-center " style='background-color: rgb(180,180,152)'>+0(3)</div><div class="text-center text-white" style='background-color: rgb(201,156,151)'>-16(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(213,139,148)'>-26(2)</div><div class="text-center " style='background-color: rgb(178,182,152)'>+1(1)</div><div class="text-center text-white" style='background-color: rgb(186,173,152)'>-4(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(201,155,151)'>-16(6)</div><div class="text-center text-white" style='background-color: rgb(185,174,152)'>-4(3)</div><div class="text-center " style='background-color: rgb(170,189,152)'>+7(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(201,156,151)'>-16(2)</div><div class="text-center " style='background-color: rgb(171,189,152)'>+6(1)</div><div class="text-center " style='background-color: rgb(160,198,151)'>+13(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12(2)</div><div class="text-center " style='background-color: rgb(167,192,152)'>+9(1)</div><div class="text-center " style='background-color: rgb(152,204,150)'>+18(2)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(234,100,138)'>-48(6)</div><div class="text-center " style='background-color: rgb(176,184,152)'>+3(3)</div><div class="text-center text-white" style='background-color: rgb(205,150,150)'>-19(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,87,134)'>-56(6)</div><div class="text-center text-white" style='background-color: rgb(188,171,152)'>-6(3)</div><div class="text-center text-white" style='background-color: rgb(222,125,145)'>-35(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,88,135)'>-55(6)</div><div class="text-center text-white" style='background-color: rgb(194,164,152)'>-10(3)</div><div class="text-center text-white" style='background-color: rgb(234,100,139)'>-48(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(240,86,134)'>-56(6)</div><div class="text-center text-white" style='background-color: rgb(214,138,148)'>-27(3)</div><div class="text-center text-white" style='background-color: rgb(233,102,139)'>-47(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,54,123)'>-72(5)</div><div class="text-center text-white" style='background-color: rgb(233,102,139)'>-47(3)</div><div class="text-center text-white" style='background-color: rgb(246,63,126)'>-68(5)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(214,138,148)'>-27(2)</div><div class="text-center text-white" style='background-color: rgb(180,180,152)'>-0(1)</div><div class="text-center text-white" style='background-color: rgb(186,174,152)'>-4(2)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-24.6(6)</div><div class="text-center " style='background-color: rgb(177,183,152)'>+2.2(3)</div><div class="text-center text-white" style='background-color: rgb(182,178,152)'>-1.3(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(207,147,150)'>-21(2)</div><div class="text-center " style='background-color: rgb(173,187,152)'>+5(1)</div><div class="text-center " style='background-color: rgb(168,191,152)'>+8(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(201,156,151)'>-16(2)</div><div class="text-center " style='background-color: rgb(168,191,152)'>+8(1)</div><div class="text-center " style='background-color: rgb(159,198,151)'>+14(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(192,166,152)'>-9(6)</div><div class="text-center " style='background-color: rgb(164,195,152)'>+11(3)</div><div class="text-center " style='background-color: rgb(144,209,149)'>+23(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(233,102,139)'>-48(2)</div><div class="text-center " style='background-color: rgb(174,185,152)'>+4(1)</div><div class="text-center text-white" style='background-color: rgb(203,153,151)'>-17(2)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,89,135)'>-54(6)</div><div class="text-center text-white" style='background-color: rgb(185,174,152)'>-4(3)</div><div class="text-center text-white" style='background-color: rgb(221,126,145)'>-34(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,87,134)'>-55(6)</div><div class="text-center text-white" style='background-color: rgb(192,167,152)'>-9(3)</div><div class="text-center text-white" style='background-color: rgb(227,116,143)'>-40(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,82,133)'>-58(6)</div><div class="text-center text-white" style='background-color: rgb(210,143,149)'>-24(3)</div><div class="text-center text-white" style='background-color: rgb(244,73,130)'>-63(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,57,124)'>-71(5)</div><div class="text-center text-white" style='background-color: rgb(231,107,140)'>-45(3)</div><div class="text-center text-white" style='background-color: rgb(246,66,127)'>-66(5)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(213,139,148)'>-26(6)</div><div class="text-center " style='background-color: rgb(176,184,152)'>+3(3)</div><div class="text-center text-white" style='background-color: rgb(198,160,151)'>-13(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(209,145,149)'>-22(2)</div><div class="text-center " style='background-color: rgb(171,188,152)'>+6(1)</div><div class="text-center " style='background-color: rgb(180,180,152)'>+0(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(206,149,150)'>-20.5(6)</div><div class="text-center " style='background-color: rgb(168,190,152)'>+7.8(3)</div><div class="text-center " style='background-color: rgb(172,187,152)'>+5.5(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(200,157,151)'>-15(2)</div><div class="text-center " style='background-color: rgb(165,193,152)'>+10(1)</div><div class="text-center " style='background-color: rgb(159,198,151)'>+14(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(199,159,151)'>-14(6)</div><div class="text-center " style='background-color: rgb(162,196,152)'>+12(3)</div><div class="text-center " style='background-color: rgb(144,210,149)'>+23(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(234,99,138)'>-49(6)</div><div class="text-center " style='background-color: rgb(167,192,152)'>+9(3)</div><div class="text-center text-white" style='background-color: rgb(215,135,148)'>-28(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(235,98,138)'>-49(6)</div><div class="text-center text-white" style='background-color: rgb(184,175,152)'>-3(3)</div><div class="text-center text-white" style='background-color: rgb(223,122,145)'>-36(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,86,134)'>-56(6)</div><div class="text-center text-white" style='background-color: rgb(193,166,152)'>-10(3)</div><div class="text-center text-white" style='background-color: rgb(225,118,143)'>-39(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,87,134)'>-56(6)</div><div class="text-center text-white" style='background-color: rgb(205,151,150)'>-19(3)</div><div class="text-center text-white" style='background-color: rgb(243,74,130)'>-62(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,57,124)'>-71(5)</div><div class="text-center text-white" style='background-color: rgb(227,115,143)'>-40(3)</div><div class="text-center text-white" style='background-color: rgb(245,68,128)'>-65(5)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(213,140,148)'>-26(6)</div><div class="text-center " style='background-color: rgb(168,191,152)'>+8(3)</div><div class="text-center text-white" style='background-color: rgb(205,151,150)'>-19(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-25(2)</div><div class="text-center " style='background-color: rgb(171,188,152)'>+6(1)</div><div class="text-center text-white" style='background-color: rgb(183,177,152)'>-2(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(206,148,150)'>-21(2)</div><div class="text-center " style='background-color: rgb(166,193,152)'>+9(1)</div><div class="text-center " style='background-color: rgb(171,188,152)'>+6(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(201,155,151)'>-16.38(1)</div><div class="text-center " style='background-color: rgb(160,197,151)'>+13.06(1)</div><div class="text-center " style='background-color: rgb(161,197,151)'>+12.78(1)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(195,163,152)'>-11.5(6)</div><div class="text-center " style='background-color: rgb(160,198,151)'>+13.5(3)</div><div class="text-center " style='background-color: rgb(152,204,150)'>+18.7(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(230,110,141)'>-43(6)</div><div class="text-center " style='background-color: rgb(161,196,152)'>+12(3)</div><div class="text-center text-white" style='background-color: rgb(209,144,149)'>-23(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(235,98,138)'>-49(6)</div><div class="text-center " style='background-color: rgb(175,185,152)'>+3(3)</div><div class="text-center text-white" style='background-color: rgb(217,133,147)'>-30(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,87,134)'>-55(6)</div><div class="text-center text-white" style='background-color: rgb(181,178,152)'>-1(3)</div><div class="text-center text-white" style='background-color: rgb(233,102,139)'>-47(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,77,131)'>-61(6)</div><div class="text-center text-white" style='background-color: rgb(203,153,151)'>-18(3)</div><div class="text-center text-white" style='background-color: rgb(242,77,131)'>-61(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,53,122)'>-73(5)</div><div class="text-center text-white" style='background-color: rgb(221,127,146)'>-34(3)</div><div class="text-center text-white" style='background-color: rgb(248,59,125)'>-70(5)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(216,135,147)'>-29(2)</div><div class="text-center " style='background-color: rgb(167,192,152)'>+9(1)</div><div class="text-center text-white" style='background-color: rgb(190,169,152)'>-7(2)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(204,152,150)'>-18(6)</div><div class="text-center " style='background-color: rgb(162,196,152)'>+12(3)</div><div class="text-center text-white" style='background-color: rgb(183,177,152)'>-2(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(210,143,149)'>-24(6)</div><div class="text-center " style='background-color: rgb(148,207,150)'>+21(3)</div><div class="text-center " style='background-color: rgb(174,186,152)'>+4(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(203,153,150)'>-18(2)</div><div class="text-center " style='background-color: rgb(156,200,151)'>+16(1)</div><div class="text-center " style='background-color: rgb(164,195,152)'>+11(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12(2)</div><div class="text-center " style='background-color: rgb(156,201,151)'>+16(1)</div><div class="text-center " style='background-color: rgb(147,207,150)'>+21(2)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(234,100,138)'>-48(6)</div><div class="text-center " style='background-color: rgb(164,194,152)'>+11(3)</div><div class="text-center text-white" style='background-color: rgb(207,147,150)'>-21(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,93,136)'>-52(6)</div><div class="text-center " style='background-color: rgb(168,191,152)'>+8(3)</div><div class="text-center text-white" style='background-color: rgb(219,129,146)'>-32(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,87,134)'>-55(6)</div><div class="text-center text-white" style='background-color: rgb(185,175,152)'>-4(3)</div><div class="text-center text-white" style='background-color: rgb(228,112,142)'>-42(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,78,131)'>-60(6)</div><div class="text-center text-white" style='background-color: rgb(208,147,150)'>-22(3)</div><div class="text-center text-white" style='background-color: rgb(236,95,137)'>-51(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(245,68,128)'>-66(5)</div><div class="text-center text-white" style='background-color: rgb(223,122,144)'>-36(3)</div><div class="text-center text-white" style='background-color: rgb(249,50,121)'>-75(5)</div> </td>
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
  <td>h20</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
 <!-- 2 -->
 <td>
<div class="text-center " style='background-color: rgb(72,244,129)'>+63(3)</div><div class="text-center text-white" style='background-color: rgb(253,31,114)'>-84(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-172(3)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(75,243,130)'>+62(3)</div><div class="text-center text-white" style='background-color: rgb(253,26,112)'>-87(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-171(3)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(69,245,128)'>+65(3)</div><div class="text-center text-white" style='background-color: rgb(254,20,110)'>-90(1)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-172(3)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(64,246,127)'>+67(3)</div><div class="text-center text-white" style='background-color: rgb(253,25,112)'>-87(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-172(3)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(62,247,126)'>+68(3)</div><div class="text-center text-white" style='background-color: rgb(253,28,113)'>-86(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-172(3)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(47,250,120)'>+76(3)</div><div class="text-center text-white" style='background-color: rgb(253,31,114)'>-84(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-170(3)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(47,250,120)'>+76(3)</div><div class="text-center text-white" style='background-color: rgb(253,30,114)'>-85(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-169(3)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center " style='background-color: rgb(48,250,121)'>+76(3)</div><div class="text-center text-white" style='background-color: rgb(252,33,115)'>-83(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-170(3)</div> </td>
 <!-- T -->
 <td>
<div class="text-center " style='background-color: rgb(101,233,139)'>+48(3)</div><div class="text-center text-white" style='background-color: rgb(253,29,113)'>-85(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-162(3)</div> </td>
 <!-- A -->
 <td>
<div class="text-center " style='background-color: rgb(175,185,152)'>+3(3)</div><div class="text-center text-white" style='background-color: rgb(254,22,110)'>-89(1)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-152(3)</div> </td>
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
<div class="text-center " style='background-color: rgb(120,224,144)'>+38(4)</div><div class="text-center text-white" style='background-color: rgb(249,51,122)'>-74(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-143(4)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(109,230,141)'>+43(4)</div><div class="text-center text-white" style='background-color: rgb(248,58,124)'>-70(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-147(4)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(111,229,142)'>+43(4)</div><div class="text-center text-white" style='background-color: rgb(250,48,121)'>-76(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-144(4)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(108,230,141)'>+44(4)</div><div class="text-center text-white" style='background-color: rgb(249,54,123)'>-72(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-141(4)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(109,230,141)'>+44(4)</div><div class="text-center text-white" style='background-color: rgb(249,52,122)'>-73(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-139(4)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(77,243,131)'>+61(4)</div><div class="text-center text-white" style='background-color: rgb(249,52,122)'>-73(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-142(4)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(64,246,127)'>+67(5)</div><div class="text-center text-white" style='background-color: rgb(249,54,123)'>-73(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-138(5)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center " style='background-color: rgb(133,217,147)'>+30(4)</div><div class="text-center text-white" style='background-color: rgb(248,58,124)'>-70(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-149(4)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(182,178,152)'>-2(4)</div><div class="text-center text-white" style='background-color: rgb(250,48,120)'>-76(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-141(4)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(201,155,151)'>-16(4)</div><div class="text-center text-white" style='background-color: rgb(252,35,115)'>-82(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-134(4)</div> </td>
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
<div class="text-center " style='background-color: rgb(166,193,152)'>+9(5)</div><div class="text-center text-white" style='background-color: rgb(245,68,128)'>-65(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-128(5)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center " style='background-color: rgb(154,203,151)'>+17(5)</div><div class="text-center text-white" style='background-color: rgb(243,74,130)'>-62(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-127(5)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center " style='background-color: rgb(155,201,151)'>+16(5)</div><div class="text-center text-white" style='background-color: rgb(244,72,129)'>-63(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-123(5)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center " style='background-color: rgb(154,202,151)'>+17(5)</div><div class="text-center text-white" style='background-color: rgb(242,79,132)'>-60(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-127(5)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(147,208,150)'>+22(5)</div><div class="text-center text-white" style='background-color: rgb(244,73,130)'>-63(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-120(5)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center " style='background-color: rgb(116,227,143)'>+40(5)</div><div class="text-center text-white" style='background-color: rgb(240,84,134)'>-57(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-121(5)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center " style='background-color: rgb(161,197,152)'>+12(5)</div><div class="text-center text-white" style='background-color: rgb(244,73,130)'>-63(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-119(5)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(206,149,150)'>-20(5)</div><div class="text-center text-white" style='background-color: rgb(241,82,133)'>-58(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-124(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(210,143,149)'>-24(5)</div><div class="text-center text-white" style='background-color: rgb(249,54,123)'>-73(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-122(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(231,107,140)'>-45(4)</div><div class="text-center text-white" style='background-color: rgb(250,49,121)'>-75(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-114(4)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(200,156,151)'>-16(5)</div><div class="text-center text-white" style='background-color: rgb(240,84,133)'>-57(3)</div><div class="text-center text-white" style='background-color: rgb(254,1,102)'>-99(5)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(201,156,151)'>-16(5)</div><div class="text-center text-white" style='background-color: rgb(239,86,134)'>-56(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-106(5)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(192,167,152)'>-9(5)</div><div class="text-center text-white" style='background-color: rgb(239,88,135)'>-55(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-107(5)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(183,177,152)'>-2(5)</div><div class="text-center text-white" style='background-color: rgb(237,91,136)'>-53(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-106(5)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center " style='background-color: rgb(174,186,152)'>+4(5)</div><div class="text-center text-white" style='background-color: rgb(238,91,136)'>-53(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-105(5)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(197,161,152)'>-12(5)</div><div class="text-center text-white" style='background-color: rgb(235,98,138)'>-49(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-103(5)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(224,120,144)'>-38(5)</div><div class="text-center text-white" style='background-color: rgb(240,83,133)'>-57(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-105(5)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(227,115,143)'>-40(5)</div><div class="text-center text-white" style='background-color: rgb(237,92,136)'>-52(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-114(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(234,99,138)'>-49(5)</div><div class="text-center text-white" style='background-color: rgb(243,74,130)'>-62(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-121(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(245,69,128)'>-65(4)</div><div class="text-center text-white" style='background-color: rgb(248,55,123)'>-72(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-109(4)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(215,136,148)'>-28(5)</div><div class="text-center text-white" style='background-color: rgb(230,108,141)'>-44(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-101(5)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(210,143,149)'>-24(5)</div><div class="text-center text-white" style='background-color: rgb(236,96,137)'>-51(3)</div><div class="text-center text-white" style='background-color: rgb(254,2,102)'>-99(5)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(205,150,150)'>-20(5)</div><div class="text-center text-white" style='background-color: rgb(233,103,139)'>-47(3)</div><div class="text-center text-white" style='background-color: rgb(254,4,103)'>-98(5)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(208,146,149)'>-22(6)</div><div class="text-center text-white" style='background-color: rgb(229,111,142)'>-42(3)</div><div class="text-center text-white" style='background-color: rgb(253,25,112)'>-87(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(194,164,152)'>-11(5)</div><div class="text-center text-white" style='background-color: rgb(233,102,139)'>-47(3)</div><div class="text-center text-white" style='background-color: rgb(254,4,103)'>-98(5)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,93,136)'>-52(6)</div><div class="text-center text-white" style='background-color: rgb(228,113,142)'>-41(3)</div><div class="text-center text-white" style='background-color: rgb(251,42,118)'>-79(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,93,136)'>-52(5)</div><div class="text-center text-white" style='background-color: rgb(230,109,141)'>-43(3)</div><div class="text-center text-white" style='background-color: rgb(254,13,107)'>-93(5)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,88,135)'>-55(2)</div><div class="text-center text-white" style='background-color: rgb(234,99,138)'>-49.0(8)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-103(2)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(240,83,133)'>-57.55(1)</div><div class="text-center text-white" style='background-color: rgb(240,83,133)'>-57.58(1)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-107.30(1)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,53,122)'>-73(1)</div><div class="text-center text-white" style='background-color: rgb(247,61,125)'>-68.9(7)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-104(1)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(217,132,147)'>-30(5)</div><div class="text-center text-white" style='background-color: rgb(228,112,142)'>-42(3)</div><div class="text-center text-white" style='background-color: rgb(254,8,105)'>-96(5)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(204,152,150)'>-19(5)</div><div class="text-center text-white" style='background-color: rgb(222,124,145)'>-35(3)</div><div class="text-center text-white" style='background-color: rgb(253,23,111)'>-88(5)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(203,153,151)'>-18(6)</div><div class="text-center text-white" style='background-color: rgb(225,118,144)'>-38(3)</div><div class="text-center text-white" style='background-color: rgb(247,59,125)'>-70(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(200,157,151)'>-15(6)</div><div class="text-center text-white" style='background-color: rgb(224,120,144)'>-37(3)</div><div class="text-center text-white" style='background-color: rgb(247,63,126)'>-68(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(202,155,151)'>-17(6)</div><div class="text-center text-white" style='background-color: rgb(222,124,145)'>-35(3)</div><div class="text-center text-white" style='background-color: rgb(249,53,122)'>-73(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,93,136)'>-52(6)</div><div class="text-center text-white" style='background-color: rgb(225,118,144)'>-38(3)</div><div class="text-center text-white" style='background-color: rgb(251,44,119)'>-78(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,95,137)'>-51(2)</div><div class="text-center text-white" style='background-color: rgb(228,112,142)'>-41.7(9)</div><div class="text-center text-white" style='background-color: rgb(253,31,114)'>-84(2)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,79,132)'>-60(5)</div><div class="text-center text-white" style='background-color: rgb(229,111,142)'>-42(3)</div><div class="text-center text-white" style='background-color: rgb(254,11,106)'>-94(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,82,133)'>-57.9(5)</div><div class="text-center text-white" style='background-color: rgb(238,89,135)'>-54.4(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-101.4(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,54,123)'>-72(4)</div><div class="text-center text-white" style='background-color: rgb(246,66,127)'>-66(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-103(4)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(217,133,147)'>-30(2)</div><div class="text-center text-white" style='background-color: rgb(224,121,144)'>-36.8(9)</div><div class="text-center text-white" style='background-color: rgb(249,50,121)'>-75(2)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-25(2)</div><div class="text-center text-white" style='background-color: rgb(221,126,145)'>-34.2(9)</div><div class="text-center text-white" style='background-color: rgb(246,63,126)'>-68(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(208,146,149)'>-22(6)</div><div class="text-center text-white" style='background-color: rgb(225,119,144)'>-38(3)</div><div class="text-center text-white" style='background-color: rgb(247,61,126)'>-69(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(197,161,151)'>-13(6)</div><div class="text-center text-white" style='background-color: rgb(214,138,148)'>-27(3)</div><div class="text-center text-white" style='background-color: rgb(249,52,122)'>-73(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(197,160,151)'>-13(2)</div><div class="text-center text-white" style='background-color: rgb(219,130,146)'>-31.6(9)</div><div class="text-center text-white" style='background-color: rgb(243,75,130)'>-62(2)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(234,99,138)'>-49(6)</div><div class="text-center text-white" style='background-color: rgb(219,129,146)'>-32(3)</div><div class="text-center text-white" style='background-color: rgb(243,74,130)'>-62(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,90,135)'>-54(6)</div><div class="text-center text-white" style='background-color: rgb(224,121,144)'>-37(3)</div><div class="text-center text-white" style='background-color: rgb(252,34,115)'>-83(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,90,135)'>-54(5)</div><div class="text-center text-white" style='background-color: rgb(228,113,142)'>-41(3)</div><div class="text-center text-white" style='background-color: rgb(254,15,108)'>-92(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,81,132)'>-58(2)</div><div class="text-center text-white" style='background-color: rgb(236,94,137)'>-51.4(8)</div><div class="text-center text-white" style='background-color: rgb(254,15,108)'>-92(2)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,56,123)'>-72(4)</div><div class="text-center text-white" style='background-color: rgb(240,83,133)'>-58(2)</div><div class="text-center text-white" style='background-color: rgb(254,19,109)'>-90(4)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(215,136,148)'>-28.3(6)</div><div class="text-center text-white" style='background-color: rgb(217,132,147)'>-30.4(3)</div><div class="text-center text-white" style='background-color: rgb(244,73,130)'>-62.7(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,141,149)'>-25(2)</div><div class="text-center text-white" style='background-color: rgb(215,135,147)'>-28.6(9)</div><div class="text-center text-white" style='background-color: rgb(239,87,134)'>-55(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(207,148,150)'>-21(6)</div><div class="text-center text-white" style='background-color: rgb(219,130,146)'>-32(3)</div><div class="text-center text-white" style='background-color: rgb(240,83,133)'>-58(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(203,153,150)'>-18(6)</div><div class="text-center text-white" style='background-color: rgb(215,136,148)'>-28(3)</div><div class="text-center text-white" style='background-color: rgb(228,112,142)'>-42(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(189,170,152)'>-7(6)</div><div class="text-center text-white" style='background-color: rgb(208,146,150)'>-22(3)</div><div class="text-center text-white" style='background-color: rgb(236,94,137)'>-52(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(233,101,139)'>-48(6)</div><div class="text-center text-white" style='background-color: rgb(208,146,149)'>-22(3)</div><div class="text-center text-white" style='background-color: rgb(242,78,131)'>-60(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,96,137)'>-51(6)</div><div class="text-center text-white" style='background-color: rgb(220,127,146)'>-33(3)</div><div class="text-center text-white" style='background-color: rgb(248,57,124)'>-71(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,94,137)'>-52(6)</div><div class="text-center text-white" style='background-color: rgb(226,116,143)'>-39(3)</div><div class="text-center text-white" style='background-color: rgb(249,50,121)'>-75(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(242,79,132)'>-60(5)</div><div class="text-center text-white" style='background-color: rgb(235,97,138)'>-50(3)</div><div class="text-center text-white" style='background-color: rgb(254,10,106)'>-95(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,52,122)'>-73(4)</div><div class="text-center text-white" style='background-color: rgb(244,74,130)'>-62(2)</div><div class="text-center text-white" style='background-color: rgb(254,2,102)'>-99(4)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(215,135,147)'>-28.5(6)</div><div class="text-center text-white" style='background-color: rgb(211,141,149)'>-24.9(3)</div><div class="text-center text-white" style='background-color: rgb(236,96,137)'>-50.7(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-24.6(6)</div><div class="text-center text-white" style='background-color: rgb(210,144,149)'>-23.5(3)</div><div class="text-center text-white" style='background-color: rgb(232,104,140)'>-46.3(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(206,149,150)'>-20.3(6)</div><div class="text-center text-white" style='background-color: rgb(208,147,150)'>-21.5(3)</div><div class="text-center text-white" style='background-color: rgb(230,109,141)'>-43.6(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(201,155,151)'>-16(2)</div><div class="text-center text-white" style='background-color: rgb(205,150,150)'>-19(1)</div><div class="text-center text-white" style='background-color: rgb(230,108,141)'>-44(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12(2)</div><div class="text-center text-white" style='background-color: rgb(202,154,151)'>-17(1)</div><div class="text-center text-white" style='background-color: rgb(221,126,145)'>-34(2)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(232,104,140)'>-46(6)</div><div class="text-center text-white" style='background-color: rgb(213,139,148)'>-26(3)</div><div class="text-center text-white" style='background-color: rgb(238,90,135)'>-54(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,92,136)'>-53(6)</div><div class="text-center text-white" style='background-color: rgb(215,136,148)'>-28(3)</div><div class="text-center text-white" style='background-color: rgb(239,87,134)'>-55(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,90,135)'>-54(6)</div><div class="text-center text-white" style='background-color: rgb(224,121,144)'>-37(3)</div><div class="text-center text-white" style='background-color: rgb(248,58,124)'>-71(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,87,134)'>-56(5)</div><div class="text-center text-white" style='background-color: rgb(230,109,141)'>-43(3)</div><div class="text-center text-white" style='background-color: rgb(249,50,121)'>-74(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,54,123)'>-73(5)</div><div class="text-center text-white" style='background-color: rgb(238,89,135)'>-54(3)</div><div class="text-center text-white" style='background-color: rgb(253,31,114)'>-84(5)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(219,130,146)'>-32(6)</div><div class="text-center " style='background-color: rgb(141,212,149)'>+25(3)</div><div class="text-center " style='background-color: rgb(102,233,139)'>+48(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(206,149,150)'>-20(6)</div><div class="text-center " style='background-color: rgb(135,216,147)'>+29(3)</div><div class="text-center " style='background-color: rgb(85,240,134)'>+57(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(209,145,149)'>-22(6)</div><div class="text-center " style='background-color: rgb(133,217,147)'>+30(3)</div><div class="text-center " style='background-color: rgb(71,244,129)'>+64(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(205,151,150)'>-19(6)</div><div class="text-center " style='background-color: rgb(135,215,147)'>+29(3)</div><div class="text-center " style='background-color: rgb(74,243,130)'>+62(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(199,159,151)'>-14(6)</div><div class="text-center " style='background-color: rgb(136,215,148)'>+28(3)</div><div class="text-center " style='background-color: rgb(73,244,130)'>+63(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,94,137)'>-52(6)</div><div class="text-center " style='background-color: rgb(138,214,148)'>+27(3)</div><div class="text-center " style='background-color: rgb(104,232,140)'>+46(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(235,98,138)'>-49(6)</div><div class="text-center " style='background-color: rgb(151,205,150)'>+19(3)</div><div class="text-center " style='background-color: rgb(125,221,145)'>+34(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,91,136)'>-53(2)</div><div class="text-center " style='background-color: rgb(152,204,150)'>+18.4(9)</div><div class="text-center " style='background-color: rgb(136,215,148)'>+28(2)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,82,133)'>-58(2)</div><div class="text-center " style='background-color: rgb(175,184,152)'>+3(1)</div><div class="text-center " style='background-color: rgb(169,190,152)'>+8(2)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,54,123)'>-72.4(5)</div><div class="text-center text-white" style='background-color: rgb(210,144,149)'>-23.5(3)</div><div class="text-center text-white" style='background-color: rgb(211,142,149)'>-24.5(5)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(219,130,146)'>-32(6)</div><div class="text-center " style='background-color: rgb(163,195,152)'>+12(3)</div><div class="text-center " style='background-color: rgb(118,225,143)'>+39(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(209,145,149)'>-23(6)</div><div class="text-center " style='background-color: rgb(158,199,151)'>+15(3)</div><div class="text-center " style='background-color: rgb(103,232,139)'>+47(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(207,147,150)'>-21(6)</div><div class="text-center " style='background-color: rgb(144,210,149)'>+24(3)</div><div class="text-center " style='background-color: rgb(82,241,133)'>+58(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(204,152,150)'>-18(6)</div><div class="text-center " style='background-color: rgb(136,215,148)'>+28(3)</div><div class="text-center " style='background-color: rgb(106,231,140)'>+45(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12(6)</div><div class="text-center " style='background-color: rgb(130,218,146)'>+31(3)</div><div class="text-center " style='background-color: rgb(80,242,132)'>+59(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(232,104,140)'>-46(6)</div><div class="text-center " style='background-color: rgb(138,213,148)'>+27(3)</div><div class="text-center " style='background-color: rgb(94,236,137)'>+51(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,94,137)'>-52(2)</div><div class="text-center " style='background-color: rgb(150,205,150)'>+19.6(9)</div><div class="text-center " style='background-color: rgb(136,215,148)'>+28(2)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,89,135)'>-55(6)</div><div class="text-center " style='background-color: rgb(161,197,151)'>+13(3)</div><div class="text-center " style='background-color: rgb(146,208,149)'>+22(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,81,132)'>-59(2)</div><div class="text-center text-white" style='background-color: rgb(188,171,152)'>-5.9(9)</div><div class="text-center text-white" style='background-color: rgb(195,164,152)'>-11(2)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(247,60,125)'>-70(5)</div><div class="text-center text-white" style='background-color: rgb(216,134,147)'>-29(3)</div><div class="text-center text-white" style='background-color: rgb(207,148,150)'>-21(5)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-25(6)</div><div class="text-center " style='background-color: rgb(167,192,152)'>+9(3)</div><div class="text-center text-white" style='background-color: rgb(181,179,152)'>-1(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(212,140,148)'>-26(2)</div><div class="text-center " style='background-color: rgb(166,193,152)'>+9(1)</div><div class="text-center " style='background-color: rgb(161,197,151)'>+13(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(206,149,150)'>-20(2)</div><div class="text-center " style='background-color: rgb(162,196,152)'>+12(1)</div><div class="text-center " style='background-color: rgb(151,205,150)'>+19(2)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(204,152,150)'>-18(6)</div><div class="text-center " style='background-color: rgb(155,202,151)'>+17(3)</div><div class="text-center " style='background-color: rgb(137,214,148)'>+27(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(194,164,152)'>-11(2)</div><div class="text-center " style='background-color: rgb(150,205,150)'>+19.4(9)</div><div class="text-center " style='background-color: rgb(134,216,147)'>+29(2)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(233,103,139)'>-47(2)</div><div class="text-center " style='background-color: rgb(155,202,151)'>+16.7(9)</div><div class="text-center " style='background-color: rgb(170,190,152)'>+7(2)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,93,136)'>-52(6)</div><div class="text-center " style='background-color: rgb(166,192,152)'>+9(3)</div><div class="text-center text-white" style='background-color: rgb(183,176,152)'>-2(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,90,135)'>-54(6)</div><div class="text-center text-white" style='background-color: rgb(189,170,152)'>-7(3)</div><div class="text-center text-white" style='background-color: rgb(217,133,147)'>-30(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(243,75,130)'>-62(6)</div><div class="text-center text-white" style='background-color: rgb(205,151,150)'>-19(3)</div><div class="text-center text-white" style='background-color: rgb(237,92,136)'>-53(6)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,57,124)'>-71(5)</div><div class="text-center text-white" style='background-color: rgb(225,118,144)'>-38(3)</div><div class="text-center text-white" style='background-color: rgb(245,69,128)'>-65(5)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(215,135,147)'>-29(6)</div><div class="text-center text-white" style='background-color: rgb(185,174,152)'>-4(3)</div><div class="text-center text-white" style='background-color: rgb(203,153,150)'>-18(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(209,145,149)'>-23(6)</div><div class="text-center text-white" style='background-color: rgb(192,166,152)'>-9(3)</div><div class="text-center text-white" style='background-color: rgb(206,150,150)'>-20(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(208,146,149)'>-22(6)</div><div class="text-center " style='background-color: rgb(168,191,152)'>+8(3)</div><div class="text-center text-white" style='background-color: rgb(202,155,151)'>-17(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(201,155,151)'>-16(2)</div><div class="text-center " style='background-color: rgb(172,188,152)'>+6(1)</div><div class="text-center " style='background-color: rgb(176,183,152)'>+2(2)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12.0(6)</div><div class="text-center " style='background-color: rgb(164,194,152)'>+10.5(3)</div><div class="text-center " style='background-color: rgb(168,191,152)'>+8.2(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,90,135)'>-54(6)</div><div class="text-center " style='background-color: rgb(167,192,152)'>+9(3)</div><div class="text-center text-white" style='background-color: rgb(207,147,150)'>-21(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(236,94,137)'>-52(6)</div><div class="text-center " style='background-color: rgb(180,180,153)'>+0(3)</div><div class="text-center text-white" style='background-color: rgb(232,105,140)'>-46(6)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,88,135)'>-55(6)</div><div class="text-center text-white" style='background-color: rgb(205,150,150)'>-20(3)</div><div class="text-center text-white" style='background-color: rgb(246,65,127)'>-67(6)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(243,77,131)'>-61(5)</div><div class="text-center text-white" style='background-color: rgb(219,129,146)'>-32(3)</div><div class="text-center text-white" style='background-color: rgb(250,45,119)'>-77(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(250,49,121)'>-75(5)</div><div class="text-center text-white" style='background-color: rgb(232,104,140)'>-46(3)</div><div class="text-center text-white" style='background-color: rgb(253,23,111)'>-88(5)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(220,128,146)'>-33(6)</div><div class="text-center text-white" style='background-color: rgb(190,169,152)'>-7(3)</div><div class="text-center text-white" style='background-color: rgb(228,113,142)'>-41(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(207,148,150)'>-21(6)</div><div class="text-center text-white" style='background-color: rgb(190,169,152)'>-8(3)</div><div class="text-center text-white" style='background-color: rgb(222,124,145)'>-35(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(207,148,150)'>-21(6)</div><div class="text-center text-white" style='background-color: rgb(183,177,152)'>-2(3)</div><div class="text-center text-white" style='background-color: rgb(223,122,145)'>-36(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(198,160,151)'>-13(6)</div><div class="text-center " style='background-color: rgb(169,190,152)'>+8(3)</div><div class="text-center text-white" style='background-color: rgb(197,160,151)'>-13(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12(6)</div><div class="text-center " style='background-color: rgb(169,190,152)'>+8(3)</div><div class="text-center text-white" style='background-color: rgb(197,160,151)'>-13(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(231,106,140)'>-45(6)</div><div class="text-center text-white" style='background-color: rgb(189,170,152)'>-7(3)</div><div class="text-center text-white" style='background-color: rgb(234,99,138)'>-49(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,93,136)'>-52(5)</div><div class="text-center text-white" style='background-color: rgb(206,150,150)'>-20(3)</div><div class="text-center text-white" style='background-color: rgb(254,21,110)'>-89(5)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(240,86,134)'>-56(5)</div><div class="text-center text-white" style='background-color: rgb(214,137,148)'>-28(3)</div><div class="text-center text-white" style='background-color: rgb(254,1,102)'>-99(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(240,84,133)'>-57(5)</div><div class="text-center text-white" style='background-color: rgb(222,124,145)'>-35(3)</div><div class="text-center text-white" style='background-color: rgb(254,15,108)'>-92(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,56,124)'>-72(4)</div><div class="text-center text-white" style='background-color: rgb(238,89,135)'>-55(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-108(4)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(212,141,148)'>-25(6)</div><div class="text-center text-white" style='background-color: rgb(197,161,152)'>-13(3)</div><div class="text-center text-white" style='background-color: rgb(233,102,139)'>-47(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(211,142,149)'>-24(2)</div><div class="text-center text-white" style='background-color: rgb(195,163,152)'>-11(1)</div><div class="text-center text-white" style='background-color: rgb(233,102,139)'>-47(2)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(205,151,150)'>-19(6)</div><div class="text-center text-white" style='background-color: rgb(185,175,152)'>-4(3)</div><div class="text-center text-white" style='background-color: rgb(226,116,143)'>-40(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(208,147,150)'>-22(6)</div><div class="text-center text-white" style='background-color: rgb(193,166,152)'>-10(3)</div><div class="text-center text-white" style='background-color: rgb(219,129,146)'>-32(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(196,162,152)'>-12(6)</div><div class="text-center text-white" style='background-color: rgb(181,179,152)'>-1(3)</div><div class="text-center text-white" style='background-color: rgb(203,153,151)'>-18(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(234,99,138)'>-49(5)</div><div class="text-center text-white" style='background-color: rgb(200,157,151)'>-15(3)</div><div class="text-center text-white" style='background-color: rgb(254,11,106)'>-94(5)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,90,135)'>-54(5)</div><div class="text-center text-white" style='background-color: rgb(208,146,149)'>-22(3)</div><div class="text-center text-white" style='background-color: rgb(254,0,102)'>-100(5)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,90,135)'>-54(5)</div><div class="text-center text-white" style='background-color: rgb(218,131,147)'>-31(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-106(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(241,82,133)'>-58(5)</div><div class="text-center text-white" style='background-color: rgb(227,114,142)'>-41(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-113(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(248,58,124)'>-71(4)</div><div class="text-center text-white" style='background-color: rgb(241,82,133)'>-58(2)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-111(4)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(215,135,148)'>-28(6)</div><div class="text-center text-white" style='background-color: rgb(195,163,152)'>-11(3)</div><div class="text-center text-white" style='background-color: rgb(240,83,133)'>-58(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(208,146,149)'>-22(6)</div><div class="text-center text-white" style='background-color: rgb(197,161,151)'>-13(3)</div><div class="text-center text-white" style='background-color: rgb(230,108,141)'>-44(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(210,144,149)'>-23(6)</div><div class="text-center text-white" style='background-color: rgb(188,171,152)'>-6(3)</div><div class="text-center text-white" style='background-color: rgb(235,96,137)'>-50(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(203,154,151)'>-17(6)</div><div class="text-center text-white" style='background-color: rgb(183,177,152)'>-2(3)</div><div class="text-center text-white" style='background-color: rgb(209,145,149)'>-22(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(198,160,151)'>-13(6)</div><div class="text-center text-white" style='background-color: rgb(182,178,152)'>-2(3)</div><div class="text-center text-white" style='background-color: rgb(211,142,149)'>-25(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(231,106,140)'>-45(6)</div><div class="text-center text-white" style='background-color: rgb(202,155,151)'>-17(3)</div><div class="text-center text-white" style='background-color: rgb(254,7,104)'>-96(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(238,90,135)'>-54(5)</div><div class="text-center text-white" style='background-color: rgb(211,142,149)'>-24(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-109(5)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(239,87,134)'>-56(5)</div><div class="text-center text-white" style='background-color: rgb(219,129,146)'>-32(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-108(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,92,136)'>-53(5)</div><div class="text-center text-white" style='background-color: rgb(226,117,143)'>-39(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-111(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,50,121)'>-74(4)</div><div class="text-center text-white" style='background-color: rgb(237,93,136)'>-52(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-110(4)</div> </td>
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
<div class="text-center text-white" style='background-color: rgb(215,135,147)'>-29(6)</div><div class="text-center text-white" style='background-color: rgb(204,152,150)'>-18(3)</div><div class="text-center text-white" style='background-color: rgb(236,95,137)'>-51(6)</div> </td>
 <!-- 3 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(212,141,149)'>-25(6)</div><div class="text-center text-white" style='background-color: rgb(199,159,151)'>-14(3)</div><div class="text-center text-white" style='background-color: rgb(235,98,138)'>-50(6)</div> </td>
 <!-- 4 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(207,148,150)'>-21(6)</div><div class="text-center text-white" style='background-color: rgb(187,172,152)'>-5(3)</div><div class="text-center text-white" style='background-color: rgb(222,124,145)'>-35(6)</div> </td>
 <!-- 5 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(200,156,151)'>-16(6)</div><div class="text-center text-white" style='background-color: rgb(182,178,152)'>-1(3)</div><div class="text-center text-white" style='background-color: rgb(217,133,147)'>-30(6)</div> </td>
 <!-- 6 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(194,164,152)'>-10(6)</div><div class="text-center " style='background-color: rgb(177,183,152)'>+2(3)</div><div class="text-center text-white" style='background-color: rgb(204,152,150)'>-18(6)</div> </td>
 <!-- 7 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(233,101,139)'>-48(6)</div><div class="text-center text-white" style='background-color: rgb(198,159,151)'>-14(3)</div><div class="text-center text-white" style='background-color: rgb(254,12,106)'>-94(6)</div> </td>
 <!-- 8 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,92,136)'>-53(5)</div><div class="text-center text-white" style='background-color: rgb(205,151,150)'>-19(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-111(5)</div> </td>
 <!-- 9 -->
 <td>
<div class="text-center text-white" style='background-color: rgb(237,92,136)'>-53(5)</div><div class="text-center text-white" style='background-color: rgb(215,136,148)'>-28(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-108(5)</div> </td>
 <!-- T -->
 <td>
<div class="text-center text-white" style='background-color: rgb(243,76,131)'>-61(5)</div><div class="text-center text-white" style='background-color: rgb(227,115,143)'>-40(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-107(5)</div> </td>
 <!-- A -->
 <td>
<div class="text-center text-white" style='background-color: rgb(249,51,122)'>-74(4)</div><div class="text-center text-white" style='background-color: rgb(239,86,134)'>-56(3)</div><div class="text-center text-white" style='background-color: rgb(255,0,102)'>-108(4)</div> </td>
</tr>

 </tbody>
</table>
```

| Hand | Number of hands | Stand | Double | Hit |
| ---- | ----- | ----- | ------ | --- |
| h20-2 | 1000 | 0.631 (0.03) | -0.844 (0.02) | -1.722 (0.03) |
| h20-3 | 1000 | 0.618 (0.03) | -0.866 (0.02) | -1.714 (0.03) |
| h20-4 | 1000 | 0.648 (0.03) | -0.899 (0.01) | -1.718 (0.03) |
| h20-5 | 1000 | 0.673 (0.03) | -0.874 (0.02) | -1.718 (0.03) |
| h20-6 | 1000 | 0.684 (0.03) | -0.855 (0.02) | -1.722 (0.03) |
| h20-7 | 1000 | 0.759 (0.03) | -0.844 (0.02) | -1.698 (0.03) |
| h20-8 | 1000 | 0.76 (0.03) | -0.846 (0.02) | -1.692 (0.03) |
| h20-9 | 1000 | 0.756 (0.03) | -0.83 (0.02) | -1.7 (0.03) |
| h20-T | 1000 | 0.477 (0.03) | -0.853 (0.02) | -1.62 (0.03) |
| h20-A | 1000 | 0.034 (0.03) | -0.888 (0.01) | -1.518 (0.03) |
| h19-2 | 1000 | 0.375 (0.04) | -0.741 (0.02) | -1.43 (0.04) |
| h19-3 | 1000 | 0.434 (0.04) | -0.704 (0.02) | -1.474 (0.04) |
| h19-4 | 1000 | 0.426 (0.04) | -0.756 (0.02) | -1.436 (0.04) |
| h19-5 | 1000 | 0.44 (0.04) | -0.725 (0.02) | -1.414 (0.04) |
| h19-6 | 1000 | 0.436 (0.04) | -0.734 (0.02) | -1.394 (0.04) |
| h19-7 | 1000 | 0.609 (0.04) | -0.734 (0.02) | -1.418 (0.04) |
| h19-8 | 1000 | 0.673 (0.05) | -0.727 (0.02) | -1.378 (0.05) |
| h19-9 | 1000 | 0.298 (0.04) | -0.705 (0.02) | -1.486 (0.04) |
| h19-T | 1000 | -0.015 (0.04) | -0.758 (0.02) | -1.413 (0.04) |
| h19-A | 1000 | -0.163 (0.04) | -0.823 (0.02) | -1.336 (0.04) |
| h18-2 | 1000 | 0.094 (0.05) | -0.652 (0.02) | -1.276 (0.05) |
| h18-3 | 1000 | 0.173 (0.05) | -0.624 (0.02) | -1.266 (0.05) |
| h18-4 | 1000 | 0.162 (0.05) | -0.631 (0.02) | -1.23 (0.05) |
| h18-5 | 1000 | 0.171 (0.05) | -0.598 (0.02) | -1.27 (0.05) |
| h18-6 | 1000 | 0.216 (0.05) | -0.627 (0.02) | -1.204 (0.05) |
| h18-7 | 1000 | 0.398 (0.05) | -0.568 (0.03) | -1.212 (0.05) |
| h18-8 | 1000 | 0.125 (0.05) | -0.628 (0.02) | -1.188 (0.05) |
| h18-9 | 1000 | -0.202 (0.05) | -0.583 (0.02) | -1.238 (0.05) |
| h18-T | 1000 | -0.236 (0.05) | -0.726 (0.02) | -1.221 (0.05) |
| h18-A | 1000 | -0.448 (0.04) | -0.753 (0.02) | -1.14 (0.04) |
| h17-2 | 1000 | -0.156 (0.05) | -0.57 (0.03) | -0.992 (0.05) |
| h17-3 | 1000 | -0.158 (0.05) | -0.557 (0.03) | -1.058 (0.05) |
| h17-4 | 1000 | -0.088 (0.05) | -0.548 (0.03) | -1.074 (0.05) |
| h17-5 | 1000 | -0.021 (0.05) | -0.531 (0.03) | -1.058 (0.05) |
| h17-6 | 1000 | 0.042 (0.05) | -0.533 (0.03) | -1.054 (0.05) |
| h17-7 | 1000 | -0.125 (0.05) | -0.494 (0.03) | -1.03 (0.05) |
| h17-8 | 1000 | -0.375 (0.05) | -0.574 (0.03) | -1.05 (0.05) |
| h17-9 | 1000 | -0.402 (0.05) | -0.525 (0.03) | -1.138 (0.05) |
| h17-T | 1000 | -0.489 (0.05) | -0.623 (0.02) | -1.211 (0.05) |
| h17-A | 1000 | -0.651 (0.04) | -0.721 (0.02) | -1.093 (0.04) |
| h16-2 | 1000 | -0.282 (0.05) | -0.438 (0.03) | -1.01 (0.05) |
| h16-3 | 1000 | -0.24 (0.05) | -0.508 (0.03) | -0.99 (0.05) |
| h16-4 | 1000 | -0.196 (0.05) | -0.469 (0.03) | -0.976 (0.05) |
| h16-5 | 1000 | -0.222 (0.06) | -0.423 (0.03) | -0.874 (0.06) |
| h16-6 | 1000 | -0.106 (0.05) | -0.473 (0.03) | -0.976 (0.05) |
| h16-7 | 1000 | -0.522 (0.06) | -0.412 (0.03) | -0.788 (0.06) |
| h16-8 | 1000 | -0.524 (0.05) | -0.433 (0.03) | -0.934 (0.05) |
| h16-9 | 10000 | -0.5468 (0.02) | -0.4897 (0.008) | -1.0266 (0.02) |
| h16-T | 1000000 | -0.575524 (0) | -0.575795 (0) | -1.07298 (0) |
| h16-A | 10000 | -0.7306 (0.01) | -0.6893 (0.007) | -1.045 (0.01) |
| h15-2 | 1000 | -0.304 (0.05) | -0.42 (0.03) | -0.96 (0.05) |
| h15-3 | 1000 | -0.186 (0.05) | -0.353 (0.03) | -0.88 (0.05) |
| h15-4 | 1000 | -0.176 (0.06) | -0.384 (0.03) | -0.7 (0.06) |
| h15-5 | 1000 | -0.152 (0.06) | -0.371 (0.03) | -0.682 (0.06) |
| h15-6 | 1000 | -0.166 (0.06) | -0.348 (0.03) | -0.73 (0.06) |
| h15-7 | 1000 | -0.524 (0.06) | -0.382 (0.03) | -0.776 (0.06) |
| h15-8 | 10000 | -0.5124 (0.02) | -0.4169 (0.009) | -0.8406 (0.02) |
| h15-9 | 1000 | -0.596 (0.05) | -0.425 (0.03) | -0.942 (0.05) |
| h15-T | 100000 | -0.57872 (0.005) | -0.54447 (0.003) | -1.01351 (0.005) |
| h15-A | 1000 | -0.724 (0.04) | -0.662 (0.02) | -1.028 (0.04) |
| h14-2 | 10000 | -0.3006 (0.02) | -0.3675 (0.009) | -0.7454 (0.02) |
| h14-3 | 10000 | -0.2476 (0.02) | -0.3417 (0.009) | -0.6788 (0.02) |
| h14-4 | 1000 | -0.222 (0.06) | -0.381 (0.03) | -0.688 (0.06) |
| h14-5 | 1000 | -0.128 (0.06) | -0.271 (0.03) | -0.734 (0.06) |
| h14-6 | 10000 | -0.1314 (0.02) | -0.3164 (0.009) | -0.619 (0.02) |
| h14-7 | 1000 | -0.49 (0.06) | -0.322 (0.03) | -0.62 (0.06) |
| h14-8 | 1000 | -0.54 (0.06) | -0.366 (0.03) | -0.828 (0.06) |
| h14-9 | 1000 | -0.538 (0.05) | -0.411 (0.03) | -0.924 (0.05) |
| h14-T | 10000 | -0.5848 (0.02) | -0.5143 (0.008) | -0.9248 (0.02) |
| h14-A | 1000 | -0.718 (0.04) | -0.576 (0.02) | -0.902 (0.04) |
| h13-2 | 100000 | -0.28324 (0.006) | -0.30386 (0.003) | -0.62712 (0.006) |
| h13-3 | 10000 | -0.2492 (0.02) | -0.2861 (0.009) | -0.5528 (0.02) |
| h13-4 | 1000 | -0.206 (0.06) | -0.318 (0.03) | -0.576 (0.06) |
| h13-5 | 1000 | -0.18 (0.06) | -0.278 (0.03) | -0.42 (0.06) |
| h13-6 | 1000 | -0.068 (0.06) | -0.219 (0.03) | -0.516 (0.06) |
| h13-7 | 1000 | -0.478 (0.06) | -0.223 (0.03) | -0.602 (0.06) |
| h13-8 | 1000 | -0.506 (0.06) | -0.334 (0.03) | -0.708 (0.06) |
| h13-9 | 1000 | -0.516 (0.06) | -0.394 (0.03) | -0.746 (0.06) |
| h13-T | 1000 | -0.598 (0.05) | -0.5 (0.03) | -0.947 (0.05) |
| h13-A | 1000 | -0.734 (0.04) | -0.625 (0.02) | -0.99 (0.04) |
| h12-2 | 100000 | -0.28482 (0.006) | -0.24941 (0.003) | -0.50748 (0.006) |
| h12-3 | 100000 | -0.24648 (0.006) | -0.23454 (0.003) | -0.4634 (0.006) |
| h12-4 | 100000 | -0.20318 (0.006) | -0.21475 (0.003) | -0.43554 (0.006) |
| h12-5 | 10000 | -0.1632 (0.02) | -0.1934 (0.01) | -0.4412 (0.02) |
| h12-6 | 10000 | -0.1184 (0.02) | -0.1702 (0.01) | -0.3416 (0.02) |
| h12-7 | 1000 | -0.462 (0.06) | -0.264 (0.03) | -0.538 (0.06) |
| h12-8 | 1000 | -0.526 (0.06) | -0.281 (0.03) | -0.552 (0.06) |
| h12-9 | 1000 | -0.536 (0.06) | -0.366 (0.03) | -0.706 (0.06) |
| h12-T | 1000 | -0.556 (0.05) | -0.434 (0.03) | -0.745 (0.05) |
| h12-A | 1000 | -0.728 (0.05) | -0.543 (0.03) | -0.841 (0.05) |
| h11-2 | 1000 | -0.316 (0.06) | 0.25 (0.03) | 0.476 (0.06) |
| h11-3 | 1000 | -0.204 (0.06) | 0.288 (0.03) | 0.566 (0.06) |
| h11-4 | 1000 | -0.224 (0.06) | 0.296 (0.03) | 0.636 (0.06) |
| h11-5 | 1000 | -0.192 (0.06) | 0.286 (0.03) | 0.62 (0.06) |
| h11-6 | 1000 | -0.14 (0.06) | 0.282 (0.03) | 0.626 (0.06) |
| h11-7 | 1000 | -0.516 (0.06) | 0.271 (0.03) | 0.46 (0.06) |
| h11-8 | 1000 | -0.494 (0.06) | 0.193 (0.03) | 0.342 (0.06) |
| h11-9 | 10000 | -0.5302 (0.02) | 0.184 (0.009) | 0.279 (0.02) |
| h11-T | 10000 | -0.5806 (0.02) | 0.0312 (0.01) | 0.076 (0.02) |
| h11-A | 100000 | -0.72378 (0.005) | -0.2353 (0.003) | -0.24466 (0.005) |
| h10-2 | 1000 | -0.318 (0.06) | 0.116 (0.03) | 0.386 (0.06) |
| h10-3 | 1000 | -0.226 (0.06) | 0.146 (0.03) | 0.466 (0.06) |
| h10-4 | 1000 | -0.212 (0.06) | 0.235 (0.03) | 0.582 (0.06) |
| h10-5 | 1000 | -0.184 (0.06) | 0.279 (0.03) | 0.45 (0.06) |
| h10-6 | 1000 | -0.118 (0.06) | 0.314 (0.03) | 0.592 (0.06) |
| h10-7 | 1000 | -0.46 (0.06) | 0.267 (0.03) | 0.514 (0.06) |
| h10-8 | 10000 | -0.517 (0.02) | 0.1957 (0.009) | 0.2802 (0.02) |
| h10-9 | 1000 | -0.546 (0.06) | 0.129 (0.03) | 0.22 (0.06) |
| h10-T | 10000 | -0.5862 (0.02) | -0.0588 (0.009) | -0.1086 (0.02) |
| h10-A | 1000 | -0.696 (0.05) | -0.29 (0.03) | -0.206 (0.05) |
| h9-2 | 1000 | -0.248 (0.06) | 0.088 (0.03) | -0.006 (0.06) |
| h9-3 | 10000 | -0.255 (0.02) | 0.0932 (0.01) | 0.1294 (0.02) |
| h9-4 | 10000 | -0.2024 (0.02) | 0.1175 (0.01) | 0.19 (0.02) |
| h9-5 | 1000 | -0.182 (0.06) | 0.168 (0.03) | 0.272 (0.06) |
| h9-6 | 10000 | -0.1058 (0.02) | 0.1937 (0.009) | 0.2904 (0.02) |
| h9-7 | 10000 | -0.4702 (0.02) | 0.1666 (0.009) | 0.0708 (0.02) |
| h9-8 | 1000 | -0.524 (0.06) | 0.093 (0.03) | -0.024 (0.06) |
| h9-9 | 1000 | -0.536 (0.06) | -0.067 (0.03) | -0.298 (0.06) |
| h9-T | 1000 | -0.618 (0.06) | -0.191 (0.03) | -0.527 (0.06) |
| h9-A | 1000 | -0.708 (0.05) | -0.383 (0.03) | -0.65 (0.05) |
| h8-2 | 1000 | -0.286 (0.06) | -0.037 (0.03) | -0.18 (0.06) |
| h8-3 | 1000 | -0.226 (0.06) | -0.092 (0.03) | -0.198 (0.06) |
| h8-4 | 1000 | -0.22 (0.06) | 0.084 (0.03) | -0.168 (0.06) |
| h8-5 | 10000 | -0.164 (0.02) | 0.0565 (0.01) | 0.0248 (0.02) |
| h8-6 | 100000 | -0.11954 (0.006) | 0.10471 (0.003) | 0.08198 (0.006) |
| h8-7 | 1000 | -0.54 (0.06) | 0.088 (0.03) | -0.212 (0.06) |
| h8-8 | 1000 | -0.516 (0.06) | 0 (0.03) | -0.458 (0.06) |
| h8-9 | 1000 | -0.548 (0.06) | -0.195 (0.03) | -0.668 (0.06) |
| h8-T | 1000 | -0.608 (0.05) | -0.323 (0.03) | -0.774 (0.05) |
| h8-A | 1000 | -0.75 (0.05) | -0.464 (0.03) | -0.884 (0.05) |
| h7-2 | 1000 | -0.326 (0.06) | -0.073 (0.03) | -0.414 (0.06) |
| h7-3 | 1000 | -0.21 (0.06) | -0.075 (0.03) | -0.348 (0.06) |
| h7-4 | 1000 | -0.21 (0.06) | -0.02 (0.03) | -0.36 (0.06) |
| h7-5 | 1000 | -0.132 (0.06) | 0.075 (0.03) | -0.13 (0.06) |
| h7-6 | 1000 | -0.122 (0.06) | 0.076 (0.03) | -0.13 (0.06) |
| h7-7 | 1000 | -0.452 (0.06) | -0.066 (0.03) | -0.492 (0.06) |
| h7-8 | 1000 | -0.522 (0.05) | -0.198 (0.03) | -0.892 (0.05) |
| h7-9 | 1000 | -0.562 (0.05) | -0.275 (0.03) | -0.994 (0.05) |
| h7-T | 1000 | -0.57 (0.05) | -0.351 (0.03) | -0.923 (0.05) |
| h7-A | 1000 | -0.716 (0.04) | -0.546 (0.03) | -1.077 (0.04) |
| h6-2 | 1000 | -0.254 (0.06) | -0.126 (0.03) | -0.472 (0.06) |
| h6-3 | 10000 | -0.244 (0.02) | -0.1126 (0.01) | -0.4712 (0.02) |
| h6-4 | 1000 | -0.192 (0.06) | -0.036 (0.03) | -0.396 (0.06) |
| h6-5 | 1000 | -0.216 (0.06) | -0.097 (0.03) | -0.322 (0.06) |
| h6-6 | 1000 | -0.12 (0.06) | -0.008 (0.03) | -0.178 (0.06) |
| h6-7 | 1000 | -0.488 (0.05) | -0.153 (0.03) | -0.942 (0.05) |
| h6-8 | 1000 | -0.536 (0.05) | -0.221 (0.03) | -0.998 (0.05) |
| h6-9 | 1000 | -0.536 (0.05) | -0.309 (0.03) | -1.058 (0.05) |
| h6-T | 1000 | -0.58 (0.05) | -0.406 (0.03) | -1.127 (0.05) |
| h6-A | 1000 | -0.706 (0.04) | -0.578 (0.02) | -1.111 (0.04) |
| h5-2 | 1000 | -0.284 (0.06) | -0.114 (0.03) | -0.576 (0.06) |
| h5-3 | 1000 | -0.22 (0.06) | -0.127 (0.03) | -0.44 (0.06) |
| h5-4 | 1000 | -0.232 (0.06) | -0.058 (0.03) | -0.504 (0.06) |
| h5-5 | 1000 | -0.174 (0.06) | -0.02 (0.03) | -0.224 (0.06) |
| h5-6 | 1000 | -0.134 (0.06) | -0.015 (0.03) | -0.248 (0.06) |
| h5-7 | 1000 | -0.454 (0.06) | -0.167 (0.03) | -0.964 (0.06) |
| h5-8 | 1000 | -0.536 (0.05) | -0.244 (0.03) | -1.088 (0.05) |
| h5-9 | 1000 | -0.556 (0.05) | -0.324 (0.03) | -1.08 (0.05) |
| h5-T | 1000 | -0.526 (0.05) | -0.392 (0.03) | -1.112 (0.05) |
| h5-A | 1000 | -0.744 (0.04) | -0.522 (0.03) | -1.1 (0.04) |
| h4-2 | 1000 | -0.286 (0.06) | -0.182 (0.03) | -0.512 (0.06) |
| h4-3 | 1000 | -0.252 (0.06) | -0.141 (0.03) | -0.496 (0.06) |
| h4-4 | 1000 | -0.206 (0.06) | -0.052 (0.03) | -0.348 (0.06) |
| h4-5 | 1000 | -0.156 (0.06) | -0.013 (0.03) | -0.296 (0.06) |
| h4-6 | 1000 | -0.104 (0.06) | 0.02 (0.03) | -0.184 (0.06) |
| h4-7 | 1000 | -0.478 (0.06) | -0.137 (0.03) | -0.94 (0.06) |
| h4-8 | 1000 | -0.526 (0.05) | -0.193 (0.03) | -1.108 (0.05) |
| h4-9 | 1000 | -0.528 (0.05) | -0.283 (0.03) | -1.084 (0.05) |
| h4-T | 1000 | -0.612 (0.05) | -0.399 (0.03) | -1.072 (0.05) |
| h4-A | 1000 | -0.74 (0.04) | -0.557 (0.03) | -1.081 (0.04) |
| s20-2 | 1000 | 0.646 (0.06) | 0.217 (0.03) | 0.312 (0.06) |
| s20-3 | 1000 | 0.677 (0.06) | 0.181 (0.03) | 0.338 (0.06) |
| s20-4 | 1000 | 0.637 (0.06) | 0.213 (0.03) | 0.436 (0.06) |
| s20-5 | 10000 | 0.6604 (0.02) | 0.2455 (0.009) | 0.5394 (0.02) |
| s20-6 | 1000 | 0.694 (0.06) | 0.281 (0.03) | 0.524 (0.06) |
| s20-7 | 1000 | 0.753 (0.06) | 0.304 (0.03) | 0.488 (0.06) |
| s20-8 | 1000 | 0.777 (0.06) | 0.229 (0.03) | 0.274 (0.06) |
| s20-9 | 1000 | 0.733 (0.06) | 0.138 (0.03) | 0.098 (0.06) |
| s20-T | 1000 | 0.438 (0.06) | -0.057 (0.03) | -0.038 (0.06) |
| s20-A | 1000 | 0.067 (0.05) | -0.272 (0.03) | -0.341 (0.05) |
| s19-2 | 1000 | 0.389 (0.06) | 0.092 (0.03) | 0.256 (0.06) |
| s19-3 | 10000 | 0.39 (0.02) | 0.1464 (0.009) | 0.3168 (0.02) |
| s19-4 | 10000 | 0.4082 (0.02) | 0.1816 (0.009) | 0.3286 (0.02) |
| s19-5 | 100000 | 0.43517 (0.006) | 0.20004 (0.003) | 0.398 (0.006) |
| s19-6 | 1000000 | 0.453457 (0) | 0.231529 (0) | 0.460572 (0) |
| s19-7 | 1000 | 0.633 (0.06) | 0.231 (0.03) | 0.372 (0.06) |
| s19-8 | 1000 | 0.59 (0.06) | 0.122 (0.03) | 0.192 (0.06) |
| s19-9 | 1000 | 0.301 (0.06) | -0.013 (0.03) | -0.122 (0.06) |
| s19-T | 1000 | -0.032 (0.06) | -0.175 (0.03) | -0.395 (0.06) |
| s19-A | 1000 | -0.133 (0.05) | -0.331 (0.03) | -0.48 (0.05) |
| s18-2 | 1000000 | 0.109892 (0) | 0.058827 (0) | 0.117848 (0) |
| s18-3 | 10000 | 0.1328 (0.02) | 0.1039 (0.01) | 0.2114 (0.02) |
| s18-4 | 10000 | 0.1586 (0.02) | 0.1282 (0.01) | 0.2484 (0.02) |
| s18-5 | 1000 | 0.203 (0.06) | 0.135 (0.03) | 0.344 (0.06) |
| s18-6 | 10000 | 0.2239 (0.02) | 0.1889 (0.009) | 0.3842 (0.02) |
| s18-7 | 10000 | 0.3993 (0.02) | 0.169 (0.009) | 0.1994 (0.02) |
| s18-8 | 10000 | 0.1101 (0.02) | 0.0447 (0.009) | -0.0398 (0.02) |
| s18-9 | 10000 | -0.1749 (0.02) | -0.0937 (0.009) | -0.2754 (0.02) |
| s18-T | 10000 | -0.2431 (0.02) | -0.2043 (0.009) | -0.388 (0.02) |
| s18-A | 1000 | -0.494 (0.05) | -0.405 (0.03) | -0.662 (0.05) |
| s17-2 | 1000000 | -0.155882 (0) | -0.006551 (0) | -0.012158 (0) |
| s17-3 | 1000 | -0.113 (0.06) | -0.008 (0.03) | 0.096 (0.06) |
| s17-4 | 1000 | -0.06 (0.06) | 0.018 (0.03) | 0.112 (0.06) |
| s17-5 | 1000 | -0.003 (0.06) | 0.071 (0.03) | 0.314 (0.06) |
| s17-6 | 1000 | -0.015 (0.06) | 0.11 (0.03) | 0.252 (0.06) |
| s17-7 | 1000 | -0.086 (0.06) | 0.059 (0.03) | -0.042 (0.06) |
| s17-8 | 1000 | -0.349 (0.06) | -0.064 (0.03) | -0.234 (0.06) |
| s17-9 | 1000 | -0.408 (0.06) | -0.211 (0.03) | -0.332 (0.06) |
| s17-T | 1000 | -0.455 (0.06) | -0.209 (0.03) | -0.507 (0.06) |
| s17-A | 1000 | -0.649 (0.05) | -0.479 (0.03) | -0.649 (0.05) |
| s16-2 | 1000 | -0.258 (0.06) | 0.002 (0.03) | -0.158 (0.06) |
| s16-3 | 10000 | -0.2604 (0.02) | 0.0147 (0.01) | -0.0448 (0.02) |
| s16-4 | 1000 | -0.162 (0.06) | -0.037 (0.03) | 0.07 (0.06) |
| s16-5 | 10000 | -0.1576 (0.02) | 0.063 (0.01) | 0.133 (0.02) |
| s16-6 | 10000 | -0.1218 (0.02) | 0.0883 (0.01) | 0.183 (0.02) |
| s16-7 | 1000 | -0.484 (0.06) | 0.027 (0.03) | -0.194 (0.06) |
| s16-8 | 1000 | -0.556 (0.06) | -0.06 (0.03) | -0.346 (0.06) |
| s16-9 | 1000 | -0.548 (0.06) | -0.105 (0.03) | -0.482 (0.06) |
| s16-T | 1000 | -0.562 (0.06) | -0.271 (0.03) | -0.474 (0.06) |
| s16-A | 1000 | -0.724 (0.05) | -0.471 (0.03) | -0.679 (0.05) |
| s15-2 | 10000 | -0.2686 (0.02) | -0.0012 (0.01) | -0.0432 (0.02) |
| s15-3 | 100000 | -0.24634 (0.006) | 0.02229 (0.003) | -0.0134 (0.006) |
| s15-4 | 10000 | -0.212 (0.02) | 0.0491 (0.01) | 0.0798 (0.02) |
| s15-5 | 10000 | -0.1584 (0.02) | 0.0804 (0.01) | 0.1388 (0.02) |
| s15-6 | 1000 | -0.092 (0.06) | 0.109 (0.03) | 0.23 (0.06) |
| s15-7 | 10000 | -0.4756 (0.02) | 0.0379 (0.01) | -0.1748 (0.02) |
| s15-8 | 1000 | -0.542 (0.06) | -0.039 (0.03) | -0.34 (0.06) |
| s15-9 | 1000 | -0.554 (0.06) | -0.086 (0.03) | -0.398 (0.06) |
| s15-T | 1000 | -0.582 (0.06) | -0.237 (0.03) | -0.63 (0.06) |
| s15-A | 1000 | -0.71 (0.05) | -0.448 (0.03) | -0.664 (0.05) |
| s14-2 | 1000 | -0.262 (0.06) | 0.03 (0.03) | -0.134 (0.06) |
| s14-3 | 10000 | -0.2244 (0.02) | 0.0605 (0.01) | 0.0012 (0.02) |
| s14-4 | 100000 | -0.20532 (0.006) | 0.07772 (0.003) | 0.0549 (0.006) |
| s14-5 | 10000 | -0.1508 (0.02) | 0.0975 (0.01) | 0.1382 (0.02) |
| s14-6 | 1000 | -0.14 (0.06) | 0.121 (0.03) | 0.232 (0.06) |
| s14-7 | 1000 | -0.49 (0.06) | 0.09 (0.03) | -0.284 (0.06) |
| s14-8 | 1000 | -0.494 (0.06) | -0.031 (0.03) | -0.36 (0.06) |
| s14-9 | 1000 | -0.56 (0.06) | -0.096 (0.03) | -0.386 (0.06) |
| s14-T | 1000 | -0.556 (0.06) | -0.192 (0.03) | -0.622 (0.06) |
| s14-A | 1000 | -0.708 (0.05) | -0.404 (0.03) | -0.654 (0.05) |
| s13-2 | 1000 | -0.26 (0.06) | 0.082 (0.03) | -0.19 (0.06) |
| s13-3 | 10000 | -0.248 (0.02) | 0.0618 (0.01) | -0.0196 (0.02) |
| s13-4 | 10000 | -0.2056 (0.02) | 0.0949 (0.01) | 0.0602 (0.02) |
| s13-5 | 1000000 | -0.163838 (0) | 0.130573 (0) | 0.127766 (0) |
| s13-6 | 100000 | -0.11506 (0.006) | 0.13519 (0.003) | 0.18672 (0.006) |
| s13-7 | 1000 | -0.432 (0.06) | 0.124 (0.03) | -0.23 (0.06) |
| s13-8 | 1000 | -0.494 (0.06) | 0.034 (0.03) | -0.296 (0.06) |
| s13-9 | 1000 | -0.554 (0.06) | -0.01 (0.03) | -0.472 (0.06) |
| s13-T | 1000 | -0.606 (0.06) | -0.178 (0.03) | -0.606 (0.06) |
| s13-A | 1000 | -0.73 (0.05) | -0.335 (0.03) | -0.702 (0.05) |
| s12-2 | 10000 | -0.2868 (0.02) | 0.0886 (0.01) | -0.0724 (0.02) |
| s12-3 | 1000 | -0.182 (0.06) | 0.121 (0.03) | -0.02 (0.06) |
| s12-4 | 1000 | -0.24 (0.06) | 0.207 (0.03) | 0.042 (0.06) |
| s12-5 | 10000 | -0.1792 (0.02) | 0.156 (0.01) | 0.1094 (0.02) |
| s12-6 | 10000 | -0.1206 (0.02) | 0.1582 (0.01) | 0.2116 (0.02) |
| s12-7 | 1000 | -0.484 (0.06) | 0.106 (0.03) | -0.212 (0.06) |
| s12-8 | 1000 | -0.52 (0.06) | 0.081 (0.03) | -0.32 (0.06) |
| s12-9 | 1000 | -0.554 (0.06) | -0.035 (0.03) | -0.416 (0.06) |
| s12-T | 1000 | -0.604 (0.06) | -0.215 (0.03) | -0.512 (0.06) |
| s12-A | 1000 | -0.656 (0.05) | -0.363 (0.03) | -0.747 (0.05) |



| Hand | Number of hands |  Yes  |  No  |
| ---- | ----- | ----- | ---- |
| pA-2 | 1000 | 0.441 (0.05) | 0.061 (0.03) |
| pA-3 | 1000 | 0.455 (0.05) | 0.127 (0.03) |
| pA-4 | 1000 | 0.613 (0.05) | 0.113 (0.03) |
| pA-5 | 1000 | 0.597 (0.05) | 0.143 (0.03) |
| pA-6 | 1000 | 0.755 (0.05) | 0.076 (0.06) |
| pA-7 | 1000 | 0.465 (0.05) | 0.205 (0.03) |
| pA-8 | 1000 | 0.4 (0.05) | 0.115 (0.03) |
| pA-9 | 1000 | 0.196 (0.05) | 0.011 (0.03) |
| pA-T | 1000 | -0.025 (0.05) | -0.19 (0.03) |
| pA-A | 1000 | -0.268 (0.04) | -0.357 (0.03) |
| pT-2 | 1000 | 0.52 (0.05) | 0.614 (0.02) |
| pT-3 | 1000 | 0.423 (0.05) | 0.673 (0.02) |
| pT-4 | 1000 | 0.553 (0.05) | 0.658 (0.02) |
| pT-5 | 1000 | 0.486 (0.05) | 0.703 (0.02) |
| pT-6 | 1000 | 0.591 (0.05) | 0.663 (0.02) |
| pT-7 | 1000 | 0.482 (0.05) | 0.771 (0.02) |
| pT-8 | 1000 | 0.378 (0.05) | 0.814 (0.02) |
| pT-9 | 1000 | 0.246 (0.04) | 0.754 (0.02) |
| pT-T | 1000 | 0.035 (0.05) | 0.432 (0.02) |
| pT-A | 1000 | -0.241 (0.04) | 0.09 (0.03) |
| p9-2 | 10000 | 0.173 (0.02) | 0.1071 (0.009) |
| p9-3 | 1000 | 0.291 (0.06) | 0.132 (0.03) |
| p9-4 | 10000 | 0.2773 (0.02) | 0.1663 (0.009) |
| p9-5 | 1000 | 0.422 (0.06) | 0.157 (0.03) |
| p9-6 | 1000 | 0.362 (0.06) | 0.206 (0.03) |
| p9-7 | 100000 | 0.37708 (0.005) | 0.39894 (0.003) |
| p9-8 | 1000 | 0.233 (0.05) | 0.073 (0.02) |
| p9-9 | 10000 | -0.0951 (0.02) | -0.165 (0.009) |
| p9-T | 1000 | -0.433 (0.05) | -0.264 (0.03) |
| p9-A | 100000 | -0.47946 (0.004) | -0.46333 (0.003) |
| p8-2 | 1000 | -0.028 (0.07) | -0.222 (0.03) |
| p8-3 | 1000 | 0.097 (0.07) | -0.28 (0.03) |
| p8-4 | 1000 | 0.193 (0.07) | -0.204 (0.03) |
| p8-5 | 1000 | 0.193 (0.07) | -0.142 (0.03) |
| p8-6 | 1000 | 0.26 (0.07) | -0.118 (0.03) |
| p8-7 | 1000 | 0.265 (0.06) | -0.41 (0.03) |
| p8-8 | 1000 | -0.059 (0.06) | -0.465 (0.03) |
| p8-9 | 10000 | -0.3916 (0.02) | -0.5137 (0.008) |
| p8-T | 1000 | -0.508 (0.05) | -0.602 (0.03) |
| p8-A | 1000000 | -0.681325 (0) | -0.684029 (0) |
| p7-2 | 1000 | -0.11 (0.07) | -0.344 (0.03) |
| p7-3 | 1000 | -0.111 (0.08) | -0.248 (0.03) |
| p7-4 | 1000 | -0.002 (0.08) | -0.198 (0.03) |
| p7-5 | 1000 | 0.132 (0.08) | -0.23 (0.03) |
| p7-6 | 1000 | 0.05 (0.08) | -0.172 (0.03) |
| p7-7 | 1000 | -0.167 (0.06) | -0.331 (0.03) |
| p7-8 | 1000000 | -0.39019 (0) | -0.371056 (0) |
| p7-9 | 1000 | -0.583 (0.06) | -0.434 (0.03) |
| p7-T | 1000 | -0.729 (0.05) | -0.49 (0.03) |
| p7-A | 1000 | -0.778 (0.04) | -0.667 (0.02) |
| p6-2 | 100000 | -0.21344 (0.007) | -0.25389 (0.003) |
| p6-3 | 10000 | -0.118 (0.02) | -0.2393 (0.009) |
| p6-4 | 1000 | -0.09 (0.08) | -0.25 (0.03) |
| p6-5 | 1000 | -0.023 (0.08) | -0.16 (0.03) |
| p6-6 | 1000 | 0.169 (0.08) | -0.106 (0.03) |
| p6-7 | 10000 | -0.2601 (0.02) | -0.2155 (0.009) |
| p6-8 | 1000 | -0.346 (0.05) | -0.25 (0.03) |
| p6-9 | 1000 | -0.592 (0.05) | -0.314 (0.03) |
| p6-T | 1000 | -0.588 (0.05) | -0.419 (0.03) |
| p6-A | 1000 | -0.799 (0.04) | -0.539 (0.03) |
| p5-2 | 1000 | -0.081 (0.07) | 0.406 (0.06) |
| p5-3 | 1000 | -0.192 (0.07) | 0.384 (0.06) |
| p5-4 | 1000 | -0.072 (0.08) | 0.45 (0.06) |
| p5-5 | 1000 | -0.018 (0.08) | 0.548 (0.06) |
| p5-6 | 1000 | 0.103 (0.08) | 0.586 (0.06) |
| p5-7 | 1000 | -0.188 (0.05) | 0.516 (0.06) |
| p5-8 | 1000 | -0.229 (0.06) | 0.332 (0.06) |
| p5-9 | 1000 | -0.595 (0.05) | 0.1 (0.06) |
| p5-T | 1000 | -0.703 (0.05) | -0.058 (0.03) |
| p5-A | 1000 | -0.792 (0.04) | -0.37 (0.05) |
| p4-2 | 1000 | -0.196 (0.06) | -0.024 (0.03) |
| p4-3 | 1000 | -0.141 (0.07) | 0.008 (0.03) |
| p4-4 | 10000 | -0.0201 (0.02) | 0.0318 (0.01) |
| p4-5 | 1000 | 0.227 (0.08) | 0.059 (0.03) |
| p4-6 | 10000 | 0.1502 (0.02) | 0.0797 (0.01) |
| p4-7 | 1000 | -0.175 (0.06) | 0.104 (0.03) |
| p4-8 | 1000 | -0.3 (0.06) | -0.026 (0.03) |
| p4-9 | 1000 | -0.584 (0.05) | -0.254 (0.03) |
| p4-T | 1000 | -0.528 (0.05) | -0.283 (0.03) |
| p4-A | 1000 | -0.761 (0.04) | -0.511 (0.03) |
| p3-2 | 10000 | -0.1154 (0.02) | -0.1628 (0.01) |
| p3-3 | 1000 | 0.009 (0.07) | -0.156 (0.03) |
| p3-4 | 10000 | 0.0318 (0.02) | -0.0634 (0.01) |
| p3-5 | 10000 | 0.0928 (0.02) | -0.0301 (0.01) |
| p3-6 | 1000 | 0.208 (0.08) | -0.009 (0.03) |
| p3-7 | 10000 | -0.0545 (0.02) | -0.1646 (0.009) |
| p3-8 | 10000 | -0.2405 (0.02) | -0.2107 (0.009) |
| p3-9 | 1000 | -0.418 (0.06) | -0.239 (0.03) |
| p3-T | 1000 | -0.556 (0.05) | -0.412 (0.03) |
| p3-A | 1000 | -0.718 (0.04) | -0.489 (0.03) |
| p2-2 | 100000 | -0.08631 (0.006) | -0.11174 (0.003) |
| p2-3 | 10000 | -0.0276 (0.02) | -0.093 (0.01) |
| p2-4 | 10000 | 0.0193 (0.02) | -0.0345 (0.01) |
| p2-5 | 10000 | 0.102 (0.02) | -0.0088 (0.01) |
| p2-6 | 1000 | 0.209 (0.08) | -0.019 (0.03) |
| p2-7 | 10000 | 0.0157 (0.02) | -0.0907 (0.01) |
| p2-8 | 1000000 | -0.17563 (0) | -0.159877 (0) |
| p2-9 | 10000 | -0.3596 (0.02) | -0.2423 (0.009) |
| p2-T | 1000 | -0.517 (0.05) | -0.314 (0.03) |
| p2-A | 1000 | -0.602 (0.04) | -0.485 (0.03) |


## Detailed explanation

We want to derive the basic strategy from scratch, i.e. without assuming anything. What we are going to do is to play a large (more on what _large_ means below) number of hands by fixing our first two cards and the dealer upcard and sequentially standing, doubling or hitting the first card. Then we will compare the results for the three cases and select as the proper strategy the better one.

Standing and doubling are easy plays, because after we stand or double the dealer plays accordingly to the rules. She hits until seventeen (either soft or hard). But if we hit on our hand, we might need to make another decision wether to stand or hit again. As we do not want to assume anything, we have to play in such an order that if we do need to make another decision, we already know which is the better one. 

### Hard hands

So we start by arranging the shoe so that the user gets hard twenty (i.e. two faces) and the dealer gets succesively upcards of two to ace. So we play each combination of dealer upcard (ten) three times each playing either

 1. always standing
 2. always doubling
 3. always hitting
 
In general the first two plays are easy, because the game stops either after standing or after receiving only one card. The last one might lead to further hitting, but since we are starting with a hard twenty, that would either give the player twenty one or a bust. In any case, the game also ends.
So we play a certain number of hands (say one thousand hands) each of these three plays for each of the ten upcard faces and record the outcome. The correct play for hard twenty against each of the ten upcards is the play that gave the better result, which is of course standing.

Next, we do the same for a hard nineteen. In this case, the hitting play might not end after one card is drawn. But if that is the case, i.e. receiving an ace for a total of hard twenty, we already know what the best play is from the previous step so we play accordingly and we stand. Repeating this procedure down to hard four we can build the basic strategy table for any hard total against any dealer upcard.

### Soft hands

We can now switch to analyze soft hands. Starting from soft twenty (i.e. an ace and a nine) we do the same we did for the hard case. The only difference is that wehn hitting, we might end either in another soft hand which we would already analyzed because we start from twenty and go down, or in a hard hand, which we also already analyzed se we can play accordingly.

### Pairs

When dealing with pairs, we have to decide wether to split or not. When we do not split, we end up in one of the already-analyzed cases: either a soft twelve of any even hard hand. When we split, we might end in a hard or soft hand (already analyzed) or in a new pair. But since the new pair can be only the same pair we are analyzing, we have to treat it like we treated the first pair: either to split it or not, so we know how to deal with it.  

### Number of hands

The output is the expected value\ $e$ of the bankroll, which is a random variable with an associated uncertainty\ $\Delta e$ (i.e. a certain numbers of standard deviations). For example, if we received only blackjacks, the expected value would be 1.5 (provided blackjacks pay 3 to 2). If we busted all of our hands without doubling or splitting, the expected value would be -1. In order to say that the best strategy is, let’s say stand and not hitting or doubling, we have to make sure that $e_h-\Delta e_h > e_s+\Delta e_s$ and $e_h-\Delta e_h > e_d+\Delta e_d$. If there is no play that can give a better expected value than the other two taking into account the uncertainties, then we have to play more hands in order to reduce the random uncertainty.


## Implementation

The steps above can be written in a [Bash](https://en.wikipedia.org/wiki/Bash_%28Unix_shell%29) script that

 * loops over hands and upcards,
 * creates a strategy file for each possible play hit, double or stand (or split or not),
 * runs [Libre Blackjack](https://www.seamplex.com/blackjack),
 * checks the results and picks the best play,
 * updates the strategy file

```bash
#!/bin/bash

for i in grep cut bc awk; do
 if [ -z "`which $i`" ]; then
  echo "error: $i not installed"
  exit 1
 fi
done

debug=0

declare -A strategy
declare -A ev

declare -A min
min["hard"]=4   # from 20 to 4 in hards
min["soft"]=12  # from 20 to 12 in softs

rm -f hard.html soft.html pair.html

# --------------------------------------------------------------
# start with standing
cp hard-stand.txt hard.txt
cp soft-stand.txt soft.txt

cat << EOF > table.md
| Hand | \$n\$ | Stand | Double | Hit |
| ---- | ----- | ----- | ------ | --- |
EOF


for type in hard soft; do
 for hand in `seq 20 -1 ${min[${type}]}`; do
 
  # choose two random cards that make up the player's assumed total
  if [ ${type} = "hard" ]; then
   t="h"
   card1=11
   card2=11
   while test $card1 -gt 10 -o $card2 -gt 10; do
    card1=$((${RANDOM} % (${hand}-3) + 2))
    card2=$((${hand} - ${card1}))
   done
  elif [ ${type} = "soft" ]; then
   t="s"
   # one card is an ace
   card1=1
   card2=$((${hand} - 10 - ${card1}))
  fi

  cat << EOF >> ${type}.html
 <tr>
  <td>${t}${hand}</td>
  <td>
   <div class="text-right">s<span class="d-none d-lg-inline">tand</span></div>
   <div class="text-right">h<span class="d-none d-lg-inline">it</span></div>
   <div class="text-right">d<span class="d-none d-lg-inline">ouble</span></div>
  </td>
EOF
  
  for upcard in `seq 2 9` T A; do
  
   if [ "$upcard" = "T" ]; then
     upcard_n=10
   elif [ "$upcard" = "A" ]; then
     upcard_n=1
   else
     upcard_n=$(($upcard))
   fi
 
   n=1000    # start with n hands
   best="x"  # x means don't know what to so, so play
   
   while [ "${best}" = "x" ]; do
    # tell the user which combination we are trying and how many we will play
    echo -n ${t}${hand}-${upcard} \($card1 $card2\) "n="${n}
   
    for play in s d h; do
     
     # start with options.conf as a template and add some custom stuff
     cp options.conf blackjack.conf
     cat << EOF >> blackjack.conf
hands = ${n}
dealer2player = internal
arranged_cards = ${card1} $((${upcard_n} + 13)) $((${card2} + 26))
yaml_report = ${t}${hand}-${upcard}-${play}.yaml
#log = ${t}${hand}-${upcard}-${play}.log
EOF
 
     # read the current strategy
     while read w p2 p3 p4 p5 p6 p7 p8 p9 pT pA; do
      # w already has the "h" or the "s"
      strategy[${w},2]=$p2   
      strategy[${w},3]=$p3
      strategy[${w},4]=$p4    
      strategy[${w},5]=$p5    
      strategy[${w},6]=$p6    
      strategy[${w},7]=$p7    
      strategy[${w},8]=$p8    
      strategy[${w},9]=$p9    
      strategy[${w},T]=$pT    
      strategy[${w},A]=$pA    
     done < ${type}.txt
     
     # override the read strategy with the explicit play: s, d or h
     strategy[${t}${hand},${upcard}]=${play}
     
     # save the new (temporary) strategy
     rm -f ${type}.txt
     for h in `seq 20 -1 ${min[${type}]}`; do
      echo -n "${t}${h}  " >> ${type}.txt
      
      # extra space if h < 10
      if [ ${h} -lt 10 ]; then
       echo -n " " >> ${type}.txt
      fi 
      
      for u in `seq 2 9` T A; do
       echo -n "${strategy[${t}${h},${u}]}  " >> ${type}.txt
      done
      echo >> ${type}.txt
     done
     
     # debug, comment for production
     if [ "${debug}" != "0" ]; then
      cp ${type}.txt ${t}${hand}-${upcard}-${play}.str
     fi
    
     # ensamble the full bs.txt with no pairing
     cat hard.txt soft.txt pair-no.txt > bs.txt
    
     # play!
     blackjack > /dev/null
    
     # evaluate the results
     ev[${t}${hand},${upcard},${play}]=`grep return ${t}${hand}-${upcard}-${play}.yaml | awk '{printf("%+g", $2)}'`
     error[${t}${hand},${upcard},${play}]=`grep error ${t}${hand}-${upcard}-${play}.yaml | awk '{printf("%.1g", $2)}'`
     
    done
   
    # choose the best one
    ev_s=`printf %g ${ev[${t}${hand},${upcard},s]}`
    ev_d=`printf %g ${ev[${t}${hand},${upcard},d]}`
    ev_h=`printf %g ${ev[${t}${hand},${upcard},h]}`
   
    
    if [ $n -le 999999 ]; then 
     # if we still have room, take into account errors
     error_s=${error[${t}${hand},${upcard},s]}
     error_d=${error[${t}${hand},${upcard},d]}
     error_h=${error[${t}${hand},${upcard},h]}
    else
     # instead of running infinite hands, above a threshold asume errors are zero
     error_s=0
     error_d=0
     error_h=0
    fi  
 
    echo -ne "\ts=${ev_s} (${error_s})"
    echo -ne "\td=${ev_d} (${error_d})"
    echo -ne "\th=${ev_h} (${error_h})"
   
    if   (( $(echo "${ev_s}-${error_s} > ${ev_d}+${error_d}" | bc -l) )) &&
         (( $(echo "${ev_s}-${error_s} > ${ev_h}+${error_h}" | bc -l) )); then
     best="s"
     echo -e "\tstand"
    elif (( $(echo "${ev_d}-${error_d} > ${ev_s}+${error_s}" | bc -l) )) &&
         (( $(echo "${ev_d}-${error_d} > ${ev_h}+${error_h}" | bc -l) )); then
     best="d"
     echo -e "\tdouble"
    elif (( $(echo "${ev_h}-${error_h} > ${ev_s}+${error_s}" | bc -l) )) &&
         (( $(echo "${ev_h}-${error_h} > ${ev_d}+${error_d}" | bc -l) )); then
     best="h"
     echo -e "\thit"
    else
     best="x"
     n=$((${n} * 10))
     echo -e "\tuncertain"
    fi
   done

   strategy[${t}${hand},${upcard}]=${best}
   
   
   
   echo "| ${t}${hand}-${upcard} | ${n} | ${ev_s} (${error_s}) | ${ev_h} (${error_h}) | ${ev_d} (${error_d}) |" >> table.md
   
   echo " <!-- ${upcard} -->" >> ${type}.html
   echo " <td>" >> ${type}.html
   echo ${ev_s} ${error_s} | awk -f cell.awk >> ${type}.html
   echo ${ev_h} ${error_h} | awk -f cell.awk >> ${type}.html
   echo ${ev_d} ${error_d} | awk -f cell.awk >> ${type}.html
   echo " </td>" >> ${type}.html
   
   
   # save the strategy again with the best strategy
   rm -f ${type}.txt
   for h in `seq 20 -1 ${min[${type}]}`; do
    echo -n "${t}${h}  " >> ${type}.txt
    
    # extra space if h < 10
    if [ ${h} -lt 10 ]; then
     echo -n " " >> ${type}.txt
    fi 
    
    for u in `seq 2 9` T A; do
     echo -n "${strategy[${t}${h},${u}]}  " >> ${type}.txt
    done
    
    echo >> ${type}.txt
    
   done
  done
  
  echo "</tr>" >> ${type}.html
  
 done
done


cat << EOF >> table.md


| Hand | \$n\$ |  Yes  |  No  |
| ---- | ----- | ----- | ---- |
EOF

# --------------------------------------------------------------------
# pairs
type="pair"
t="p"
cp pair-no.txt pair.txt

for hand in A T `seq 9 -1 2`; do
 if [ "${hand}" = "A" ]; then
  pair=1
 elif [ "${hand}" = "T" ]; then
  pair=10
 else
  pair=$((${hand}))
 fi
  
 cat << EOF >> ${type}.html
 <tr>
  <td>${t}${hand}</td>
  <td>
   <div class="text-right">y<span class="d-none d-lg-inline">es</span></div>
   <div class="text-right">n<span class="d-none d-lg-inline">o</span></div>
  </td>
EOF
  
 for upcard in `seq 2 9` T A; do
  if [ "$upcard" = "T" ]; then
    upcard_n=10
  elif [ "$upcard" = "A" ]; then
    upcard_n=1
  else
    upcard_n=$(($upcard))
  fi
 
  n=1000    # start with n hands
  best="x"  # x means don't know what to so, so play
   
  while [ "${best}" = "x" ]; do
   # tell the user which combination we are trying and how many we will play
   echo -n ${t}${hand}-${upcard} "n="${n}
   
   for play in y n; do
     
    # start with options.conf as a template and add some custom stuff
    cp options.conf blackjack.conf
    cat << EOF >> blackjack.conf
hands = ${n}
dealer2player = internal
arranged_cards = ${pair} $((${upcard_n} + 13)) $((${pair} + 26))
yaml_report = ${t}${hand}-${upcard}-${play}.yaml
log = ${t}${hand}-${upcard}-${play}.log
EOF
 
    # read the current strategy
    while read w p2 p3 p4 p5 p6 p7 p8 p9 pT pA; do
     # w already has the "p"
     strategy[${w},2]=$p2   
     strategy[${w},3]=$p3
     strategy[${w},4]=$p4    
     strategy[${w},5]=$p5    
     strategy[${w},6]=$p6    
     strategy[${w},7]=$p7    
     strategy[${w},8]=$p8    
     strategy[${w},9]=$p9    
     strategy[${w},T]=$pT    
     strategy[${w},A]=$pA    
    done < ${type}.txt
     
    # override the read strategy with the explicit play: y or n
    strategy[${t}${hand},${upcard}]=${play}
     
    # save the new (temporary) strategy
    rm -f ${type}.txt
    for h in A T `seq 9 -1 2`; do
     echo -n "${t}${h}   " >> ${type}.txt
     for u in `seq 2 9` T A; do
      echo -n "${strategy[${t}${h},${u}]}  " >> ${type}.txt
     done
     echo >> ${type}.txt
    done
     
    if [ "${debug}" != "0" ]; then
     cp ${type}.txt ${t}${hand}-${upcard}-${play}.str
    fi  
    
    # ensamble the full bs.txt
    cat hard.txt soft.txt pair.txt > bs.txt
    
    # play!
    blackjack > /dev/null
    
    # evaluate the results
    ev[${t}${hand},${upcard},${play}]=`grep return ${t}${hand}-${upcard}-${play}.yaml | awk '{printf("%+g", $2)}'`
    error[${t}${hand},${upcard},${play}]=`grep error ${t}${hand}-${upcard}-${play}.yaml | awk '{printf("%.1g", $2)}'`
    
   done
   
   # choose the best one
   ev_y=`printf %g ${ev[${t}${hand},${upcard},y]}`
   ev_n=`printf %g ${ev[${t}${hand},${upcard},n]}`
   
   if [ $n -le 999999 ]; then 
    # if we still have room, take into account errors
    error_y=${error[${t}${hand},${upcard},y]}
    error_n=${error[${t}${hand},${upcard},n]}
   else
    # instead of running infinite hands, above a threshold asume errors are zero
    error_y=0
    error_n=0
   fi  
 
   echo -ne "\ty=${ev_y} (${error_y})"
   echo -ne "\tn=${ev_n} (${error_n})"
   
   if   (( $(echo "${ev_y}-${error_y} > ${ev_n}+${error_n}" | bc -l) )); then
    best="y"
    echo -e "\tyes"
   elif (( $(echo "${ev_n}-${error_n} > ${ev_y}+${error_y}" | bc -l) )); then
    best="n"
    echo -e "\tno"
   else
    best="x"
    n=$((${n} * 10))
    echo -e "\tuncertain"
   fi
  done

  echo "| ${t}${hand}-${upcard} | ${n} | ${ev_y} (${error_y}) | ${ev_n} (${error_n}) |" >> table.md
  
  echo " <!-- ${upcard} -->" >> ${type}.html
  echo " <td>" >> ${type}.html
  echo ${ev_y} ${error_y} | awk -f cell.awk >> ${type}.html
  echo ${ev_n} ${error_n} | awk -f cell.awk >> ${type}.html
  echo " </td>" >> ${type}.html
  
  
  strategy[${t}${hand},${upcard}]=${best}
   
  # save the strategy again with the best strategy
  rm -f ${type}.txt
  for h in A T `seq 9 -1 2`; do
   echo -n "${t}${h}   " >> ${type}.txt
   for u in `seq 2 9` T A; do
    echo -n "${strategy[${t}${h},${u}]}  " >> ${type}.txt
   done
   echo >> ${type}.txt
  done
 done
done

 
cat header.txt hard.txt header.txt soft.txt header.txt pair.txt > bs.txt
if [ "${debug}" == "0" ]; then
 rm -f *.yaml
 rm -f *.str
 rm -f *.log
fi
 

```

-------
:::{.text-center}
[Previous](../08-mimic-the-dealer) | [Index](../) | [Next](../)
:::
