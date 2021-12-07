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
        System.out.println("4 -> Delete a movie by name");
        System.out.println("5 -> View movie by ID");
        System.out.println("6 -> View movie by name");
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
                case 1: app.movieService.getMovies("");
                break;
                case 2: {
                    System.out.println("Enter name of the movie: ");
                    String movieName = app.sc.next();

                    System.out.println("Enter year in which it was released: ");
                    int yearOfRelease = app.sc.nextInt();

                    System.out.println("Enter the movie watch time in minutes: ");
                    int lengthInMin = app.sc.nextInt();

                    System.out.println("Enter the language of the movie: ");
                    String language = app.sc.next();

                    System.out.println("Enter description of the movie:");
                    String description = app.sc.next();

                    System.out.println("Enter genre of the movie: ");
                    String genre = app.sc.next();

                    System.out.println("Enter directors full name: ");
                    String directorName = app.sc.next();
                    app.movieService.addMovie(movieName, yearOfRelease, lengthInMin, language, description, genre, directorName);
                    System.out.println("Movie added successfully!");
                }
                break;
                case 3: {
                    System.out.println("Enter the id of the movie to be updated");
                    int movieId = app.sc.nextInt();

                    System.out.println("Enter new name of the movie: ");
                    String movieName = app.sc.next();

                    System.out.println("Enter new year in which it was released: ");
                    int yearOfRelease = app.sc.nextInt();

                    System.out.println("Enter new movie watch time in minutes: ");
                    int lengthInMin = app.sc.nextInt();

                    System.out.println("Enter new language of the movie: ");
                    String language = app.sc.next();

                    System.out.println("Enter new description of the movie:");
                    String description = app.sc.next();

                    System.out.println("Enter new genre of the movie: ");
                    String genre = app.sc.next();

                    System.out.println("Enter new directors full name: ");
                    String directorName = app.sc.next();
                    app.movieService.updateMovie(movieId, movieName, yearOfRelease, lengthInMin, language, description, genre, directorName);
                    System.out.println("Movie updated successfully!");
                }
                break;
                case 4: {
                    System.out.println("Enter name of the movie to be deleted: ");
                    String movieName = app.sc.next();
                    app.movieService.deleteMovieByName(movieName);
                    System.out.println("Movie deleted successfully!");
                }
                break;
                case 5: {
                    System.out.println("Enter the id of the movie to be viewed");
                    int movieId = app.sc.nextInt();

                    app.movieService.getMovies("movie_id = " + Integer.toString(movieId));
                }
                break;
                case 6: {
                    System.out.println("Enter the name of the movie viewed");
                    String movieName = app.sc.next();

                    app.movieService.getMovies("name = '" + movieName + "'");
                }
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