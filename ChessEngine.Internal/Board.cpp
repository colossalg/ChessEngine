#include "pch.h"

#include "Board.h"

#include "BoardHasher.h"
#include "Helper.h"
#include "Move.h"
#include "MoveInverse.h"

namespace ChessEngine
{
	Board::Board():
		m_pieces(StartingPieces),
		m_hash(BoardHasher::Hash(*this))
	{
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

		// Get the hash for this position
		m_hash = BoardHasher::Hash(*this);
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

	void Board::MakeMove(const Move move)
	{
		// It is assumed that the move provided is a valid move. Checking of whether a
		// move is valid will be done at the point where the user move is parsed. All
		// computer generated moves should be legal.

		const Square init = move.GetInitSquare();
		const Square dest = move.GetDestSquare();

		const Piece piece = m_pieces[move.GetInitSquare()];

		// Update the piece array
		if (move.IsQuiet())
		{
			MovePiece(init, dest);
		}
		else if (move.IsKingsideCastles())
		{
			KCastles();
		}
		else if (move.IsQueensideCastles())
		{
			QCastles();
		}
		else if (move.IsDoublePawnPush())
		{
			MovePiece(init, dest);
		}
		else if (move.IsEnPassantCapture())
		{
			EPCapture(init, dest);
		}
		else if (move.IsPromotion())
		{
			Promotion(init, dest, move.GetPromotionType());
		}
		else if (move.IsCapture())
		{
			MovePiece(init, dest);
		}

		// Update castling rights
		if (piece.IsKing() || move.IsKingsideCastles() || move.IsQueensideCastles())
		{
			if (m_whiteToPlay)
			{
				SetWhiteCastleKingside(false);
				SetWhiteCastleQueenside(false);
			}
			else
			{
				SetBlackCastleKingside(false);
				SetBlackCastleQueenside(false);
			}
		}
		else if (piece.IsRook())
		{
			if (m_whiteToPlay)
			{
				if (init == WhiteKingsideRookStartingSquare)
				{
					SetWhiteCastleKingside(false);
				}
				else if (init == WhiteQueensideRookStartingSquare)
				{
					SetWhiteCastleQueenside(false);
				}
			}
			else
			{
				if (init == BlackKingsideRookStartingSquare)
				{
					SetBlackCastleKingside(false);
				}
				else if (init == BlackQueensideRookStartingSquare)
				{
					SetBlackCastleQueenside(false);
				}
			}
		}

		// Update en passan square
		if (move.IsDoublePawnPush())
		{
			SetEnPassant(init + (m_whiteToPlay ? +8 : -8));
		}
		else
		{
			SetEnPassant(std::nullopt);
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

	void Board::UndoMove(const MoveInverse moveInverse)
	{
		const Move move = moveInverse.GetMove();
		
		const Square init = move.GetInitSquare();
		const Square dest = move.GetDestSquare();

		const Piece capturedPiece = moveInverse.GetCapturedPiece();

		// Update the piece array
		if (move.IsQuiet())
		{
			MovePieceInverse(init, dest);
		}
		else if (move.IsKingsideCastles())
		{
			KCastlesInverse();
		}
		else if (move.IsQueensideCastles())
		{
			QCastlesInverse();
		}
		else if (move.IsDoublePawnPush())
		{
			MovePieceInverse(init, dest);
		}
		else if (move.IsEnPassantCapture())
		{
			EPCaptureInverse(init, dest);
		}
		else if (move.IsPromotion())
		{
			PromotionInverse(init, dest, capturedPiece);
		}
		else if (move.IsCapture())
		{
			MovePieceInverse(init, dest, capturedPiece);
		}
		
		// Update castling rights
		SetWhiteCastleKingside(moveInverse.GetWhiteKingside());
		SetWhiteCastleQueenside(moveInverse.GetWhiteQueenside());
		SetBlackCastleKingside(moveInverse.GetBlackKingside());
		SetBlackCastleQueenside(moveInverse.GetBlackQueenside());

		// Update en passant square
		SetEnPassant(moveInverse.GetEnPassant());

		// Update half move counter
		m_halfMoves = moveInverse.GetHalfMoves();

		// Update full move counter
		if (m_whiteToPlay)
		{
			m_fullMoves--;
		}

		// Update whose turn it is to play
		m_whiteToPlay = !m_whiteToPlay;
	}

	inline void Board::RemovePiece(const Square square)
	{
		m_hash = BoardHasher::RemovePiece(m_hash, square, m_pieces[square]);
		m_pieces[square] = Piece::ee;
	}

	inline void Board::InsertPiece(const Square square, const Piece piece)
	{
		m_hash = BoardHasher::InsertPiece(m_hash, square, m_pieces[square]);
		m_pieces[square] = piece;
	}

	inline void Board::SetEnPassant(const EnPassant& enPassant)
	{
		m_hash = BoardHasher::UpdateEnPassant(m_hash, m_enPassant, enPassant);
		m_enPassant = enPassant;
	}

	inline void Board::SetWhiteCastleKingside(bool canCastle)
	{
		if (canCastle != m_whiteKingside)
		{
			m_whiteKingside = canCastle;
			m_hash = BoardHasher::UpdateWhiteCastleKingside(m_hash);
		}
	}

	inline void Board::SetWhiteCastleQueenside(bool canCastle)
	{
		if (canCastle != m_whiteQueenside)
		{
			m_whiteQueenside = canCastle;
			m_hash = BoardHasher::UpdateWhiteCastleQueenside(m_hash);
		}
	}

	inline void Board::SetBlackCastleKingside(bool canCastle)
	{
		if (canCastle != m_blackKingside)
		{
			m_blackKingside = canCastle;
			m_hash = BoardHasher::UpdateBlackCastleKingside(m_hash);
		}
	}

	inline void Board::SetBlackCastleQueenside(bool canCastle)
	{
		if (canCastle != m_blackQueenside)
		{
			m_blackQueenside = canCastle;
			m_hash = BoardHasher::UpdateBlackCastleQueenside(m_hash);
		}
	}

	inline void Board::MovePiece(const Square init, const Square dest)
	{
		Piece pieceAtInit = m_pieces[init];
		Piece pieceAtDest = m_pieces[dest];

		RemovePiece(init);
		RemovePiece(dest);
		InsertPiece(init, Piece::ee);
		InsertPiece(dest, pieceAtInit);
	}

	inline void Board::MovePieceInverse(const Square init, const Square dest, const Piece capturedPiece)
	{
		Piece pieceAtInit = m_pieces[init];
		Piece pieceAtDest = m_pieces[dest];

		RemovePiece(init);
		RemovePiece(dest);
		InsertPiece(init, pieceAtDest);
		InsertPiece(dest, capturedPiece);
	}

	inline void Board::KCastles()
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

	inline void Board::KCastlesInverse()
	{
		if (!m_whiteToPlay)
		{
			MovePieceInverse(WhiteKingStartingSquare, WhiteKingStartingSquare + 2);
			MovePieceInverse(WhiteKingsideRookStartingSquare, WhiteKingStartingSquare + 1);
		}
		else
		{
			MovePieceInverse(BlackKingStartingSquare, BlackKingStartingSquare + 2);
			MovePieceInverse(BlackKingsideRookStartingSquare, BlackKingStartingSquare + 1);
		}
	}

	inline void Board::QCastles()
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

	inline void Board::QCastlesInverse()
	{
		if (!m_whiteToPlay)
		{
			MovePieceInverse(WhiteKingStartingSquare, WhiteKingStartingSquare - 2);
			MovePieceInverse(WhiteQueensideRookStartingSquare, WhiteKingStartingSquare - 1);
		}
		else
		{
			MovePieceInverse(BlackKingStartingSquare, BlackKingStartingSquare - 2);
			MovePieceInverse(BlackQueensideRookStartingSquare, BlackKingStartingSquare - 1);
		}
	}

	inline void Board::EPCapture(const Square init, const Square dest)
	{
		MovePiece(init, dest);

		const Square captureSquare = dest + (m_whiteToPlay ? -8 : +8);

		RemovePiece(captureSquare);
		InsertPiece(captureSquare, Piece::ee);
	}

	inline void Board::EPCaptureInverse(const Square init, const Square dest)
	{
		MovePieceInverse(init, dest);

		const Square captureSquare = dest + (m_whiteToPlay ? +8 : -8);

		RemovePiece(captureSquare);
		InsertPiece(captureSquare, (m_whiteToPlay ? Piece::wp : Piece::bp));
	}

	inline void Board::Promotion(const Square init, const Square dest, const Piece::Type type)
	{
		RemovePiece(init);
		RemovePiece(dest);
		InsertPiece(init, Piece::ee);
		InsertPiece(dest, Piece(type, m_whiteToPlay));
	}

	inline void Board::PromotionInverse(const Square init, const Square dest, const Piece capturedPiece)
	{
		RemovePiece(init);
		RemovePiece(dest);
		InsertPiece(init, (!m_whiteToPlay ? Piece::wp : Piece::bp));
		InsertPiece(dest, capturedPiece);
	}
}