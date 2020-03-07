define(case_title, Internal player)
---
title: case_title
...

# case_title

> Difficulty: case_difficulty/100

If `libreblackjack` is called with the `-i` option, it uses an _internal_ player to play against itself. By default it plays basic strategy. Run 

```terminal
include(run.sh)dnl
```

and you will get a report with the results of one million hands.

```yaml
include(report.yaml)
```

case_nav
