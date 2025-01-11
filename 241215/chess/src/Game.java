package src;

import java.util.ArrayList;
import java.util.List;

public class Game {
    private Board board;
    private List<String> moveHistory = new ArrayList<>();
    private Player whitePlayer;
    private Player blackPlayer;
    private Player currentPlayer;

    public Game(Player whitePlayer, Player blackPlayer) {
        this.whitePlayer = whitePlayer;
        this.blackPlayer = blackPlayer;
        this.currentPlayer = whitePlayer;
        this.board = new Board();
    }

    public void startGame() {
        System.out.println("src.Game started between " + whitePlayer.getName() + " and " + blackPlayer.getName());
    }

    public boolean makeMove(Position start, Position end) {
        if (board.movePiece(start, end)) {
            moveHistory.add(currentPlayer.getName() + " moved from " + start + " to " + end);
            switchPlayer();
            return true;
        }
        System.out.println("Invalid move!");
        return false;
    }

    private void switchPlayer() {
        currentPlayer = currentPlayer == whitePlayer ? blackPlayer : whitePlayer;
    }

    public Board getBoard() {
        return board;
    }

    public Player getCurrentPlayer() {
        return currentPlayer;
    }
}
