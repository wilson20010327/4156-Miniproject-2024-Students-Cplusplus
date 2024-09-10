// Copyright 2024 Wilson Liang
#include <gtest/gtest.h>

#include "MyApp.h"
#include "RouteController.h"

// Demonstrate some basic assertions.
TEST(RouteControllerUnitTests, SetupTest) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  routeController.index(response);
  EXPECT_EQ(
      response.body,
      "Welcome, in order to make an API call direct your browser or Postman to "
      "an endpoint "
      "\n\n This can be done using the following format: \n\n "
      "http://127.0.0.1:8080/endpoint?arg=value");
}
TEST(RouteControllerUnitTests, RetrieveDepartmentSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;
  request.url_params = crow::query_string("?deptCode=COMS");
  routeController.retrieveDepartment(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body,
            MyApp::getDatabase()->getDepartmentMapping()["COMS"].display());
}
TEST(RouteControllerUnitTests, RetrieveDepartmentFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;
  request.url_params = crow::query_string("?deptCode=None");
  routeController.retrieveDepartment(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");
  request.url_params = crow::query_string("?d=None");
  routeController.retrieveDepartment(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
TEST(RouteControllerUnitTests, RetrieveCourseSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;
  request.url_params = crow::query_string("?deptCode=COMS&courseCode=3157");
  routeController.retrieveCourse(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body, MyApp::getDatabase()
                               ->getDepartmentMapping()["COMS"]
                               .getCourseSelection()["3157"]
                               ->display());
}
TEST(RouteControllerUnitTests, RetrieveCourseFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params = crow::query_string("?deptCode=COMS&courseCode=3252");
  routeController.retrieveCourse(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Course Not Found");
  response.clear();

  request.url_params = crow::query_string("?deptCode=XXX&courseCode=2000");
  routeController.retrieveCourse(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");

  response.clear();
  request.url_params = crow::query_string("?d=None");
  routeController.retrieveCourse(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
TEST(RouteControllerUnitTests, IsCourseFullSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params = crow::query_string("?deptCode=COMS&courseCode=3157");
  routeController.isCourseFull(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body, "false");
}
TEST(RouteControllerUnitTests, IsCourseFullFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params = crow::query_string("?deptCode=COMS&courseCode=3252");
  routeController.isCourseFull(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Course Not Found");
  response.clear();

  request.url_params = crow::query_string("?deptCode=XXX&courseCode=2000");
  routeController.isCourseFull(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");

  response.clear();
  request.url_params = crow::query_string("?d=None");
  routeController.isCourseFull(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
TEST(RouteControllerUnitTests, GetMajorCountFromDeptSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;
  request.url_params = crow::query_string("?deptCode=COMS");
  routeController.getMajorCountFromDept(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body, "There are: 2700 majors in the department");
}
TEST(RouteControllerUnitTests, GetMajorCountFromDeptFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;
  request.url_params = crow::query_string("?deptCode=None");
  routeController.getMajorCountFromDept(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");
  request.url_params = crow::query_string("?d=None");
  routeController.getMajorCountFromDept(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
TEST(RouteControllerUnitTests, IdentifyDeptChairSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;
  request.url_params = crow::query_string("?deptCode=COMS");
  routeController.identifyDeptChair(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body, "Luca Carloni is the department chair.");
}
TEST(RouteControllerUnitTests, IdentifyDeptChairFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;
  request.url_params = crow::query_string("?deptCode=None");
  routeController.identifyDeptChair(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");
  request.url_params = crow::query_string("?d=None");
  routeController.identifyDeptChair(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
TEST(RouteControllerUnitTests, FindCourseLocationSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params = crow::query_string("?deptCode=COMS&courseCode=3157");
  routeController.findCourseLocation(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body, "417 IAB is where the course is located.");
}
TEST(RouteControllerUnitTests, FindCourseLocationFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params = crow::query_string("?deptCode=COMS&courseCode=3252");
  routeController.findCourseLocation(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Course Not Found");
  response.clear();

  request.url_params = crow::query_string("?deptCode=XXX&courseCode=2000");
  routeController.findCourseLocation(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");

  response.clear();
  request.url_params = crow::query_string("?d=None");
  routeController.findCourseLocation(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
TEST(RouteControllerUnitTests, FindCourseInstructorSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params = crow::query_string("?deptCode=COMS&courseCode=3157");
  routeController.findCourseInstructor(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body, "Jae Lee is the instructor for the course.");
}
TEST(RouteControllerUnitTests, FindCourseInstructorFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params = crow::query_string("?deptCode=COMS&courseCode=3252");
  routeController.findCourseInstructor(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Course Not Found");
  response.clear();

  request.url_params = crow::query_string("?deptCode=XXX&courseCode=2000");
  routeController.findCourseInstructor(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");

  response.clear();
  request.url_params = crow::query_string("?d=None");
  routeController.findCourseInstructor(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
TEST(RouteControllerUnitTests, FindCourseTimeSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params = crow::query_string("?deptCode=COMS&courseCode=3157");
  routeController.findCourseTime(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body, "The course meets at: 4:10-5:25");
}
TEST(RouteControllerUnitTests, FindCourseTimeFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params = crow::query_string("?deptCode=COMS&courseCode=3252");
  routeController.findCourseTime(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Course Not Found");
  response.clear();

  request.url_params = crow::query_string("?deptCode=XXX&courseCode=2000");
  routeController.findCourseTime(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");

  response.clear();
  request.url_params = crow::query_string("?d=None");
  routeController.findCourseTime(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
TEST(RouteControllerUnitTests, AddMajorToDeptSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;
  request.url_params = crow::query_string("?deptCode=COMS");
  routeController.addMajorToDept(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body, "Attribute was updated successfully");
}
TEST(RouteControllerUnitTests, AddMajorToDeptFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;
  request.url_params = crow::query_string("?deptCode=None");
  routeController.addMajorToDept(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");
  request.url_params = crow::query_string("?d=None");
  routeController.addMajorToDept(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
TEST(RouteControllerUnitTests, SetEnrollmentCountSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params =
      crow::query_string("?deptCode=COMS&courseCode=3157&count=100");
  routeController.setEnrollmentCount(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body, "Attribute was updated successfully.");
}
TEST(RouteControllerUnitTests, SetEnrollmentCountFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params =
      crow::query_string("?deptCode=COMS&courseCode=3252&count=100");
  routeController.setEnrollmentCount(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Course Not Found");
  response.clear();

  request.url_params =
      crow::query_string("?deptCode=XXX&courseCode=2000&count=100");
  routeController.setEnrollmentCount(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");

  response.clear();
  request.url_params = crow::query_string("?d=None");
  routeController.setEnrollmentCount(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
TEST(RouteControllerUnitTests, SetCourseLocationSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params =
      crow::query_string("?deptCode=COMS&courseCode=3157&location=Mudd");
  routeController.setCourseLocation(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body, "Attribute was updated successfully.");
}
TEST(RouteControllerUnitTests, SetCourseLocationFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params =
      crow::query_string("?deptCode=COMS&courseCode=3252&location=Mudd");
  routeController.setCourseLocation(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Course Not Found");
  response.clear();

  request.url_params =
      crow::query_string("?deptCode=XXX&courseCode=2000&location=Mudd");
  routeController.setCourseLocation(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");

  response.clear();
  request.url_params = crow::query_string("?d=None");
  routeController.setCourseLocation(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
TEST(RouteControllerUnitTests, SetCourseInstructorSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params =
      crow::query_string("?deptCode=COMS&courseCode=3157&instructor=Jack");
  routeController.setCourseInstructor(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body, "Attribute was updated successfully.");
}
TEST(RouteControllerUnitTests, SetCourseInstructorFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params =
      crow::query_string("?deptCode=COMS&courseCode=3252&instructor=Jack");
  routeController.setCourseInstructor(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Course Not Found");
  response.clear();

  request.url_params =
      crow::query_string("?deptCode=XXX&courseCode=2000&instructor=Jack");
  routeController.setCourseInstructor(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");

  response.clear();
  request.url_params = crow::query_string("?d=None");
  routeController.setCourseInstructor(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
TEST(RouteControllerUnitTests, SetCourseTimeSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params =
      crow::query_string("?deptCode=COMS&courseCode=3157&time=11:40-12:50");
  routeController.setCourseTime(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body, "Attribute was updated successfully.");
}
TEST(RouteControllerUnitTests, SetCourseTimeFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params =
      crow::query_string("?deptCode=COMS&courseCode=3252&time=11:40-11:50");
  routeController.setCourseTime(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Course Not Found");
  response.clear();

  request.url_params =
      crow::query_string("?deptCode=XXX&courseCode=2000&time=11:40-11:50");
  routeController.setCourseTime(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");

  response.clear();
  request.url_params = crow::query_string("?d=None");
  routeController.setCourseTime(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
TEST(RouteControllerUnitTests, RemoveMajorFromDeptSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;
  request.url_params = crow::query_string("?deptCode=COMS");
  routeController.removeMajorFromDept(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body, "Attribute was updated successfully");
}
TEST(RouteControllerUnitTests, RemoveMajorFromDeptFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;
  request.url_params = crow::query_string("?deptCode=None");
  routeController.removeMajorFromDept(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");
  request.url_params = crow::query_string("?d=None");
  routeController.removeMajorFromDept(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
TEST(RouteControllerUnitTests, DropStudentFromCourseSuccess) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params = crow::query_string("?deptCode=COMS&courseCode=3157");
  routeController.dropStudentFromCourse(request, response);
  EXPECT_EQ(response.code, 200);
  EXPECT_EQ(response.body, "Student has been dropped");
}
TEST(RouteControllerUnitTests, DropStudentFromCourseFail) {
  MyApp::run("setup");
  crow::SimpleApp app;
  app.signal_clear();
  RouteController routeController;
  routeController.initRoutes(app);
  routeController.setDatabase(MyApp::getDatabase());
  crow::response response;
  crow::request request;

  request.url_params = crow::query_string("?deptCode=COMS&courseCode=3252");
  routeController.dropStudentFromCourse(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Course Not Found");
  response.clear();

  request.url_params = crow::query_string("?deptCode=XXX&courseCode=2000");
  routeController.dropStudentFromCourse(request, response);
  EXPECT_EQ(response.code, 404);
  EXPECT_EQ(response.body, "Department Not Found");

  response.clear();
  request.url_params = crow::query_string("?d=None");
  routeController.dropStudentFromCourse(request, response);
  std::string expect = "An error has occurred";
  EXPECT_EQ(response.body, expect);
}
