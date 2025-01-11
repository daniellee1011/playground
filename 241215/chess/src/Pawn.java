package src;

public class Pawn extends ChessPiece {
    public Pawn(String color, Position position) {
        super("src.Pawn", color, position);
    }

    @Override
    public boolean isValidMove(Position start, Position end, Board board) {
        int direction = color.equals("White") ? -1 : 1;

        if (start.y == end.y && start.x + direction == end.x && board.getPieceAt(end) == null) {
            return true; // Normal forward move
        }

        if (Math.abs(end.y - start.y) == 1 && start.x + direction == end.x && board.getPieceAt(end) != null) {
            return true; // Capturing move
        }

        return false;
    }
}
