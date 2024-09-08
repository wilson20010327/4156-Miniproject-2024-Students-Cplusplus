// Copyright 2024 Wilson Liang
#include <gtest/gtest.h>

#include "Course.h"

TEST(CourseUnitTests, EmptyInit) {
  Course emptyCourse = Course();
  // Expect equality.
  EXPECT_EQ(emptyCourse.getCourseLocation(), "");
  EXPECT_EQ(emptyCourse.getInstructorName(), "");
  EXPECT_EQ(emptyCourse.getCourseTimeSlot(), "");
  EXPECT_EQ(emptyCourse.isCourseFull(), true);
}
TEST(CourseUnitTests, DetialInit) {
  Course detailCourse =
      Course(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
  // Expect equality.
  EXPECT_EQ(detailCourse.getInstructorName(), "Griffin Newbold");
  EXPECT_EQ(detailCourse.getCourseLocation(), "417 IAB");
  EXPECT_EQ(detailCourse.getCourseTimeSlot(), "11:40-12:55");
  EXPECT_EQ(detailCourse.isCourseFull(), false);
}

TEST(CourseUnitTests, InrollFunction) {
  Course tempCourse = Course(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
  // Expect equality.
  for (int i = 0; i < 250; i++) {
    EXPECT_EQ(tempCourse.enrollStudent(), true);
  }
  EXPECT_EQ(tempCourse.isCourseFull(), true);
  EXPECT_EQ(tempCourse.enrollStudent(), false);
}
TEST(CourseUnitTests, SetStudentFunction) {
  Course tempCourse = Course(2, "Griffin Newbold", "417 IAB", "11:40-12:55");
  // Expect equality.
  tempCourse.setEnrolledStudentCount(2);
  EXPECT_EQ(tempCourse.isCourseFull(), true);
}
TEST(CourseUnitTests, DropFunction) {
  Course tempCourse = Course(5, "Griffin Newbold", "417 IAB", "11:40-12:55");
  // Expect equality.
  tempCourse.setEnrolledStudentCount(5);
  EXPECT_EQ(tempCourse.isCourseFull(), true);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(tempCourse.dropStudent(), true);
  }
  EXPECT_EQ(tempCourse.dropStudent(), false);
}
TEST(CourseUnitTests, ReassignFunction) {
  Course tempCourse = Course(5, "Griffin Newbold", "417 IAB", "11:40-12:55");
  // Expect equality.
  tempCourse.reassignInstructor("Wilson Liang");
  tempCourse.reassignLocation("417 IA");
  tempCourse.reassignTime("11:40-11:55");
  EXPECT_EQ(tempCourse.getInstructorName(), "Wilson Liang");
  EXPECT_EQ(tempCourse.getCourseLocation(), "417 IA");
  EXPECT_EQ(tempCourse.getCourseTimeSlot(), "11:40-11:55");
}
TEST(CourseUnitTests, DetialInitDisplay) {
  Course detailCourse =
      Course(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
  // Expect equality.
  EXPECT_EQ(
      detailCourse.display(),
      "\nInstructor: Griffin Newbold; Location: 417 IAB; Time: 11:40-12:55");
}
TEST(CourseUnitTests, EqualTest) {
  Course tempCourse1 = Course(5, "Griffin Newbold", "417 IAB", "11:40-12:55");
  Course tempCourse2 = Course(5, "Griffin Newbold", "417 IAB", "11:40-12:55");
  Course tempCourse3 = Course(5, "Griffin Newbold", "41 IAB", "11:40-12:55");
  EXPECT_EQ(tempCourse1, tempCourse2);
  EXPECT_NE(tempCourse1, tempCourse3);
}
