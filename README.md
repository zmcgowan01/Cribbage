# Cribbage

Several important things are needed to create the game of cribbage.  They will be divided in such a way
that certain features that can be re-used in other card games will be encapsulated for that purpose.

Deck: the deck contains 52 Cards, each card is assigned a suit (spade, club, diamond, heart) with a
character symbol to identify the card (Ace, King, Queen, Jack, 2-10).  For cribbage, the value of these
cards will be Ace = 1, King/Queen/Jack = 10, number card values match their symbols.

Objective of cribbage: Cribbage can be played as 1v1, 1v1v1, or 2v2.  I will start with the creation of 
the 1v1 game.  In this game mode, the objective is to be the first player to score 121 points. The game
is completed in rounds.  For each round, one player is the dealer.  The dealer will deal 6 cards to each
player.  The players will then select 4 cards to keep, discarding the other 2 cards into a third hand called
the "crib".  The crib is a hand that belongs to the dealer and the points in that hand will be awarded to the 
dealer at the conclusion of the hand.
After players have selected the 4 cards they would like to keep, the non-dealing player will "cut" the deck,
i.e. select a random point in the deck.  The top card after the cut is turned over, this card is called the
"cut card".
The round is then scored in two phases.  The first phase is called "pegging".  Pegging requires the non-dealing
player to "play" a card from his or her hand by placing it phase up on the table.  Then, the dealing player will
select a card to play, and this continues until no players have cards remaining.  There are a few rules and ways
to score points during this phase:
  -if a player plays a card that matches the previously played card by the opponent, that player is awarded 2 points.
  -if a player plays a card that matches two previously played cards, that player is awarded 6 points (e.g., three
  7's played consecutively).
  -if a player plays a card that matches the three previously played cards, that player is awarded 12 points (e.g.,
  four 2's played consecutively).
  -Points are awarded for 3 or more consecutively played cards that form a straight.  The number of points awarded
  
It took an average of 5.76ns to count the points in a 5 card hand, calculated from a 200 hand sample size randomly
chosen.

In cribbage you are dealt a 6 card hand and must choose 4 cards to keep.  6 choose 4 results in 15 different 
combinations, for each combination there could be one of 47 different cut cards, making the total number of 
combinations at 15*47 = 705.  Unless a flush is possible, we could assume the cut card is one of the 13 
different card types and disregard suit.  That gives 15*13 = 195 combinations, and the likelihood of the 
cut cards given the knowledge of what cards are in your hand can be calculated into the decision making of
which two cards to discard.