#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class ExamException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid input! Please provide a valid response.";
    }
};
template <typename T>
class Question {
public:
    std::string questionText;
    T correctAnswer;

    Question(const std::string& qText, const T& ans)
        : questionText(qText), correctAnswer(ans) {}

    bool checkAnswer(const T& answer) const {
        return correctAnswer == answer;
    }
};
class Exam {
private:
    std::vector<Question<std::string>> questions; 

public:
    void addQuestion(const Question<std::string>& q) {
        questions.push_back(q);
    }

    void conductExam() {
        std::string userAnswer;
        int score = 0;

        for (size_t i = 0; i < questions.size(); ++i) {
            std::cout << "Question " << (i + 1) << ": " << questions[i].questionText << "\n";

            try {
                std::cout << "Your answer: ";
                std::getline(std::cin, userAnswer); 


                if (userAnswer.empty()) {
                    throw ExamException();
                }

            
                if (questions[i].checkAnswer(userAnswer)) {
                    score++;
                }
            } catch (const ExamException& e) {
                std::cerr << e.what() << " Try again.\n";
                --i;  
            }
        }

        std::cout << "You scored " << score << " out of " << questions.size() << "\n";
    }
};

int main() {
    Exam exam;

    
    exam.addQuestion(Question<std::string>("What is the capital of France?", "Paris"));
    exam.addQuestion(Question<std::string>("What is 5 + 3?", "8"));
    exam.addQuestion(Question<std::string>("What is the color of the sky?", "Blue"));


    exam.conductExam();

    return 0;
}
