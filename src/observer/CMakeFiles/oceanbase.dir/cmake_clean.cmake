file(REMOVE_RECURSE
  "liboceanbase.pdb"
  "liboceanbase.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang ASM C CXX)
  include(CMakeFiles/oceanbase.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
