# CPPMixed
Class Example

This program demonstrates several key concepts:

1. Mixed Inheritance:
   - Concrete base class `Course` with implemented functionality
   - Abstract interface `IAssessable` with pure virtual functions
   - `GradedCourse` inheriting from both

2. Concrete Base Class Features:
   - Manages basic course information
   - Has fully implemented methods
   - Contains protected members that derived classes can access

3. Interface Features:
   - Pure virtual functions for assessment management
   - No implementation, only method declarations
   - Defines a contract that derived classes must fulfill

4. Derived Class Implementation:
   - Inherits and uses concrete functionality from `Course`
   - Implements all pure virtual functions from `IAssessable`
   - Adds its own specific functionality

5. Error Handling:
   - Validates assessment weights
   - Checks for matching score counts
   - Validates grade ranges

The program models a university course system where:
- Basic course information is handled by the concrete base class
- Assessment functionality is defined by the interface
- `GradedCourse` combines both to create a fully functional graded course
