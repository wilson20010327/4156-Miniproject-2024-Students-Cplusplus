// Copyright 2024 Wilson Liang
#include <gtest/gtest.h>

#include "Course.h"

TEST(CourseUnitTests, EmptyInit) {
  Course emptyCourse = Course();
  // Expect equality.
  EXPECT_EQ(emptyCourse.getCourseLocation(), "");
  EXPECT_EQ(emptyCourse.getInstructorName(), "");
  EXPECT_EQ(emptyCourse.getCourseTimeSlot(), "");
  EXPECT_EQ(emptyCourse.isCourseFull(), false);
}
TEST(CourseUnitTests, DetialInit) {
  Course detailCourse =
      Course(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
  // Expect equality.
  EXPECT_EQ(detailCourse.getCourseLocation(), "Griffin Newbold");
  EXPECT_EQ(detailCourse.getInstructorName(), "417 IAB");
  EXPECT_EQ(detailCourse.getCourseTimeSlot(), "11:40-12:55");
  EXPECT_EQ(detailCourse.isCourseFull(), false);
}

TEST(CourseUnitTests, EmptyInitDisplay) {
  Course emptyCourse = Course();
  // Expect equality.
  EXPECT_EQ(emptyCourse.display(), "\nInstructor: ; Location: ; Time: ");
}
TEST(CourseUnitTests, DetialInitDisplay) {
  Course detailCourse =
      Course(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
  // Expect equality.
  EXPECT_EQ(
      detailCourse.display(),
      "\nInstructor: Griffin Newbold; Location: 417 IAB; Time: 11:40-12:55");
}
