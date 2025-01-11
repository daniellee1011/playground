package src;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Player whitePlayer = new Player("Alice", "White");
        Player blackPlayer = new Player("Bob", "Black");

        Game chessGame = new Game(whitePlayer, blackPlayer);

        chessGame.startGame();
        displayBoard(chessGame);

        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println(chessGame.getCurrentPlayer().getName() + "'s turn (" +
                    chessGame.getCurrentPlayer().getColor() + ")");
            System.out.println("Enter your move (e.g., 'e2 e4'): ");
            String input = scanner.nextLine();

            if (input.equalsIgnoreCase("quit")) {
                System.out.println("src.Game ended.");
                break;
            }

            String[] positions = input.split(" ");
            if (positions.length != 2) {
                System.out.println("Invalid input. Please enter moves in 'start end' format.");
                continue;
            }

            Position start = parsePosition(positions[0]);
            Position end = parsePosition(positions[1]);

            if (!chessGame.makeMove(start, end)) {
                System.out.println("Invalid move. Try again.");
            }

            displayBoard(chessGame);
        }
        scanner.close();
    }

    private static Position parsePosition(String pos) {
        // Convert algebraic notation (e.g., "e2") to src.Position (row, column)
        int x = 8 - Character.getNumericValue(pos.charAt(1)); // Row (8 to 1 -> 0 to 7)
        int y = pos.charAt(0) - 'a'; // Column ('a' to 'h' -> 0 to 7
        return new Position(x, y);
    }

    private static void displayBoard(Game game) {
        Board board = game.getBoard();
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                ChessPiece piece = board.getPieceAt(new Position(i, j));
                if (piece == null) {
                    System.out.print(". ");
                } else {
                    System.out.print(piece.getType().charAt(0) + " ");
                }
            }
            System.out.println();
        }
    }
}
