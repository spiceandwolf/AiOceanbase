file(REMOVE_RECURSE
  "liboceanbase_static.a"
  "liboceanbase_static.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C CXX)
  include(CMakeFiles/oceanbase_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
