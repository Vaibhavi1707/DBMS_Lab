import java.util.Scanner;

public class Application {
    private DBManager dbManager;
    private MovieService movieService;
    private Scanner sc;

    public Application() {
        this.dbManager = new DBManager();
        this.movieService = new MovieService(dbManager);
        this.sc = new Scanner(System.in);
    }

    private void showOptions() {
        System.out.println("Enter the choice number for the below options:");

        System.out.println("1 -> View all movies");
        System.out.println("2 -> Add new movie");
        System.out.println("3 -> Update a field");
        System.out.println("4 -> Delete a movie");
        System.out.println("0 -> Close");
    }

    private int acceptChoice() {
        System.out.println("Enter your choice");
        return this.sc.nextInt();
    }

    public static void main(String[] args) {
        Application app = new Application();

        app.showOptions();
        int choice = app.acceptChoice();

        while (choice != 0) {
            switch(choice) {
                case 1: app.movieService.getAllMovies();
                break;
                default: System.out.println("To be implemented :)");
            }

            System.out.println();
            choice = app.acceptChoice();
            System.out.println();
        }

        app.dbManager.closeConnection();
        System.out.println("Thank you!");
    }    
}