# CMake generated Testfile for 
# Source directory: /home/spice/workspace/oceanbase/unittest/sql/engine
# Build directory: /home/spice/workspace/oceanbase/unittest/sql/engine
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[test_exec_context]=] "test_exec_context")
set_tests_properties([=[test_exec_context]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/spice/workspace/oceanbase/unittest/CMakeLists.txt;8;add_test;/home/spice/workspace/oceanbase/unittest/sql/CMakeLists.txt;13;ob_unittest;/home/spice/workspace/oceanbase/unittest/sql/engine/CMakeLists.txt;1;sql_unittest;/home/spice/workspace/oceanbase/unittest/sql/engine/CMakeLists.txt;0;")
add_test([=[test_phy_operator]=] "test_phy_operator")
set_tests_properties([=[test_phy_operator]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/spice/workspace/oceanbase/unittest/CMakeLists.txt;8;add_test;/home/spice/workspace/oceanbase/unittest/sql/CMakeLists.txt;13;ob_unittest;/home/spice/workspace/oceanbase/unittest/sql/engine/CMakeLists.txt;2;sql_unittest;/home/spice/workspace/oceanbase/unittest/sql/engine/CMakeLists.txt;0;")
add_test([=[test_engine]=] "test_engine")
set_tests_properties([=[test_engine]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/spice/workspace/oceanbase/unittest/CMakeLists.txt;8;add_test;/home/spice/workspace/oceanbase/unittest/sql/CMakeLists.txt;13;ob_unittest;/home/spice/workspace/oceanbase/unittest/sql/engine/CMakeLists.txt;3;sql_unittest;/home/spice/workspace/oceanbase/unittest/sql/engine/CMakeLists.txt;0;")
add_test([=[test_physical_plan]=] "test_physical_plan")
set_tests_properties([=[test_physical_plan]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/spice/workspace/oceanbase/unittest/CMakeLists.txt;8;add_test;/home/spice/workspace/oceanbase/unittest/sql/CMakeLists.txt;13;ob_unittest;/home/spice/workspace/oceanbase/unittest/sql/engine/CMakeLists.txt;4;sql_unittest;/home/spice/workspace/oceanbase/unittest/sql/engine/CMakeLists.txt;0;")
add_test([=[test_empty_table_scan]=] "test_empty_table_scan")
set_tests_properties([=[test_empty_table_scan]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/spice/workspace/oceanbase/unittest/CMakeLists.txt;8;add_test;/home/spice/workspace/oceanbase/unittest/sql/CMakeLists.txt;13;ob_unittest;/home/spice/workspace/oceanbase/unittest/sql/engine/CMakeLists.txt;5;sql_unittest;/home/spice/workspace/oceanbase/unittest/sql/engine/CMakeLists.txt;0;")
add_test([=[test_sql_fixed_array]=] "test_sql_fixed_array")
set_tests_properties([=[test_sql_fixed_array]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/spice/workspace/oceanbase/unittest/CMakeLists.txt;8;add_test;/home/spice/workspace/oceanbase/unittest/sql/CMakeLists.txt;13;ob_unittest;/home/spice/workspace/oceanbase/unittest/sql/engine/CMakeLists.txt;6;sql_unittest;/home/spice/workspace/oceanbase/unittest/sql/engine/CMakeLists.txt;0;")
subdirs("aggregate")
subdirs("dml")
subdirs("subquery")
subdirs("expr")
subdirs("set")
subdirs("px")
subdirs("basic")
subdirs("sort")
subdirs("join")
subdirs("monitoring_dump")
