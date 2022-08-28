# Install script for directory: /home/spice/workspace/oceanbase

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/spice/workspace/oceanbase/deps/easy/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/spice/workspace/oceanbase/deps/oblib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/spice/workspace/oceanbase/src/cmake_install.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xserverx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES
    "/home/spice/workspace/oceanbase/tools/timezone/import_time_zone_info.py"
    "/home/spice/workspace/oceanbase/src/observer/observer"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xserverx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/etc" TYPE FILE FILES
    "/home/spice/workspace/oceanbase/tools/timezone/timezone_V1.log"
    "/home/spice/workspace/oceanbase/tools/upgrade/upgrade_pre.py"
    "/home/spice/workspace/oceanbase/tools/upgrade/upgrade_post.py"
    "/home/spice/workspace/oceanbase/tools/upgrade/upgrade_post_checker.py"
    "/home/spice/workspace/oceanbase/tools/upgrade/upgrade_checker.py"
    "/home/spice/workspace/oceanbase/tools/upgrade/upgrade_cluster_health_checker.py"
    "/home/spice/workspace/oceanbase/tools/upgrade/upgrade_rolling_pre.py"
    "/home/spice/workspace/oceanbase/tools/upgrade/upgrade_rolling_post.py"
    "/home/spice/workspace/oceanbase/tools/upgrade/priv_checker.py"
    "/home/spice/workspace/oceanbase/tools/upgrade/oceanbase_upgrade_dep.yml"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/include/ob_errno.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/include" TYPE FILE FILES "/home/spice/workspace/oceanbase/deps/oblib/src/lib/ob_errno.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibsx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE PROGRAM FILES
    "/home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/deps/devel/lib/libaio.so.1"
    "/home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/deps/devel/lib/libaio.so.1.0.1"
    "/home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/deps/devel/lib/libaio.so"
    "/home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/deps/devel/lib/mariadb/libmariadb.so"
    "/home/spice/workspace/oceanbase/deps/3rd/usr/local/oceanbase/deps/devel/lib/mariadb/libmariadb.so.3"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/spice/workspace/oceanbase/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
