package src;

public class Rook extends ChessPiece {
    public Rook(String color, Position position) {
        super("src.Rook", color, position);
    }

    @Override
    public boolean isValidMove(Position start, Position end, Board board) {
        if (start.x == end.x || start.y == end.y) {
            return board.isPathClear(start, end);
        }
        return false;
    }
}
