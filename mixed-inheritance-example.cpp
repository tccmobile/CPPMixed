#include <iostream>
#include <string>
#include <vector>

// Concrete base class
class Course {
protected:
    std::string courseName;
    std::string courseCode;
    int creditHours;
    std::string instructor;

public:
    Course(const std::string& name, const std::string& code, int credits, const std::string& prof)
        : courseName(name), courseCode(code), creditHours(credits), instructor(prof) {}
    
    virtual ~Course() = default;

    // Regular member functions
    void displayInfo() const {
        std::cout << "Course: " << courseName << " (" << courseCode << ")\n"
                  << "Credits: " << creditHours << "\n"
                  << "Instructor: " << instructor << "\n";
    }

    void updateInstructor(const std::string& newInstructor) {
        instructor = newInstructor;
        std::cout << "Instructor updated for " << courseCode << "\n";
    }

    std::string getCourseName() const { return courseName; }
    std::string getCourseCode() const { return courseCode; }
    int getCreditHours() const { return creditHours; }
    std::string getInstructor() const { return instructor; }
};

// Abstract interface
class IAssessable {
public:
    virtual ~IAssessable() = default;
    
    // Pure virtual functions
    virtual void addAssessment(const std::string& name, double weight) = 0;
    virtual double calculateFinalGrade(const std::vector<double>& scores) = 0;
    virtual void displayAssessmentStructure() const = 0;
};

// Derived class inheriting from both concrete class and interface
class GradedCourse : public Course, public IAssessable {
private:
    struct Assessment {
        std::string name;
        double weight;
    };
    
    std::vector<Assessment> assessments;
    double passingGrade;

public:
    GradedCourse(const std::string& name, const std::string& code, int credits, 
                 const std::string& prof, double passGrade = 50.0)
        : Course(name, code, credits, prof), passingGrade(passGrade) {}

    // Implementing IAssessable interface
    void addAssessment(const std::string& name, double weight) override {
        // Check if total weight would exceed 100%
        double totalWeight = 0;
        for (const auto& assessment : assessments) {
            totalWeight += assessment.weight;
        }
        
        if (totalWeight + weight > 100.0) {
            std::cout << "Error: Total assessment weight cannot exceed 100%\n";
            return;
        }
        
        assessments.push_back({name, weight});
        std::cout << "Added assessment: " << name << " (Weight: " << weight << "%)\n";
    }

    double calculateFinalGrade(const std::vector<double>& scores) override {
        if (scores.size() != assessments.size()) {
            std::cout << "Error: Number of scores doesn't match number of assessments\n";
            return -1;
        }

        double finalGrade = 0.0;
        for (size_t i = 0; i < scores.size(); ++i) {
            finalGrade += scores[i] * (assessments[i].weight / 100.0);
        }

        return finalGrade;
    }

    void displayAssessmentStructure() const override {
        std::cout << "\nAssessment Structure for " << getCourseCode() << ":\n";
        for (const auto& assessment : assessments) {
            std::cout << "- " << assessment.name << ": " << assessment.weight << "%\n";
        }
        std::cout << "Passing Grade: " << passingGrade << "%\n";
    }

    // Additional methods specific to GradedCourse
    bool isPassing(double grade) const {
        return grade >= passingGrade;
    }

    void setPassingGrade(double newPassingGrade) {
        if (newPassingGrade >= 0 && newPassingGrade <= 100) {
            passingGrade = newPassingGrade;
            std::cout << "Passing grade updated to: " << passingGrade << "%\n";
        } else {
            std::cout << "Error: Invalid passing grade\n";
        }
    }
};

int main() {
    // Create a graded course
    GradedCourse programmingCourse("Advanced Programming", "CS301", 3, "Dr. Smith", 60.0);
    
    // Use methods from concrete base class (Course)
    programmingCourse.displayInfo();
    programmingCourse.updateInstructor("Dr. Johnson");
    
    // Use methods from interface (IAssessable)
    programmingCourse.addAssessment("Midterm", 30.0);
    programmingCourse.addAssessment("Final Project", 40.0);
    programmingCourse.addAssessment("Assignments", 30.0);
    
    programmingCourse.displayAssessmentStructure();
    
    // Calculate final grade
    std::vector<double> studentScores = {85.0, 92.0, 88.0};
    double finalGrade = programmingCourse.calculateFinalGrade(studentScores);
    
    std::cout << "\nFinal Grade: " << finalGrade << "%\n";
    std::cout << "Pass Status: " << (programmingCourse.isPassing(finalGrade) ? "Passed" : "Failed") << "\n";
    
    // Demonstrate error handling
    std::cout << "\nTrying to add assessment that exceeds 100% weight:\n";
    programmingCourse.addAssessment("Extra Credit", 20.0);
    
    // Try calculating with incorrect number of scores
    std::cout << "\nTrying to calculate grade with incorrect number of scores:\n";
    std::vector<double> incorrectScores = {85.0, 92.0};
    programmingCourse.calculateFinalGrade(incorrectScores);

    return 0;
}
