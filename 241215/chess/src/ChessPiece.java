package src;

public abstract class ChessPiece {
    String type;
    String color;
    Position position;

    public ChessPiece(String type, String color, Position position) {
        this.type = type;
        this.color = color;
        this.position = position;
    }

    public String getType() {
        return type;
    }

    public Position getPosition() {
        return position;
    }

    public void setPosition(Position position) {
        this.position = position;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public abstract boolean isValidMove(Position start, Position end, Board board);
}
