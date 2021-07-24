#include "Board.h"

#include <algorithm>
#include <sstream>

#include "Helper.h"

namespace ChessEngine
{
	Board::Board():
		m_pieces(StartingPieces)
	{
		ResetPieceLists();
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

		ResetPieceLists();

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

		// Parse the number of half and full moves
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

	void Board::MakeMove(Move move)
	{
		// It is assumed that the move provided is a valid move. Checking of whether a
		// move is valid will be done at the point where the user move is parsed. All
		// computer generated moves should be legal.

		const Square init = move.GetInitSquare();
		const Square dest = move.GetDestSquare();

		const Piece piece = m_pieces[move.GetInitSquare()];

		// Update the piece array and lists
		if (move.IsQuiet())
		{
			MovePiece(init, dest);
		}
		else if (move.IsKingsideCastles())
		{
			KCastles(move);
		}
		else if (move.IsQueensideCastles())
		{
			QCastles(move);
		}
		else if (move.IsDoublePawnPush())
		{
			MovePiece(init, dest);
		}
		else if (move.IsEnPassantCapture())
		{
			EPCapture(move);
		}
		else if (move.IsPromotion())
		{
			Promotion(move);
		}
		else if (move.IsCapture())
		{
			TakePiece(init, dest);
		}

		// Update castling rights
		if (piece.IsKing() || move.IsKingsideCastles() || move.IsQueensideCastles())
		{
			if (m_whiteToPlay)
			{
				m_whiteKingside = false;
				m_whiteQueenside = false;
			}
			else
			{
				m_blackKingside = false;
				m_blackQueenside = false;
			}
		}
		else if (piece.IsRook())
		{
			if (m_whiteToPlay)
			{
				if (init == WhiteKingsideRookStartingSquare)
				{
					m_whiteKingside = false;
				}
				else if (init == WhiteQueensideRookStartingSquare)
				{
					m_whiteQueenside = false;
				}
			}
			else
			{
				if (init == BlackKingsideRookStartingSquare)
				{
					m_blackKingside = false;
				}
				else if (init == BlackQueensideRookStartingSquare)
				{
					m_blackQueenside = false;
				}
			}
		}

		// Update en passan square
		if (move.IsDoublePawnPush())
		{
			m_enPassant = init + (m_whiteToPlay ? +8 : -8);
		}
		else
		{
			m_enPassant.reset();
		}

		// Update half move counter
		if (piece.IsPawn() || move.IsCapture())
		{
			m_halfMoves = 0;
		}
		else
		{
			m_halfMoves++;
		}

		// Update full move counter
		if (!m_whiteToPlay)
		{
			m_fullMoves++;
		}

		// Update whose turn it is to play
		m_whiteToPlay = !m_whiteToPlay;
	}

	void Board::ResetPieceLists()
	{
		m_whitePieceList.clear();
		m_blackPieceList.clear();

		for (Square square = 0; Helper::IsValidSquare(square); square++)
		{
			const Piece& piece = m_pieces[square];

			if (!piece.IsEmpty())
			{
				auto& pieceList = (piece.IsWhite() ? m_whitePieceList : m_blackPieceList);
				pieceList.push_back(std::make_pair(piece, square));
			}
		}
	}

	void Board::MovePiece(Square init, Square dest)
	{
		Piece piece = m_pieces[init];

		// Update piece array
		m_pieces[init] = Piece::ee;
		m_pieces[dest] = piece;

		// Update piece lists
		auto& pieceList = (m_whiteToPlay ? m_whitePieceList : m_blackPieceList);
		for (auto& [_, squ] : pieceList)
		{
			if (squ == init)
			{
				squ = dest;
				break;
			}
		}
	}

	void Board::TakePiece(Square init, Square dest)
	{
		// Remove captured piece from piece lists
		auto& pieceList = (m_whiteToPlay ? m_blackPieceList : m_whitePieceList);
		std::remove_if(
			pieceList.begin(),
			pieceList.end(),
			[dest](auto& elem) { return (elem.second == dest); }
		);

		MovePiece(init, dest);
	}

	void Board::KCastles(Move move)
	{
		if (m_whiteToPlay)
		{
			MovePiece(WhiteKingStartingSquare, WhiteKingStartingSquare + 2);
			MovePiece(WhiteKingsideRookStartingSquare, WhiteKingStartingSquare + 1);
		}
		else
		{
			MovePiece(BlackKingStartingSquare, BlackKingStartingSquare + 2);
			MovePiece(BlackKingsideRookStartingSquare, BlackKingStartingSquare + 1);
		}
	}

	void Board::QCastles(Move move)
	{
		if (m_whiteToPlay)
		{
			MovePiece(WhiteKingStartingSquare, WhiteKingStartingSquare - 2);
			MovePiece(WhiteQueensideRookStartingSquare, WhiteKingStartingSquare - 1);
		}
		else
		{
			MovePiece(BlackKingStartingSquare, BlackKingStartingSquare - 2);
			MovePiece(BlackQueensideRookStartingSquare, BlackKingStartingSquare - 1);
		}
	}

	void Board::EPCapture(Move move)
	{
		const Square init = move.GetInitSquare();
		const Square dest = m_enPassant.value();

		MovePiece(init, dest);

		const Square captured = dest + (m_whiteToPlay ? -8 : +8);

		m_pieces[captured] = Piece::ee;

		auto & pieceList = (m_whiteToPlay ? m_blackPieceList : m_whitePieceList);
		std::remove_if(
			pieceList.begin(),
			pieceList.end(),
			[captured](auto& elem) { return (elem.second == captured); }
		);
	}

	void Board::Promotion(Move move)
	{
		const Square init = move.GetInitSquare();
		const Square dest = move.GetDestSquare();

		if (move.IsCapture())
		{
			TakePiece(init, dest);
		}
		else
		{
			MovePiece(init, dest);
		}

		Piece promotionPiece = Piece(move.GetPromotionType(), m_whiteToPlay);

		m_pieces[dest] = promotionPiece;

		auto& pieceList = (m_whiteToPlay ? m_whitePieceList : m_blackPieceList);
		std::replace_if(
			pieceList.begin(),
			pieceList.end(),
			[dest](auto& entry) { return (entry.second == dest); },
			std::make_pair(promotionPiece, dest)
		);
	}
}