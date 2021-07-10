#include "Board.h"

#include <iostream>
#include <sstream>

#include "Helper.h"

namespace ChessEngine
{
	Board::Board():
		m_pieces(StartingPieces)
	{
		UpdatePieceLists();
	}

	Board::Board(const std::string& FEN)
	{
		std::string pieces;
		std::string toPlay;
		std::string castling;
		std::string enPassant;

		std::istringstream FENStream(FEN);
		FENStream >> pieces >> toPlay >> castling >> enPassant;

		char token;

		// Parse the pieces
		std::istringstream piecesStream(pieces);
		int numSquaresParsed = 0;
		Row row = 7;
		Col col = 0;
		while (piecesStream >> token)
		{
			if (token == '/')
			{
				row--;
				col = 0;
			}
			else if (std::isdigit(token))
			{
				for (int i = 0; i < token - '0'; i++)
				{
					m_pieces[Helper::SquareFromRowAndCol(row, col)] = Piece(Piece::Type::Empty, true);
					numSquaresParsed++;
					col++;
				}
			}
			else
			{
				m_pieces[Helper::SquareFromRowAndCol(row, col)] = Piece(token);
				numSquaresParsed++;
				col++;
			}
		}

		if (numSquaresParsed != 64)
		{
			std::string error = "Invalid pieces in FEN string (" + pieces + "), not 64 squares.";
			throw std::invalid_argument(error);
		}

		UpdatePieceLists();

		// Parse whose turn it is to play
		if (toPlay == "w")
		{
			m_whiteToPlay = true;
		}
		else if (toPlay == "b")
		{
			m_whiteToPlay = false;
		}
		else
		{
			std::string error = "Invalid character for 'player to move' + (" + toPlay + ") in FEN string.";
			throw std::invalid_argument(error);
		}

		// Parse the castling rights
		std::istringstream castlingStream(castling);
		m_whiteKingside = m_whiteQueenside = m_blackKingside = m_blackQueenside = false;
		while (castlingStream >> token)
		{
			switch (token)
			{
			case 'k':
				m_whiteKingside = true;
				break;
			case 'q':
				m_whiteQueenside = true;
				break;
			case 'K':
				m_blackKingside = true;
				break;
			case 'Q':
				m_blackQueenside = true;
				break;
			case '-':
				continue;
			default:
				std::string error = "Invalid string for 'castling rights' (" + castling + ") in FEN string.";
				throw std::invalid_argument(error);
			}
		}

		// Parse the en passant square
		if (enPassant == "-")
		{
			m_enPassant.reset();
		}
		else
		{
			m_enPassant = Helper::SquareFromString(enPassant);
		}

		// Get the number of half and full moves
		int halfMoves;
		int fullMoves;
		FENStream >> halfMoves;
		FENStream >> fullMoves;
		m_halfMoves = static_cast<unsigned char>(halfMoves);
		m_fullMoves = static_cast<unsigned char>(fullMoves);
	}

	std::string Board::GetFEN() const
	{
		std::ostringstream FENStream;

		// Output the pieces
		int consecutiveEmptySquares = 0;
		for (Row row = 7; Helper::IsValidRow(row); row--)
		{
			for (Col col = 0; Helper::IsValidCol(col); col++)
			{
				Piece piece = m_pieces[Helper::SquareFromRowAndCol(row, col)];

				if (piece.IsEmpty())
				{
					consecutiveEmptySquares++;
				}
				else
				{
					if (consecutiveEmptySquares > 0)
					{
						FENStream << consecutiveEmptySquares;
						consecutiveEmptySquares = 0;
					}

					FENStream << piece.GetAscii();
				}

				if (!Helper::IsValidCol(col + 1))
				{
					if (consecutiveEmptySquares > 0)
					{
						FENStream << consecutiveEmptySquares;
						consecutiveEmptySquares = 0;
					}

					if (Helper::IsValidRow(row - 1))
					{
						FENStream << '/';
					}
				}
			}
		}
		FENStream << ' ';

		// Output whose turn it is to play
		FENStream << (m_whiteToPlay ? 'w' : 'b');
		FENStream << ' ';

		// Output the castling rights
		if (!m_whiteKingside && !m_whiteQueenside && !m_blackKingside && !m_blackQueenside)
		{
			FENStream << '-';
		}
		else
		{
			if (m_whiteKingside) { FENStream << 'K'; }
			if (m_whiteQueenside) { FENStream << 'Q'; }
			if (m_blackKingside) { FENStream << 'k'; }
			if (m_blackQueenside) { FENStream << 'q'; }
		}
		FENStream << ' ';

		// Output the en passant square
		if (m_enPassant)
		{
			FENStream << Helper::StringFromSquare(*m_enPassant);
		}
		else
		{
			FENStream << '-';
		}
		FENStream << ' ';

		// Output the half and full moves
		FENStream << static_cast<int>(m_halfMoves);
		FENStream << ' ';
		FENStream << static_cast<int>(m_fullMoves);

		return FENStream.str();
	}

	void Board::UpdatePieceLists()
	{
		m_whitePieceList.clear();
		m_blackPieceList.clear();

		for (Square square = 0; Helper::IsValidSquare(square); square++)
		{
			const Piece& piece = m_pieces[square];

			if (!piece.IsEmpty())
			{
				if (piece.IsWhite())
				{
					m_whitePieceList.push_back(std::make_pair(piece, square));
				}
				else
				{
					m_blackPieceList.push_back(std::make_pair(piece, square));
				}
			}
		}
	}
}