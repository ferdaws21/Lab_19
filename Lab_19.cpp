#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

struct Review {
    double rating;
    std::string comment;
    Review* next;
};

class Movie {
private:
    std::string title;
    Review* head;

public:
    
    Movie(const std::string& movieTitle) : title(movieTitle), head(nullptr) {}

    
    void addReview(double rating, const std::string& comment) {
        Review* newReview = new Review{rating, comment, head};
        head = newReview;
    }

   
    void outputReviews() const {
        std::cout << "Movie: " << title << std::endl;
        Review* current = head;
        int index = 1;

        while (current != nullptr) {
            std::cout << "    > Review #" << index << ": " << std::fixed << std::setprecision(1)
                      << current->rating << ": " << current->comment << std::endl;
            current = current->next;
            index++;
        }
    }

    
    ~Movie() {
        Review* current = head;
        while (current != nullptr) {
            Review* next = current->next;
            delete current;
            current = next;
        }
    }
};


double generateRandomRating() {
    return 1.0 + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (5.0 - 1.0)));
}


std::vector<Movie> createMoviesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string comment;
    std::vector<Movie> movies;

    
    movies.emplace_back("Movie 1");
    movies.emplace_back("Movie 2");
    movies.emplace_back("Movie 3");
    movies.emplace_back("Movie 4");

    if (file.is_open()) {
        int movieIndex = 0;
        while (std::getline(file, comment) && movieIndex < 4) {
            double rating = generateRandomRating();
            movies[movieIndex].addReview(rating, comment);
            movieIndex = (movieIndex + 1) % 4; 
        }
        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
    }

    return movies;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); 
    
    std::vector<Movie> movies = createMoviesFromFile("reviews.txt");

   
    for (const auto& movie : movies) {
        movie.outputReviews();
        std::cout << std::endl;
    }

    return 0;
}
