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

To implement this I have used a class called Pieces which has a single
data member (s_pieces). Most of the methods are inline for efficiency,
I think that this abstraction makes the code much more readable and does
not really add any overhead to efficiency.

## Board

*(Ammended: I have decided to drop the piece lists for now as though
they have the potential to speed up the aglorithms they are difficult to
get under unit testing. For the sake of development speed, I will elect
to not implement them for now. I hope they will not be too difficult to
add in the future.)*

For the overall board representation, I have chosen to use a 64-byte
array. Each byte representing a piece as per the above subsection. ~~I
will supplement this with two piece lists, one for white and one for
black. The hope with this is that it will simplify and potentially speed
up the move generation algorithms.~~

- Piece Array - 64 bytes.
- ~~White Piece List - Up to 16 bytes.~~
- ~~Black Piece List - Up to 16 bytes.~~

~~As seen, this gives a total of 96 bytes for the representation of the
pieces (plus whatever overhead the standard library array and list
containers have).~~

I will also need to store some meta information for things such as En
Passant. The space required for these will be negligable compared to the
pieces however.

To implement this I have created a class called Board.

## Moves

For the representation of moves, I have chosen to use the encoding found
here on the chess programming wiki:
https://www.chessprogramming.org/Encoding_Moves

This encoding uses a single 16-bit unsigned short to store each move.
Bits [10-15] store the starting square of the move, referred to as the
'init' square. Bits [4-9] store the ending square of the move referred
to as the 'dest' square. Bit 3 indicates whether the move is a
promotion. Bit 2 indicates whether the move is a capture. Bits 0 and 1
indicate which type of piece the promotion is to.

- Bits 0 to 1 - What type of piece the promotion is to.
    - 00 - Knight
    - 01 - Bishop
    - 10 - Rook
    - 11 - Queen
- Bit 2 - Whether the move is a capture.
- Bit 3 - Whether the move is a promotion.
- Bits 4 to 9 - The 'init' square of the move.
- Bits 10 to 15 - The 'dest' square of the move.

To implement this I have used a class called Move which has a single
data member (s_move). Most of the methods are inline for efficiency,
I think that this abstraction makes the code much more readable and does
not really add any overhead to efficiency.

# Resources and References

1. https://www.chessprogramming.org/ This is without a doubt the most
helpful resource out there for somebody keen on writing their own chess
engine.