#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

struct Review // Review Linked List
{
    double rating;
    string comment;
    
    // Linked List Creation
    Review* next;
};

class Movie
{
    private:
        string title;
        Review* headReviewNode;
    
    public:

    // Constructor
    Movie(string inTitle)
    {
        title = inTitle;
        headReviewNode = nullptr;
    }

    // Setters
    void setMovieTitle(string inTitle) { title = inTitle; } // Sets Movie Title
    void setHeadReviewNode(Review* inHeadNode) { headReviewNode = inHeadNode; }

    // Getters
    string getMovieTitle() { return title; }
    Review* getHeadReviewNode() { return headReviewNode; }

    // Function Prototypes for our Movie Objects
    void addReview(double rating, string comment);
    void printReviews();
};

void Movie::addReview(double rating, string comment) // Adds a review onto a monvie object
{
    // Using head first LL
    Review* tempReview = new Review;

    // Initialize Values
    tempReview->rating = rating;
    tempReview->comment = comment;

    // Link to Second Node
    tempReview->next = headReviewNode;

    // Make it First Node
    headReviewNode = tempReview;
}

void Movie::printReviews()
{
    cout << "Movie: " << title << endl;

    Review* traversalPtr = headReviewNode;
    double ratingTotal = 0.0;
    double ratingCount = 0.0;

    while (traversalPtr)
    {
        cout << "Rating: " << traversalPtr->rating << endl;
        cout << "Comment: " << traversalPtr->comment << endl;
        ratingTotal += traversalPtr->rating;
        ratingCount++;

        // Point to Next in Line
        traversalPtr = traversalPtr->next;
    }

    // Print Average
    cout << "Average Rating Score: " << ratingTotal / ratingCount << endl;
}

// Global Function Prototypes
double randomNumberGenerator();
void populateReviews(vector<Movie>& movieList, string textFileName);


int main()
{
    // Initialize the random generator 
    srand(time(0));

    // Create Vector of Movies
    vector<Movie> movieList;

    // Add some Movies
    movieList.push_back(Movie("Dispicable Me"));
    movieList.push_back(Movie("Joker 2"));
    movieList.push_back(Movie("Big Hero 6"));
    movieList.push_back(Movie("Lion King"));

    // Populate Reviews on each Movie
    populateReviews(movieList, "reviews.txt");

    for (auto& movie : movieList) // Range Based Loop to call print functions
    {
        movie.printReviews();
    }

    return 0;
}

double randomNumberGenerator()
{
    int randomNumber = rand() % 5 + 1;
    return static_cast<double>(randomNumber);
}

void populateReviews(vector<Movie>& movieList)
{
    ifstream reviewList("reviews.txt");

    // Test if file was opened properly
    if (!reviewList)
    {
        cout << "File Stream Error" << endl;
        return;
    }

    // Create some tracking Variables to ensure sizing is accurate and secure
    string currentComment;
    int movieCount = 0;

    // Populate Vector by Iterating Per Movie
    for (int movieCount = 0; movieCount < movieList.size(); movieCount++)
    {
        for (int reviewCount = 0; reviewCount < 3; reviewCount++)
        {
            // If we are able to getline and its not empty, populate that Movie Review
            if (getline(reviewList, currentComment) && !currentComment.empty())
            {
                // Generate our Rating & Populate comment
                double rating = randomNumberGenerator();
                movieList.at(movieCount).addReview(rating, currentComment);
            }
        }
    }

    // Close File
    reviewList.close();

}
