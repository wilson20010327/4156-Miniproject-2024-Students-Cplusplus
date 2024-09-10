# BugLists
## Course.cpp
* Course init enrolledStudentCount with 500, change it into 0
> commit [93bcf1b](https://github.com/wilson20010327/4156-Miniproject-2024-Students-Cplusplus/commit/93bcf1b4994e5dfdc41636e049fdfabfea39e945)
```diff
Course::Course(int capacity, const std::string& instructorName,
               const std::string& courseLocation, const std::string& timeSlot)
    : enrollmentCapacity(capacity),
-      enrolledStudentCount(500),
+      enrolledStudentCount(0),
      courseLocation(courseLocation),
      instructorName(instructorName),
      courseTimeSlot(timeSlot) {}
```
* enrolledStudent should check whether enrolledStudentCount is out of the limit of the class. If the class is fulled than it return false, and do not thing otherwise enrolledStudentCount+1
> commit [93bcf1b](https://github.com/wilson20010327/4156-Miniproject-2024-Students-Cplusplus/commit/93bcf1b4994e5dfdc41636e049fdfabfea39e945)
```diff
bool Course::enrollStudent() {
+  if (enrolledStudentCount >= enrollmentCapacity) {
+    return false;
+  }
  enrolledStudentCount++;
-  return false;
+  return true;
}
```
* dropStudent should check whether enrolledStudentCount is 0. If the class is 0 than it return false, and do not thing otherwise enrolledStudentCount-1
> commit [93bcf1b](https://github.com/wilson20010327/4156-Miniproject-2024-Students-Cplusplus/commit/93bcf1b4994e5dfdc41636e049fdfabfea39e945)
```diff
bool Course::dropStudent() {
+  if (enrolledStudentCount == 0) return false;
  enrolledStudentCount--;
-  return false;
+  return true;
}
```
* getInstructorName should return instructorName not courseTimeSlot
> commit [93bcf1b](https://github.com/wilson20010327/4156-Miniproject-2024-Students-Cplusplus/commit/93bcf1b4994e5dfdc41636e049fdfabfea39e945)
```diff
- std::string Course::getInstructorName() const { return courseTimeSlot; }
+ std::string Course::getInstructorName() const { return instructorName; }
```
* getInstructorName should return getCourseTimeSlot not instructorName
> commit [93bcf1b](https://github.com/wilson20010327/4156-Miniproject-2024-Students-Cplusplus/commit/93bcf1b4994e5dfdc41636e049fdfabfea39e945)
```diff
- std::string Course::getCourseTimeSlot() const { return instructorName; }
+ std::string Course::getCourseTimeSlot() const { return courseTimeSlot; }
```
* isCourseFull should be enrollmentCapacity <= enrolledStudentCount
> commit [93bcf1b](https://github.com/wilson20010327/4156-Miniproject-2024-Students-Cplusplus/commit/93bcf1b4994e5dfdc41636e049fdfabfea39e945)
```diff
bool Course::isCourseFull() const {
-  return enrollmentCapacity > enrolledStudentCount;
+  return enrollmentCapacity <= enrolledStudentCount;
}
```
* Not bug but I added operator( ==, !=) in this class 
> commit [bb12b41](https://github.com/wilson20010327/4156-Miniproject-2024-Students-Cplusplus/commit/bb12b41d729f34dd13a32e1c111e195ae52e5f1b)
## Department.cpp
* getDepartmentChair return static string, it should return variable departmentChair.
> commit [bb12b41](https://github.com/wilson20010327/4156-Miniproject-2024-Students-Cplusplus/commit/bb12b41d729f34dd13a32e1c111e195ae52e5f1b)
```diff
- std::string Department::getDepartmentChair() const { return "departmentChair"; }
+ std::string Department::getDepartmentChair() const { return departmentChair; }
```