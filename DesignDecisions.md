Chess Engine Initial Design Decisions
=====================================

This document details the initial design decisions made for this chess
engine.

The decisions were made based upon the following criteria:

- Performance
- Simplicity

In general I erred on the side of simplicity for this project rather
that going for maximum performance. The rationale for this is simple,
this project is predominantly for the purpose of learning how to design
and implement programs utilizing complex algorithms. I have no illusions
that this chess engine will ever compete with existing engines such as
Stockfish.

# Board Representation

## Pieces

This engine will represent each piece using a single byte. The first bit
represents the colour of the piece, it is 0 for black and 1 for white.
The second bit represents whether the piece has moved, it is 0 if the
piece has not yet moved and 1 if it has. The next 6 bits represent the
type of the piece. As there are 6 pieces only one of these 6 bits is set
to 1 and the rest are left as 0.

Bit:
1. Colour of the piece (0 for black, 1 for white).
2. Whether the piece has moved (0 if not, 1 otherwise).
3. Pawn (1 if the piece is a pawn, 0 otherwise).
4. Knight (1 if the piece is a knight, 0 otherwise).
5. Bishop (1 if the piece is a bishop, 0 otherwise).
6. Rook (1 if the piece is a rook, 0 otherwise).
7. Queen (1 if the piece is a queen, 0 otherwise).
8. King (1 if the piece is a king, 0 otherwise).

Example. A white knight which has made at least one move would be as
follows: 0b00001011

I chose this representation as it is simple yet compact, allowing me to
store most of the information of the board in a single 64-Byte array. I
think that this works well with the overrall board representation
outlined below.

## Board



# Resources and References