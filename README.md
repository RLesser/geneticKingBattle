# geneticKingBattle
A genetic-algorithm-like program based on 538's similar riddler.

This project was inspired by the [FiveThirtyEight Riddler on 2/3/17](https://fivethirtyeight.com/features/can-you-rule-riddler-nation/)

### The question, from the FiveThirtyEight article:
> In a distant, war-torn land, there are 10 castles. There are two warlords: you and your archenemy. Each castle has its own strategic value for a would-be conqueror. Specifically, the castles are worth 1, 2, 3, …, 9, and 10 victory points. You and your enemy each have 100 soldiers to distribute, any way you like, to fight at any of the 10 castles. Whoever sends more soldiers to a given castle conquers that castle and wins its victory points. If you each send the same number of troops, you split the points. You don’t know what distribution of forces your enemy has chosen until the battles begin. Whoever wins the most points wins the war.

For FiveThirtyEight, readers submitted their battle plans, 1382 in all, and the winner of the competition had the best W-L record against all other kings.

### My approach:
Instead of many kings battling at once, I was interested in how strategy among a small set of kings would evolve over many iterations. After each year, kings would have a set amount of "children", or slightly mutated versions of the parent distribution. The number of "children" each king had was based on how well they did against the other kings of their year.
This "survival of the fittest" iteratative process, combined with the mutation between each generation, allow for a constantly evolving set of strategies.
