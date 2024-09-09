// Copyright 2024 Wilson Liang
#include <gtest/gtest.h>

#include <fstream>

#include "Department.h"

TEST(DepartmentUnitTests, EmptyInit) {
  Department tempDepartment = Department();
  EXPECT_EQ(tempDepartment.getNumberOfMajors(), 0);
}

TEST(DepartmentUnitTests, DetailInit) {
  std::string deptCode = "COMS";
  std::map<std::string, std::shared_ptr<Course>> courses;
  std::string departmentChair = "Jacky";
  int numberOfMajors = 5;
  std::shared_ptr<Course> coms3311 = std::shared_ptr<Course>();
  courses["3311"] = coms3311;
  Department tempDepartment =
      Department(deptCode, courses, departmentChair, numberOfMajors);
  EXPECT_EQ(tempDepartment.getCourseSelection(), courses);
  EXPECT_EQ(tempDepartment.getDepartmentChair(), departmentChair);
  EXPECT_EQ(tempDepartment.getNumberOfMajors(), numberOfMajors);
}

TEST(DepartmentUnitTests, MajorAddandDropFunction) {
  Department tempDepartment = Department();
  for (int i = 0; i < 5; i++) {
    tempDepartment.addPersonToMajor();
    EXPECT_EQ(tempDepartment.getNumberOfMajors(), i + 1);
  }
  for (int i = 5; i > 0; i--) {
    EXPECT_EQ(tempDepartment.getNumberOfMajors(), i);
    tempDepartment.dropPersonFromMajor();
  }
  EXPECT_EQ(tempDepartment.getNumberOfMajors(), 0);
}

TEST(DepartmentUnitTests, AddCousreFunction) {
  Department tempDepartment = Department();
  std::map<std::string, std::shared_ptr<Course>> courses;
  std::shared_ptr<Course> coms3311 = std::shared_ptr<Course>();
  courses["3311"] = coms3311;
  tempDepartment.addCourse("3311", coms3311);
  EXPECT_EQ(tempDepartment.getCourseSelection(), courses);
}
TEST(DepartmentUnitTests, CreateCousreFunction) {
  Department tempDepartment = Department();
  std::map<std::string, std::shared_ptr<Course>> courses;
  std::string courseId = "3311";
  std::string instructorName = "Jack";
  std::string courseLocation = "Mudd 451";
  std::string courseTimeSlot = "11:40-12:55";
  int capacity = 500;
  std::shared_ptr<Course> coms3311 = std::make_shared<Course>(
      capacity, instructorName, courseLocation, courseTimeSlot);
  courses[courseId] = coms3311;
  EXPECT_EQ(tempDepartment.getCourseSelection().size(), 0);
  tempDepartment.createCourse(courseId, instructorName, courseLocation,
                              courseTimeSlot, capacity);
  EXPECT_EQ(tempDepartment.getCourseSelection().size(), 1);
  EXPECT_EQ(*(tempDepartment.getCourseSelection()[courseId].get()),
            *(courses[courseId].get()));
}
TEST(DepartmentUnitTests, DisplayFunciton) {
  std::string deptCode = "COMS";
  std::string departmentChair = "Jacky";
  int numberOfMajors = 5;
  std::map<std::string, std::shared_ptr<Course>> courses;
  std::string courseId = "3311";
  std::string instructorName = "Jack";
  std::string courseLocation = "Mudd 451";
  std::string courseTimeSlot = "11:40-12:55";
  int capacity = 500;
  std::shared_ptr<Course> coms3311 = std::make_shared<Course>(
      capacity, instructorName, courseLocation, courseTimeSlot);
  courses[courseId] = coms3311;

  courseId = "3313";
  std::shared_ptr<Course> coms3313 = std::make_shared<Course>(
      capacity, instructorName, courseLocation, courseTimeSlot);
  courses[courseId] = coms3313;
  Department tempDepartment =
      Department(deptCode, courses, departmentChair, numberOfMajors);
  std::string expectedResult =
      "COMS 3311: \nInstructor: Jack; Location: Mudd 451; Time: 11:40-12:55\n"
      "COMS 3313: \nInstructor: Jack; Location: Mudd 451; Time: 11:40-12:55\n";
  EXPECT_EQ(tempDepartment.display(), expectedResult);
}
TEST(DepartmentUnitTests, DeserializeAndSerialize) {
  std::string deptCode = "COMS";
  std::string departmentChair = "Jacky";
  int numberOfMajors = 5;
  std::map<std::string, std::shared_ptr<Course>> courses;
  std::string courseId = "3311";
  std::string instructorName = "Jack";
  std::string courseLocation = "Mudd 451";
  std::string courseTimeSlot = "11:40-12:55";
  int capacity = 500;
  std::shared_ptr<Course> coms3311 = std::make_shared<Course>(
      capacity, instructorName, courseLocation, courseTimeSlot);
  courses[courseId] = coms3311;

  courseId = "3313";
  std::shared_ptr<Course> coms3313 = std::make_shared<Course>(
      capacity, instructorName, courseLocation, courseTimeSlot);
  courses[courseId] = coms3313;
  Department tempDepartment =
      Department(deptCode, courses, departmentChair, numberOfMajors);
  std::ofstream outFile("Log.txt");
  tempDepartment.serialize(outFile);
  outFile.close();
  std::ifstream inFile("Log.txt");
  Department tempDepartment2 = Department();
  tempDepartment2.deserialize(inFile);
  EXPECT_EQ(tempDepartment.display(), tempDepartment2.display());
}
