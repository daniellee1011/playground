package src;

public class Board {
    private ChessPiece[][] grid = new ChessPiece[8][8];

    public Board() {

    }

    private void initializeBoard() {
        // Add pawns
        for (int i = 0; i < 8; i++) {
            grid[1][i] = new Pawn("Black", new Position(1, i));
            grid[6][i] = new Pawn("White", new Position(6, i));
        }
        // Add Rooks
        grid[0][0] = new Rook("Black", new Position(0, 0));
        grid[0][7] = new Rook("Black", new Position(0, 7));
        grid[7][0] = new Rook("White", new Position(7, 0));
        grid[7][7] = new Rook("White", new Position(7, 7));
    }

    public ChessPiece getPieceAt(Position position) {
        return grid[position.x][position.y];
    }

    public void setPieceAt(Position position, ChessPiece piece) {
        grid[position.x][position.y] = piece;
    }

    public boolean movePiece(Position start, Position end) {
        ChessPiece piece = getPieceAt(start);
        if (piece != null && piece.isValidMove(start, end, this)) {
            setPieceAt(end, piece);
            setPieceAt(start,null);
            piece.setPosition(end);
            return true;
        }
        return false;
    }

    public boolean isPathClear(Position start, Position end) {
        if (start.x == end.x) {
            int step = start.y < end.y ? 1 : -1;
            for (int y = start.y + step; y != end.y; y += step) {
                if (getPieceAt(new Position(start.x, y)) != null) return false;
            }
        } else if (start.y == end.y) {
            int step = start.x < end.x ? 1 : -1;
            for (int x = start.x + step; x != end.x; x += step) {
                if (getPieceAt(new Position(x, start.y)) != null) return false;
            }
        }
        return true;
    }
}
