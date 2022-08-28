file(REMOVE_RECURSE
  "observer"
  "observer.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/observer.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
