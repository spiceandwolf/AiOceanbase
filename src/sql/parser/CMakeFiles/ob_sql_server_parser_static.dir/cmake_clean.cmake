file(REMOVE_RECURSE
  "libob_sql_server_parser_static.a"
  "libob_sql_server_parser_static.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C CXX)
  include(CMakeFiles/ob_sql_server_parser_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
