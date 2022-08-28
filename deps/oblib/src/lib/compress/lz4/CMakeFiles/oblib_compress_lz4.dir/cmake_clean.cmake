file(REMOVE_RECURSE
  "lz4-all.a.o"
  "lz4_171.a"
  "lz4_191.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/oblib_compress_lz4.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
