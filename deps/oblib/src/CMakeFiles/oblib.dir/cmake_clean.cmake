file(REMOVE_RECURSE
  "liboblib.a"
  "liboblib.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang ASM C CXX)
  include(CMakeFiles/oblib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
