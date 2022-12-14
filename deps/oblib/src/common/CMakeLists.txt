ob_set_subtarget(oblib_common common
  cell/ob_cell_reader.cpp
  cell/ob_cell_writer.cpp
  data_buffer.cpp
  log/ob_direct_log_reader.cpp
  log/ob_log_cursor.cpp
  log/ob_log_data_writer.cpp
  log/ob_log_dir_scanner.cpp
  log/ob_log_entry.cpp
  log/ob_log_generator.cpp
  log/ob_log_reader.cpp
  log/ob_single_log_reader.cpp
  ob_accuracy.cpp
  ob_balance_filter.cpp
  ob_clock_generator.cpp
  ob_common_utility.cpp
  ob_smart_var.cpp
  ob_smart_call.cpp
  ob_field.cpp
  ob_hint.cpp
  object/ob_obj_compare.cpp
  object/ob_object.cpp
  object/ob_obj_type.cpp
  ob_member.cpp
  ob_member_list.ipp
  ob_partition_key.cpp
  ob_queue_thread.cpp
  ob_range.cpp
  ob_record_header.cpp
  ob_role.cpp
  ob_segmented_buffer.cpp
  ob_server_ext.cpp
  ob_store_format.cpp
  ob_store_range.cpp
  ob_string_buf.ipp
  ob_timeout_ctx.cpp
  ob_trace_profile.cpp
  ob_unit_info.cpp
  ob_zone_type.cpp
  rowkey/ob_rowkey.cpp
  rowkey/ob_rowkey_info.cpp
  rowkey/ob_store_rowkey.cpp
  row/ob_row_checksum.cpp
  row/ob_row.cpp
  row/ob_row_desc.cpp
  row/ob_row_store.cpp
  row/ob_row_util.cpp
  sql_mode/ob_sql_mode_utils.cpp
  storage/ob_freeze_define.cpp
  storage/ob_freeze_define.h)

ob_lib_add_target(oblib_common)

ob_lib_add_pchs(common
  ob_local_store.h
  data_buffer.h
  ob_common_utility.h
  object/ob_obj_type.h
  ob_accuracy.h
  ob_partition_key.h
  ob_simple_iterator.h
  object/ob_object.h
  ob_action_flag.h
  rowkey/ob_rowkey.h
  ob_zone.h
  ob_string_buf.h
  ob_smart_var.h
  row/ob_row_desc.h
  row/ob_row.h
  ob_zerofill_info.h
  sql_mode/ob_sql_mode.h
  ob_range.h
  ob_region.h
  ob_role.h
  row/ob_row_checksum.h
  ob_hint.h
  rowkey/ob_rowkey_info.h
  row/ob_row_util.h
  ob_store_format.h
  ob_timeout_ctx.h
  ob_clock_generator.h
  cell/ob_cell_writer.h
  row/ob_row_iterator.h
  row/ob_row_store.h
  ob_member.h
  ob_member_list.h
  ob_common_types.h
  ob_zone_status.h
  storage/ob_freeze_define.h
  ob_zone_type.h
  ob_idc.h
  ob_unit_info.h
  ob_role_mgr.h
  object/ob_obj_compare.h
  ob_balance_filter.h
  server_framework/ob_priority_scheduler.h
  ob_queue_thread.h
  ob_record_header.h
  log/ob_log_entry.h
  rowkey/ob_store_rowkey.h
  log/ob_log_cursor.h
  ob_store_range.h
  log/ob_log_generator.h
  log/ob_log_data_writer.h
  ob_field.h
  expression/ob_expr_string_buf.h
  sql_mode/ob_sql_mode_utils.h
)
