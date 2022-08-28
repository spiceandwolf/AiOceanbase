# CMake generated Testfile for 
# Source directory: /home/spice/workspace/oceanbase/unittest/sql/parser
# Build directory: /home/spice/workspace/oceanbase/unittest/sql/parser
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[test_parser_perf]=] "test_parser_perf")
set_tests_properties([=[test_parser_perf]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/spice/workspace/oceanbase/unittest/CMakeLists.txt;8;add_test;/home/spice/workspace/oceanbase/unittest/sql/parser/CMakeLists.txt;1;ob_unittest;/home/spice/workspace/oceanbase/unittest/sql/parser/CMakeLists.txt;0;")
add_test([=[test_parser]=] "test_parser")
set_tests_properties([=[test_parser]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/spice/workspace/oceanbase/unittest/CMakeLists.txt;8;add_test;/home/spice/workspace/oceanbase/unittest/sql/CMakeLists.txt;13;ob_unittest;/home/spice/workspace/oceanbase/unittest/sql/parser/CMakeLists.txt;2;sql_unittest;/home/spice/workspace/oceanbase/unittest/sql/parser/CMakeLists.txt;0;")
add_test([=[test_multi_parser]=] "test_multi_parser")
set_tests_properties([=[test_multi_parser]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/spice/workspace/oceanbase/unittest/CMakeLists.txt;8;add_test;/home/spice/workspace/oceanbase/unittest/sql/CMakeLists.txt;13;ob_unittest;/home/spice/workspace/oceanbase/unittest/sql/parser/CMakeLists.txt;3;sql_unittest;/home/spice/workspace/oceanbase/unittest/sql/parser/CMakeLists.txt;0;")
